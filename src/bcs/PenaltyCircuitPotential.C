//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PenaltyCircuitPotential.h"
#include "MooseMesh.h"

registerMooseObject("ZapdosApp", PenaltyCircuitPotential);

InputParameters
PenaltyCircuitPotential::validParams()
{
  InputParameters params = NonlocalIntegratedBC::validParams();
  params.addRequiredParam<UserObjectName>(
      "current",
      "The postprocessor response for calculating the current passing through the needle surface.");
  params.addRequiredParam<Real>(
      "surface_potential",
      "The electrical potential applied to the surface if no current was flowing in the circuit.");
  params.addRequiredParam<std::string>("surface",
                                       "Whether you are specifying the potential on the "
                                       "anode or the cathode with the requirement that the "
                                       "other metal surface be grounded.");
  params.addRequiredParam<Real>("penalty", "The constant multiplying the penalty term.");
  params.addRequiredParam<UserObjectName>(
      "data_provider",
      "The name of the UserObject that can provide some data to materials, bcs, etc.");

  params.addRequiredCoupledVar("em", "The electron variable.");
  params.deprecateCoupledVar("em", "electrons", "06/01/2024");
  params.addRequiredCoupledVar("electrons", "The electron density in log form.");

  params.addRequiredCoupledVar("ip", "The ion variable.");
  params.deprecateCoupledVar("ip", "ions", "06/01/2024");
  params.addRequiredCoupledVar("ions", "The ion density in log form.");

  params.addRequiredCoupledVar("mean_en", "The mean electron energy density in log form.");
  params.deprecateCoupledVar("mean_en", "electron_energy", "06/01/2024");
  params.addRequiredCoupledVar("electron_energy", "The mean electron energy density in log form.");

  params.addParam<Real>("area", "Must be provided when the number of dimensions equals 1.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("resistance", "The ballast resistance in Ohms.");
  params.addClassDescription(
      "Circuit boundary condition for potential multiplied by a penalty term");
  return params;
}

PenaltyCircuitPotential::PenaltyCircuitPotential(const InputParameters & parameters)
  : NonlocalIntegratedBC(parameters),
    _current_uo(getUserObject<CurrentDensityShapeSideUserObject>("current")),
    _current(_current_uo.getIntegral()),
    _current_jac(_current_uo.getJacobian()),
    _surface_potential(getParam<Real>("surface_potential")),
    _surface(getParam<std::string>("surface")),
    _p(getParam<Real>("penalty")),
    _data(getUserObject<ProvideMobility>("data_provider")),
    _var_dofs(_var.dofIndices()),
    _em_id(coupled("electrons")),
    _em_dofs(getVar("electrons", 0)->dofIndices()),
    _mean_en_id(coupled("electron_energy")),
    _mean_en_dofs(getVar("electron_energy", 0)->dofIndices()),
    _r_units(1. / getParam<Real>("position_units")),
    _resistance(getParam<Real>("resistance")),
    _num_ions(coupledComponents("ions"))
{

  _ip_ids.resize(_num_ions);
  _ip_dofs.resize(_num_ions);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip_ids[i] = coupled("ions", i);
    _ip_dofs[i] = &getVar("ions", i)->dofIndices();
  }

  if (_surface.compare("anode") == 0)
    _current_sign = -1.;
  else if (_surface.compare("cathode") == 0)
    _current_sign = 1.;

  if (_mesh.dimension() == 1 && isParamValid("area"))
  {
    _area = getParam<Real>("area");
    _use_area = true;
  }
  else if (_mesh.dimension() == 1 && !(isParamValid("area")))
    mooseError("In a one-dimensional simulation, the area parameter must be set.");
  else
    _use_area = false;

  if (getParam<std::string>("potential_units").compare("V") == 0)
    _voltage_scaling = 1.;
  else if (getParam<std::string>("potential_units").compare("kV") == 0)
    _voltage_scaling = 1000;
  else
    mooseError("Potential specified must be either 'V' or 'kV'.");
}

Real
PenaltyCircuitPotential::computeQpResidual()
{
  curr_times_resist = _current_sign * _current * _resistance / _voltage_scaling;
  if (_use_area)
    curr_times_resist *= _area;

  return _test[_i][_qp] * _r_units * _p * (_surface_potential - _u[_qp] + curr_times_resist);
}

Real
PenaltyCircuitPotential::computeQpJacobian()
{
  d_curr_times_resist_d_potential =
      _current_sign * _current_jac[_var_dofs[_j]] * _resistance / _voltage_scaling;
  if (_use_area)
    d_curr_times_resist_d_potential *= _area;

  return _test[_i][_qp] * _r_units * _p * (-_phi[_j][_qp] + d_curr_times_resist_d_potential);
}

Real
PenaltyCircuitPotential::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
  {
    d_curr_times_resist_d_em =
        _current_sign * _current_jac[_em_dofs[_j]] * _resistance / _voltage_scaling;
    if (_use_area)
      d_curr_times_resist_d_em *= _area;

    return _test[_i][_qp] * _r_units * _p * d_curr_times_resist_d_em;
  }
  else if (jvar == _mean_en_id)
  {
    d_curr_times_resist_d_mean_en =
        _current_sign * _current_jac[_mean_en_dofs[_j]] * _resistance / _voltage_scaling;
    if (_use_area)
      d_curr_times_resist_d_mean_en *= _area;

    return _test[_i][_qp] * _r_units * _p * d_curr_times_resist_d_mean_en;
  }
  else
  {
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      if (jvar == _ip_ids[i])
      {
        d_curr_times_resist_d_ip =
            _current_sign * _current_jac[(*_ip_dofs[i])[_j]] * _resistance / _voltage_scaling;
        if (_use_area)
          d_curr_times_resist_d_ip *= _area;

        return _test[_i][_qp] * _r_units * _p * d_curr_times_resist_d_ip;
      }
    }
  }

  return 0;
}

Real
PenaltyCircuitPotential::computeQpNonlocalJacobian(dof_id_type dof_index)
{
  d_curr_times_resist_d_potential =
      _current_sign * _current_jac[dof_index] * _resistance / _voltage_scaling;
  if (_use_area)
    d_curr_times_resist_d_potential *= _area;

  return _test[_i][_qp] * _r_units * _p * d_curr_times_resist_d_potential;
}

Real
PenaltyCircuitPotential::computeQpNonlocalOffDiagJacobian(unsigned int jvar, dof_id_type dof_index)
{
  if (jvar == _em_id || jvar == _mean_en_id)
  {
    d_curr_times_resist_d_coupled_var =
        _current_sign * _current_jac[dof_index] * _resistance / _voltage_scaling;
    if (_use_area)
      d_curr_times_resist_d_coupled_var *= _area;

    return _test[_i][_qp] * _r_units * _p * d_curr_times_resist_d_coupled_var;
  }
  else
  {
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      if (jvar == _ip_ids[i])
      {
        d_curr_times_resist_d_coupled_var =
            _current_sign * _current_jac[dof_index] * _resistance / _voltage_scaling;
        if (_use_area)
          d_curr_times_resist_d_coupled_var *= _area;

        return _test[_i][_qp] * _r_units * _p * d_curr_times_resist_d_coupled_var;
      }
    }
  }
  return 0;
}
