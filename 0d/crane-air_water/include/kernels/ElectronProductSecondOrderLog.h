/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#pragma once

#include "Kernel.h"

// Forward Declaration
class ElectronProductSecondOrderLog;

template <>
InputParameters validParams<ElectronProductSecondOrderLog>();

class ElectronProductSecondOrderLog : public Kernel
{
public:
  ElectronProductSecondOrderLog(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // MooseVariable & _coupled_var_A;
  // MooseVariable & _coupled_var_B;
  const VariableValue & _electron;
  const VariableValue & _target;
  const VariableValue & _energy;
  unsigned int _electron_id;
  unsigned int _target_id;
  unsigned int _energy_id;
  const MaterialProperty<Real> & _n_gas;

  // The reaction coefficient
  const MaterialProperty<Real> & _reaction_coeff;
  const MaterialProperty<Real> & _d_k_d_en;
  Real _stoichiometric_coeff;
  bool _electron_eq_u;
  bool _target_eq_u;
  bool _target_coupled;
};
