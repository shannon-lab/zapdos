//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ParticleConservation.h"

registerMooseObject("ZapdosApp", ParticleConservation);

defineLegacyParams(ParticleConservation);

InputParameters
ParticleConservation::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription(" ");
  params.addRequiredCoupledVar("nonconserved", "Densities of the other particles");
  return params;
}

ParticleConservation::ParticleConservation(const InputParameters & parameters)
  : Material(parameters),
    _gas_temp(getMaterialProperty<Real>("T_gas")),
    _gas_pressure(getMaterialProperty<Real>("p_gas")),
    _conserved_density(declareADProperty<Real>("conserved_density"))
{
  _num_ions = coupledComponents("nonconserved");

  // Resize the vectors to store _num_ions values:
  _other_densities.resize(_num_ions);
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _other_densities[i] = &coupledValue("nonconserved", i);
  }
}

void
ParticleConservation::computeQpProperties()
{
  ADReal density_summation;
  for ( unsigned int i = 0; i < _num_ions; ++i)
  {
    density_summation += std::exp((*_other_densities[i])[_qp]);
  }

  _conserved_density[_qp] = ((_gas_pressure[_qp] / (_gas_temp[_qp] * 1.38e-23))/ (6.022e23)) - density_summation;
}
