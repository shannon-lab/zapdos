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
class ElectronReactantSecondOrderLog;

template <>
InputParameters validParams<ElectronReactantSecondOrderLog>();

class ElectronReactantSecondOrderLog : public Kernel
{
public:
  ElectronReactantSecondOrderLog(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // The reaction coefficient
  // MooseVariable & _coupled_var_A;
  const MaterialProperty<Real> & _reaction_coeff;
  const MaterialProperty<Real> & _d_k_d_en;
  const VariableValue & _v;
  const VariableValue & _energy;
  unsigned int _v_id;
  unsigned int _energy_id;
  const MaterialProperty<Real> & _n_gas;
  Real _stoichiometric_coeff;
  bool _v_eq_electron;
};
