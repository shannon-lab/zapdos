//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronDiffusionDoNothingBC.h"

registerMooseObject("ZapdosApp", ElectronDiffusionDoNothingBC);

template <>
InputParameters
validParams<ElectronDiffusionDoNothingBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("mean_en",
                               "The log of the product of mean energy times electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position");
  params.addClassDescription(
    "Boundary condition where the election diffusion flux at the boundary is equal to the bulk election diffusion equation");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

ElectronDiffusionDoNothingBC::ElectronDiffusionDoNothingBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffem(getMaterialProperty<Real>("diffem")),
    _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en")),

    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),

    _d_diffem_d_u(0),
    _d_diffem_d_mean_en(0)
{
}

ElectronDiffusionDoNothingBC::~ElectronDiffusionDoNothingBC() {}

Real
ElectronDiffusionDoNothingBC::computeQpResidual()
{
  return -_diffem[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * _normals[_qp] *
         _test[_i][_qp] * _r_units;
}

Real
ElectronDiffusionDoNothingBC::computeQpJacobian()
{
  _d_diffem_d_u =
      _d_diffem_d_actual_mean_en[_qp] * std::exp(_mean_en[_qp] - _u[_qp]) * -_phi[_j][_qp];

  return -_diffem[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] * _r_units +
                          std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp] * _r_units) *
             _normals[_qp] * _test[_i][_qp] * _r_units -
         _d_diffem_d_u * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * _normals[_qp] *
             _test[_i][_qp] * _r_units;
}

Real
ElectronDiffusionDoNothingBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _mean_en_id)
  {
    _d_diffem_d_mean_en =
        _d_diffem_d_actual_mean_en[_qp] * std::exp(_mean_en[_qp] - _u[_qp]) * _phi[_j][_qp];

    return -_d_diffem_d_mean_en * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * _normals[_qp] *
           _test[_i][_qp] * _r_units;
  }

  else
    return 0.;
}
