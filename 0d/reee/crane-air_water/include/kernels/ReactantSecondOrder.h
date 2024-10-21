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
class ReactantSecondOrder;

template <>
InputParameters validParams<ReactantSecondOrder>();

class ReactantSecondOrder : public Kernel
{
public:
  ReactantSecondOrder(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // The reaction coefficient
  const MaterialProperty<Real> & _reaction_coeff;
  const VariableValue & _v;
  unsigned int _v_id;
  Real _stoichiometric_coeff;
  bool _v_eq_u;

};
