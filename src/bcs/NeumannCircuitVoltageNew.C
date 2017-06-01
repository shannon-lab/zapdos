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
#include "MooseMesh.h"
#include "Function.h"

template<>
InputParameters validParams<NeumannCircuitVoltageNew>()
{
	InputParameters p = validParams<NonlocalIntegratedBC>();
	p.addRequiredParam<FunctionName>("source_voltage", "The function describing the time dependent source voltage.");
	p.addRequiredParam<UserObjectName>("current", "The current in the circuit.");
	p.addRequiredParam<std::string>("surface", "Whether you are specifying the potential on the anode or the cathode with the requirement that the other metal surface be grounded.");
	p.addRequiredParam<UserObjectName>("data_provider", "The name of the UserObject that can provide some data to materials, bcs, etc.");
	p.addRequiredCoupledVar("em", "The electron variable.");
	p.addRequiredCoupledVar("ip", "The ion variable.");
	p.addRequiredCoupledVar("mean_en", "The ion variable.");
	p.addParam<Real>("area", "Must be provided when the number of dimensions equals 1.");
	p.addRequiredParam<std::string>("potential_units", "The potential units.");
	p.addRequiredParam<Real>("position_units", "Units of position.");
	p.addRequiredParam<Real>("resistance", "The ballast resistance in Ohms.");
	return p;
}


NeumannCircuitVoltageNew::NeumannCircuitVoltageNew(const InputParameters & parameters) :
	NonlocalIntegratedBC(parameters),
	_current_uo(getUserObject<CurrentDensityShapeSideUserObject>("current")),
	_current(_current_uo.getIntegral()),
	_current_jac(_current_uo.getJacobian()),
	_surface(getParam<std::string>("surface")),
	_data(getUserObject<ProvideMobility>("data_provider")),

	// dof
	_var_dofs(_var.dofIndices()),
	_em_id(coupled("em")),
	_em_dofs(getVar("em", 0)->dofIndices()),
	_ip_id(coupled("ip")),
	_ip_dofs(getVar("ip", 0)->dofIndices()),
	_mean_en_id(coupled("mean_en")),
	_mean_en_dofs(getVar("mean_en", 0)->dofIndices()),

	// System properties
	_V_source(getFunction("source_voltage")),
	_resistance(getParam<Real>("resistance")),

	// units
	_r_units(1. / getParam<Real>("position_units"))

{
	if (_surface.compare("anode") == 0) {
		_current_sign = -1.;
	} else if (_surface.compare("cathode") == 0) {
		_current_sign = 1.;
	}

	if (_mesh.dimension() == 1 && isParamValid("area"))
	{
		_area = getParam<Real>("area");
		_use_area = true;
	} else if (_mesh.dimension() == 1 && !(isParamValid("area"))) {
		mooseError("In a one-dimensional simulation, the area parameter must be set.");
	} else {
		_use_area = false;
	}

	if (getParam<std::string>("potential_units").compare("V") == 0) {
		_voltage_scaling = 1.;
	} else if (getParam<std::string>("potential_units").compare("kV") == 0) {
		_voltage_scaling = 1000;
	} else {
		mooseError("Potential specified must be either 'V' or 'kV'.");
	}
}

Real
NeumannCircuitVoltageNew::computeQpResidual()
{
	Real d_curr_times_resist_d_potential = _current_sign * _current * _resistance / _voltage_scaling;

	if (_use_area) {
		d_curr_times_resist_d_potential *= _area;
	}

	return _test[_i][_qp] * _r_units * (_V_source.value(_t, _q_point[_qp]) + _u[_qp] + d_curr_times_resist_d_potential);
}

Real
NeumannCircuitVoltageNew::computeQpJacobian()
{
	Real d_curr_times_resist_dv = _current_sign * _current_jac[_var_dofs[_j]] * _resistance / _voltage_scaling;

	if (_use_area) {
		d_curr_times_resist_dv *= _area;
	}

	return _test[_i][_qp] * _r_units * ( _phi[_j][_qp] + d_curr_times_resist_dv);
}

Real
NeumannCircuitVoltageNew::computeQpOffDiagJacobian(unsigned int jvar)
{
	Real d_curr_times_resist_dv;

	if (jvar == _em_id) {
		d_curr_times_resist_dv = _current_sign * _current_jac[_em_dofs[_j]] * _resistance / _voltage_scaling ;
	} else if (jvar == _ip_id) {
		d_curr_times_resist_dv = _current_sign * _current_jac[_ip_dofs[_j]] * _resistance / _voltage_scaling;
	} else if (jvar == _mean_en_id) {
		d_curr_times_resist_dv = _current_sign * _current_jac[_mean_en_dofs[_j]] * _resistance / _voltage_scaling;
	} else {
		return 0;
	}

	if (_use_area) {
		d_curr_times_resist_dv *= _area;
	}

	return _test[_i][_qp] * _r_units * d_curr_times_resist_dv;

}

Real
NeumannCircuitVoltageNew::computeQpNonlocalJacobian(dof_id_type dof_index)
{
	Real d_curr_times_resist_d_potential = _current_sign * _current_jac[dof_index] * _resistance / _voltage_scaling;

	if (_use_area) {
		d_curr_times_resist_d_potential *= _area;
	}

	return _test[_i][_qp] * _r_units * d_curr_times_resist_d_potential;
}

Real
NeumannCircuitVoltageNew::computeQpNonlocalOffDiagJacobian(unsigned int jvar, dof_id_type dof_index)
{
	if (jvar == _em_id || jvar == _ip_id || jvar == _mean_en_id)
	{
		Real d_curr_times_resist_dv = _current_sign * _current_jac[dof_index] * _resistance / _voltage_scaling;

		if (_use_area) {
			d_curr_times_resist_dv *= _area;
		}

		return _test[_i][_qp] * _r_units * d_curr_times_resist_dv;
	}

	return 0;
}
