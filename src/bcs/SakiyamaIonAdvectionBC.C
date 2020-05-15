//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaIonAdvectionBC.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", SakiyamaIonAdvectionBC);

template <>
InputParameters
validParams<SakiyamaIonAdvectionBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic advective ion boundary condition"
                             "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

SakiyamaIonAdvectionBC::SakiyamaIonAdvectionBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),

    _mu(getMaterialProperty<Real>("mu" + _var.name())),
    _e(getMaterialProperty<Real>("e")),
    _sgn(getMaterialProperty<Real>("sgn" + _var.name())),
    _a(0.5)
{
}

Real
SakiyamaIonAdvectionBC::computeQpResidual()
{
  if (_normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  return _test[_i][_qp] * _r_units *
         (_a * _sgn[_qp] * _mu[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) *
          _normals[_qp]);
}

Real
SakiyamaIonAdvectionBC::computeQpJacobian()
{
  if (_normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  return _test[_i][_qp] * _r_units *
         (_a * _sgn[_qp] * _mu[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) *
          _phi[_j][_qp] * _normals[_qp]);
}

Real
SakiyamaIonAdvectionBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    if (_normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    return _test[_i][_qp] * _r_units *
           (_a * _sgn[_qp] * _mu[_qp] * -_grad_phi[_j][_qp] * _r_units * std::exp(_u[_qp]) *
            _normals[_qp]);
  }

  else
    return 0.0;
}
