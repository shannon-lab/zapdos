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

#ifndef TIMEDERIVATIVESUPG_H
#define TIMEDERIVATIVESUPG_H

#include "TimeKernel.h"

// Forward Declaration
class TimeDerivativeSUPG;

template<>
InputParameters validParams<TimeDerivativeSUPG>();

class TimeDerivativeSUPG : public TimeKernel
{
public:
  TimeDerivativeSUPG(const std::string & name, InputParameters parameters);

  virtual void computeJacobian();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  bool _lumping;

  // Material properties

  MaterialProperty<Real> & _alpha;
  //  MaterialProperty<RealVectorValue> & _velocity;  
  MaterialProperty<RealVectorValue> & _velocity_norm;  

  // Kernel specific members

  //  RealVectorValue _velocity;

};

#endif //TIMEDERIVATIVESUPG_H
