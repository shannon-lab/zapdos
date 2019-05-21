//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef EFIELDMAGNITUDESOURCE_H
#define EFIELDMAGNITUDESOURCE_H

#include "Kernel.h"

class EFieldMagnitudeSource;

template <>
InputParameters validParams<EFieldMagnitudeSource>();

class EFieldMagnitudeSource : public Kernel
{
public:
  EFieldMagnitudeSource(const InputParameters & parameters);
  virtual ~EFieldMagnitudeSource();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
};

#endif /* EFIELDMAGNITUDESOURCE_H */
