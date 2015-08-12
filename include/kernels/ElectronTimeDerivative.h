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

#ifndef ELECTRONTIMEDERIVATIVE_H
#define ELECTRONTIMEDERIVATIVE_H

#include "TimeKernel.h"

// Forward Declaration
class ElectronTimeDerivative;

template<>
InputParameters validParams<ElectronTimeDerivative>();

class ElectronTimeDerivative : public TimeKernel
{
public:
  ElectronTimeDerivative(const InputParameters & parameters);

  /* virtual void computeJacobian(); */

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  /* virtual Real computeQpOffDiagJacobian(unsigned int jvar); */

  bool _lumping;
};

#endif //ELECTRONTIMEDERIVATIVE_H
