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
class ReactantFirstOrder;

template <>
InputParameters validParams<ReactantFirstOrder>();

class ReactantFirstOrder : public Kernel
{
public:
  ReactantFirstOrder(const InputParameters & parameters);

protected:
  Real computeQpResidual() override;
  Real computeQpJacobian() override;
  Real computeQpOffDiagJacobian(unsigned int) override;

  // The reaction coefficient
  // MooseVariable & _coupled_var_A;
  const MaterialProperty<Real> & _reaction_coeff;
  // const MaterialProperty<Real> & _n_gas;
  Real _stoichiometric_coeff;
};
