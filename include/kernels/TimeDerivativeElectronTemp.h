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

#ifndef TIMEDERIVATIVEELECTRONTEMP_H
#define TIMEDERIVATIVEELECTRONTEMP_H

#include "TimeKernel.h"

// Forward Declaration
class TimeDerivativeElectronTemp;

template<>
InputParameters validParams<TimeDerivativeElectronTemp>();

class TimeDerivativeElectronTemp : public TimeKernel
{
public:
  TimeDerivativeElectronTemp(const InputParameters & parameters);

  /* virtual void computeJacobian(); */

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  /* virtual Real computeQpOffDiagJacobian(unsigned int jvar); */

  bool _lumping;
  /* VariableValue & _em; */
  /* VariableValue & _em_dot; */
  /* VariableValue & _dem_dot; */
  /* unsigned int _em_id; */
};

#endif //TIMEDERIVATIVEELECTRONTEMP_H
