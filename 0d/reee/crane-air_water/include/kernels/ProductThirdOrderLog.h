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
class ProductThirdOrderLog;

template <>
InputParameters validParams<ProductThirdOrderLog>();

class ProductThirdOrderLog : public Kernel
{
public:
  ProductThirdOrderLog(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const VariableValue & _v;
  const VariableValue & _w;
  const VariableValue & _x;
  unsigned int _v_id;
  unsigned int _w_id;
  unsigned int _x_id;
  bool _v_eq_u;
  bool _w_eq_u;
  bool _x_eq_u;

  const MaterialProperty<Real> & _reaction_coeff;
  Real _stoichiometric_coeff;
};
