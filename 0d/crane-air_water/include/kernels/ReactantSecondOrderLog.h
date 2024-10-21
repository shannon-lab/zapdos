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
class ReactantSecondOrderLog;

template <>
InputParameters validParams<ReactantSecondOrderLog>();

class ReactantSecondOrderLog : public Kernel
{
public:
  ReactantSecondOrderLog(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // The reaction coefficient
  // MooseVariable & _coupled_var_A;
  const MaterialProperty<Real> & _reaction_coeff;
  const VariableValue & _v;
  unsigned int _v_id;
  // const MaterialProperty<Real> & _n_gas;
  Real _stoichiometric_coeff;
  bool _v_eq_u;
};
