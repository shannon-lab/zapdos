//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CoeffDiffusionEnergy.h"

registerMooseObject("ZapdosApp", CoeffDiffusionEnergy);

InputParameters
CoeffDiffusionEnergy::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("em", "The log of the electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Electron energy specific diffusion term"
                             "(Densities must be in log form)");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

CoeffDiffusionEnergy::CoeffDiffusionEnergy(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _diffel(getADMaterialProperty<Real>("diffmean_en")),
    _em(coupledValue("em"))
{
}

ADReal
CoeffDiffusionEnergy::computeQpResidual()
{
  return -_diffel[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
         _r_units;
}
