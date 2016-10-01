#include "FieldEmissionBC.h"

template<>
InputParameters validParams<FieldEmissionBC>()
{
	InputParameters params = validParams<IntegratedBC>();
	params.addRequiredParam<Real>("r", "The reflection coefficient");
	params.addRequiredCoupledVar("potential","The electric potential");
	params.addRequiredCoupledVar("mean_en", "The mean energy.");
	params.addRequiredCoupledVar("ip", "The ion density.");
	params.addRequiredParam<Real>("position_units", "Units of position.");
	return params;
}

FieldEmissionBC::FieldEmissionBC(const InputParameters & parameters) :
	IntegratedBC(parameters),

	_r_units(1. / getParam<Real>("position_units")),
	_r(getParam<Real>("r")),

// Coupled Variables
	_grad_potential(coupledGradient("potential")),
	_potential_id(coupled("potential")),
	_mean_en(coupledValue("mean_en")),
	_mean_en_id(coupled("mean_en")),
	_ip_var(*getVar("ip",0)),
	_ip(coupledValue("ip")),
	_grad_ip(coupledGradient("ip")),
	_ip_id(coupled("ip")),

	_muem(getMaterialProperty<Real>("muem")),
	_d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
	_massem(getMaterialProperty<Real>("massem")),
	_e(getMaterialProperty<Real>("e")),
	_sgnip(getMaterialProperty<Real>("sgn" + _ip_var.name())),
	_muip(getMaterialProperty<Real>("mu" + _ip_var.name())),
	_Dip(getMaterialProperty<Real>("diff" + _ip_var.name())),
	_work_function(getMaterialProperty<Real>("work_function")),
	_field_enhancement(getMaterialProperty<Real>("field_enhancement")),
	_a(0.5),
	_v_thermal(0),
	_ion_flux(0, 0, 0),
	_n_gamma(0),
	_d_v_thermal_d_u(0),
	_d_v_thermal_d_mean_en(0),
	_d_ion_flux_d_potential(0, 0, 0),
	_d_ion_flux_d_ip(0, 0, 0),
	_d_n_gamma_d_potential(0),
	_d_n_gamma_d_ip(0),
	_d_n_gamma_d_u(0),
	_d_n_gamma_d_mean_en(0),
	_actual_mean_en(0)
{}

Real
FieldEmissionBC::computeQpResidual()
{	
	Real a;
	Real b;
	Real c;
	Real v;
	Real f;
	Real je;
	Real F;

	_v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]));
	
	if ( _normals[_qp] * -_grad_potential[_qp] > 0.0) {
		_a = 1.0;

		// Fowler-Nordheim
			// je = (a / wf) * F^2 * exp(-v(f) * b * wf^1.5 / F)
			// a = 1.541434E-6 A eV/V^2
			// b = 6.830890E9 V/m-eV^1.5
			// c = 1.439964E-9 eV^2-m/V
			// v(f) = 1 - f + (f/6)*ln(f)
			// f = c*(F/wf^2)
	
		F = -_a * _field_enhancement[_qp] * _normals[_qp] * _grad_potential[_qp] * _r_units;
	
		a = 1.541434; // A eV/kV^2
		b = 6.830890E6; // kV/m-eV^1.5
		c = 1.439964E-6; // eV^2*m/kV
	
		f = c * F / pow(_work_function[_qp], 2) ;
		v = 1 - f + (f/6)*std::log(f);
	
		je = (a / (_work_function[_qp])) * pow( F , 2) * std::exp(v * b * pow(_work_function[_qp], 1.5) / F);
	
		return -_test[_i][_qp] * (je / _e[_qp]);
	}
	else {
		_a = 0.0;
		return 0;
	}
	
}

Real
FieldEmissionBC::computeQpJacobian()
{
	if ( _normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0) {
		_a = 1.0;
	}
	else {
		_a = 0.0;
	}
 
	_actual_mean_en = std::exp(_mean_en[_qp] - _u[_qp]);
 
	_v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]));
	_d_v_thermal_d_u = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]) * -_phi[_j][_qp];

	return 0.;
}

Real
FieldEmissionBC::computeQpOffDiagJacobian(unsigned int jvar)
{
	Real a;
	Real b;
	Real c;
	Real v;
	Real f;
	Real F;
	
	_v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]));

	// Fowler-Nordheim
	// je = (a / wf) * F^2 * exp(-v(f) * b * wf^1.5 / F)
	// a = 1.541434E-6 A eV/V^2
	// b = 6.830890E9 V/m-eV^1.5
	// v(f) = 1 - f + (f/6)*ln(f)
	// f = (1.439964E-9 eV^2 m/V)*(F/wf^2)
		
	if (jvar == _potential_id)
	{
		if ( _normals[_qp] * -_grad_potential[_qp] > 0.0)
		{
			_a = 1.0;
	
			F = -_a * _field_enhancement[_qp] * _normals[_qp] * _grad_potential[_qp] * _r_units;
	
			a = 1.541434; // A eV/kV^2
			b = 6.830890E6; // kV/m-eV^1.5
			c = 1.439964E-6; // eV^2*m/kV
	
			f = c * F / pow(_work_function[_qp], 2) ;
			v = 1 - f + (f/6)*std::log(f);

			return - _test[_i][_qp] * 
						a / (6*_e[_qp]*pow(_work_function[_qp], 2.5)) * 
						std::exp(b * (pow(_work_function[_qp], 2) - c*F)/(F*sqrt(_work_function[_qp]))) *
						pow(c*F*pow(_work_function[_qp],-1) , b*c/(6*sqrt(_work_function[_qp]))) *
						(b*c*F + 12*F*pow(_work_function[_qp], 1.5) - 6*b*pow(_work_function[_qp], 3)) *
						_field_enhancement[_qp] * (-_grad_phi[_j][_qp] * _normals[_qp]) * _r_units ;
		}
		else
		{
			_a = 0.0;
			
			return 0.0 ;
		}
	}
	else if (jvar == _mean_en_id)
	{
		if ( _normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0) {
			_a = 1.0;
		}
		else {
			_a = 0.0;
		}
		_v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]));
		_d_v_thermal_d_mean_en	= 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]) * _phi[_j][_qp];
		_actual_mean_en = std::exp(_mean_en[_qp] - _u[_qp]);

		return 0.;
	}

	else if (jvar == _ip_id)
	{
		if ( _normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0) {
			_a = 1.0;
		}
		else {
			_a = 0.0;
		}

		_v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]));
		_d_ion_flux_d_ip = _sgnip[_qp] * _muip[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_ip[_qp]) * _phi[_j][_qp] - _Dip[_qp] * std::exp(_ip[_qp]) * _grad_phi[_j][_qp] * _r_units - _Dip[_qp] * std::exp(_ip[_qp]) * _phi[_j][_qp] * _grad_ip[_qp] * _r_units;

		return 0;
	}

	else
		return 0.0;
}
