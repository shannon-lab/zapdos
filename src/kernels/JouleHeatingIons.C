//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "JouleHeatingIons.h"

registerADMooseObject("ZapdosApp", JouleHeatingIons);

// defineADLegacyParams(JouleHeatingIons);
// defineADValidParams(
//    JouleHeatingIons,
//    ADKernel,
//    params.addRequiredParam<Real>("position_units", "Units of position.");
//    params.addClassDescription("Same as JouleHeating, but the Jacobian is computed using forward
//    "
//                               "automatic differentiation."););

InputParameters
JouleHeatingIons::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("ions", "The electron density.");
  params.addRequiredCoupledVar("potential", "The electron density.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

JouleHeatingIons::JouleHeatingIons(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _potential_units(getParam<std::string>("potential_units")),
    //_diff(getADMaterialProperty<Real>("diffem")),
    //_mu(getADMaterialProperty<Real>("muem")),
    _grad_potential(adCoupledGradient("potential"))
//_em(adCoupledValue("em")),
//_grad_em(adCoupledGradient("em"))
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000.;
  else
    mooseError("Potential units " + _potential_units + " not valid! Use V or kV.");

  _num_ions = coupledComponents("ions");

  // Resize the vectors to store _num_ions values:
  _ion.resize(_num_ions);
  _grad_ion.resize(_num_ions);
  _mu.resize(_num_ions);
  _diff.resize(_num_ions);
  _sign.resize(_num_ions);

  // Retrieve the values for each ion and store in the relevant vectors.
  // Note that these need to be dereferenced to get the values inside the
  // main body of the code.
  // e.g. instead of "_ip[_qp]" it would be "(*_ip[i])[_qp]", where "i"
  // refers to a single ion species.
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion[i] = &adCoupledValue("ions", i);
    _grad_ion[i] = &adCoupledGradient("ions", i);
    _mu[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _diff[i] = &getADMaterialProperty<Real>("diff" + (*getVar("ions", i)).name());
    _sign[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
  }
}

ADReal
JouleHeatingIons::computeQpResidual()
{
  // Loop through the ions to calculate total flux term

  ADReal _ion_flux;
  _ion_flux = 0;
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion_flux += _test[_i][_qp] * -_grad_potential[_qp] * _r_units * _voltage_scaling *
                 std::exp((*_ion[i])[_qp]) *
                 ((*_sign[i])[_qp] * (*_mu[i])[_qp] * -_grad_potential[_qp] * _r_units -
                  (*_diff[i])[_qp] * (*_grad_ion[i])[_qp] * _r_units);
  }
  // return _test[_i][_qp] * -_grad_potential[_qp] * _r_units * _voltage_scaling * _ion_flux;
  return -_ion_flux;

  /*
  return _test[_i][_qp] * -_grad_potential[_qp] * _r_units * _voltage_scaling * std::exp(_em[_qp]) *
         (-_mu[_qp] * -_grad_potential[_qp] * _r_units - _diff[_qp] * _grad_em[_qp] * _r_units);
         */
}
