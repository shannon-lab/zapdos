//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "LymberopoulosElectronBC.h"

registerMooseObject("ZapdosApp", LymberopoulosElectronBC);

InputParameters
LymberopoulosElectronBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("ks", "The recombination coefficient");
  params.addRequiredParam<std::vector<Real>>(
      "emission_coeffs", "The species-dependent secondary electron emission coefficients");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("ions", "A list of ion densities in log form");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Simpified kinetic electron boundary condition"
                             " (Based on [!cite](Lymberopoulos1993))");
  return params;
}

LymberopoulosElectronBC::LymberopoulosElectronBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _ks(getParam<Real>("ks")),
    _gamma(getParam<std::vector<Real>>("emission_coeffs")),
    _num_ions(coupledComponents("ions")),
    // Coupled Variables
    _grad_potential(adCoupledGradient("potential"))
{
  // Resize the vectors to store _num_ions values:
  _ion.resize(_num_ions);
  _ion_var.resize(_num_ions);
  _muion.resize(_num_ions);
  _sgnion.resize(_num_ions);

  // Retrieve the values for each ion and store in the relevant vectors.
  // Note that these need to be dereferenced to get the values inside the
  // main body of the code.
  // e.g. instead of "_ip[_qp]" it would be "(*_ip[i])[_qp]", where "i"
  // refers to a single ion species.
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion_var[i] = getVar("ions", i);
    _ion[i] = &adCoupledValue("ions", i);
    _muion[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _sgnion[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
  }
}

ADReal
LymberopoulosElectronBC::computeQpResidual()
{
  _ion_flux.zero();
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion_flux += _gamma[i] * (*_sgnion[i])[_qp] * (*_muion[i])[_qp] * -_grad_potential[_qp] *
                 _r_units * std::exp((*_ion[i])[_qp]);
  }

  return _test[_i][_qp] * _r_units *
         (_ks * std::exp(_u[_qp]) * _normals[_qp] * _normals[_qp] - _ion_flux * _normals[_qp]);
}
