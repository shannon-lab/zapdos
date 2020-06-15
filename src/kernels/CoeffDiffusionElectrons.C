//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CoeffDiffusionElectrons.h"

registerADMooseObject("ZapdosApp", CoeffDiffusionElectrons);

InputParameters
CoeffDiffusionElectrons::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
      "Electron specific diffusion term (electron density must be in log form), where the Jacobian "
      "is computed using forward automatic differentiation.");
  return params;
}

CoeffDiffusionElectrons::CoeffDiffusionElectrons(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _diffem(getADMaterialProperty<Real>("diffem"))
{
}

ADReal
CoeffDiffusionElectrons::computeQpResidual()
{
  return -_diffem[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
         _r_units;
}
