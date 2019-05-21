//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef POTENTIALDRIFTOUTFLOWBC_H
#define POTENTIALDRIFTOUTFLOWBC_H

#include "IntegratedBC.h"

class PotentialDriftOutflowBC;

template <>
InputParameters validParams<PotentialDriftOutflowBC>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class PotentialDriftOutflowBC : public IntegratedBC
{
public:
  PotentialDriftOutflowBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  int _charge_sign;
  unsigned int _potential_id;
  const VariableGradient & _grad_potential;
};

#endif /* POTENTIALDRIFTOUTFLOWBC_H */
