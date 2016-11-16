/****************************************************************/
/*								DO NOT MODIFY THIS HEADER											*/
/*	MOOSE - Multiphysics Object Oriented Simulation Environment	*/
/*																															*/
/*						(c) 2010 Battelle Energy Alliance, LLC						*/
/*										ALL RIGHTS RESERVED												*/
/*																															*/
/*					Prepared by Battelle Energy Alliance, LLC						*/
/*						Under Contract No. DE-AC07-05ID14517							*/
/*						With the U. S. Department of Energy								*/
/*																															*/
/*						See COPYRIGHT for full restrictions								*/
/****************************************************************/

#include "NeumannCircuitVoltageNew.h"
#include "Function.h"

template<>
InputParameters validParams<NeumannCircuitVoltageNew>()
{
	InputParameters params = validParams<NonlocalIntegratedBC>();
	params.addRequiredParam<FunctionName>("function", "The function describing the time dependent source voltage.");
	params.addRequiredParam<UserObjectName>("current_density", "The total gas current density.");

	params.addRequiredCoupledVar("ip","The ion density.");
	params.addRequiredCoupledVar("em","The log of the electron density.");
	params.addRequiredCoupledVar("mean_en","The log of the product of the mean energy and the electron density.");
	params.addRequiredParam<std::string>("potential_units", "The potential units.");
	params.addRequiredParam<Real>("position_units", "Units of position.");

//	params.addRequiredParam<UserObjectName>("data_provider","The name of the UserObject that can provide some data to materials, bcs, etc.");
//	params.addRequiredParam<Real>("r", "The reflection coefficient applied to both electrons and ions");
	return params;
}

NeumannCircuitVoltageNew::NeumannCircuitVoltageNew(const InputParameters & parameters) :
	NonlocalIntegratedBC(parameters),

	//Data
  _data(getUserObject<ProvideMobility>("data_provider")),

	// Current and current density
  _current_density(getUserObject<CurrentDensityShapeSideUserObject>("current_density")),
	_current(_current_density.getIntegral()),
	_current_density_jacobian(_current_density.getJacobian()),

	// Coupled variables
	_var_dofs(_var.dofIndices()),

//	_ip(coupledValue("ip")),
//	_em(coupledValue("em")),
//	_mean_en(coupledValue("mean_en")),

	_ip_id(coupled("ip")),
	_ip_dofs(getVar("ip", 0)->dofIndices()),

	_em_id(coupled("em")),
	_em_dofs(getVar("em", 0)->dofIndices()),

	_mean_en_id(coupled("mean_en")),
	_mean_en_dofs(getVar("mean_en", 0)->dofIndices()),

	// System parameters
	_V_source(getFunction("function")),

	// Units
	_potential_units(getParam<std::string>("potential_units")),
	_r_units(1. / getParam<Real>("position_units"))

{
	if (_potential_units.compare("V") == 0)
		_voltage_scaling = 1.;
	else if (_potential_units.compare("kV") == 0)
		_voltage_scaling = 1000;
}


Real
NeumannCircuitVoltageNew::computeQpResidual()
{
	return _test[_i][_qp] * _r_units * ( _u[_qp] + _V_source.value(_t, _q_point[_qp]) - _data.ballast_resist() * _current ) / _voltage_scaling ;
}

Real
NeumannCircuitVoltageNew::computeQpJacobian()
{
	return _test[_i][_qp] * _r_units * _phi[_j][_qp] / _voltage_scaling ;
}


Real
NeumannCircuitVoltageNew::computeQpOffDiagJacobian(unsigned int jvar)
{
	if (jvar == _ip_id) {
		return _test[_i][_qp] * _r_units * ( - _data.ballast_resist() * _current_density_jacobian[_ip_dofs[_j]] ) / _voltage_scaling ;
	} else if (jvar == _em_id) {
		return _test[_i][_qp] * _r_units * ( - _data.ballast_resist() * _current_density_jacobian[_em_dofs[_j]] ) / _voltage_scaling ;
	} else if (jvar == _mean_en_id) {
		return _test[_i][_qp] * _r_units * ( - _data.ballast_resist() * _current_density_jacobian[_mean_en_dofs[_j]] ) / _voltage_scaling ;
	}	else {
		return 0.0;
	}
}
