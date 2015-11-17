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

#ifndef REACTANTFIRSTORDERRXN_H
#define REACTANTFIRSTORDERRXN_H

#include "Kernel.h"

// Forward Declaration
class ReactantFirstOrderRxn;

template<>
InputParameters validParams<ReactantFirstOrderRxn>();

class ReactantFirstOrderRxn : public Kernel
{
public:
  ReactantFirstOrderRxn(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
  // The reaction coefficient
  const MaterialProperty<Real> &  _reaction_coeff;
  
};
#endif //REACTANTFIRSTORDERRXN_H
