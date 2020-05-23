//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "InterfaceKernel.h"

/**
 * DG kernel for interfacing diffusion between two variables on adjacent blocks
 */
class InterfacePotential : public InterfaceKernel
{
public:
  static InputParameters validParams();

  InterfacePotential(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type) override;
  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;
  virtual Real computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar) override;

  const Real _r_units;
  const MaterialProperty<Real> & _D;
  const MaterialProperty<Real> & _D_neighbor;
  // const VariableValue & _sigma;
  const MaterialProperty<Real> & _sigma;
  const MaterialProperty<Real> & _d_sigma_d_potential;
  const MaterialProperty<Real> & _d_sigma_d_em;
  const MaterialProperty<Real> & _d_sigma_d_mean_en;
  const MaterialProperty<std::vector<Real>> & _d_sigma_d_ion;

  unsigned int _em_id;
  unsigned int _mean_en_id;
  std::vector<unsigned int> _ion_id;
  unsigned int _num_ions;
  unsigned int _ip_index;
  std::vector<unsigned int>::iterator _iter;
};
