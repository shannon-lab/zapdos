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
  TimeDerivativeSUPG(const InputParameters & parameters);

  virtual void computeJacobian();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  bool _lumping;
  const bool & _crosswind;
  const Real & _epsilon;

  // Material properties

  const MaterialProperty<Real> & _tau;
  //  const MaterialProperty<RealVectorValue> & _velocity;  
  const MaterialProperty<RealVectorValue> & _velocity; 
  const MaterialProperty<Real> & _diffusivity;

  // Kernel specific members

  //  RealVectorValue _velocity;
  RealVectorValue _velocity_h;
  RealVectorValue _d_velocity_h_d_uj;
  Real _peclet_num_h;
  Real _alpha_h;
  Real _tau_h;
  Real _sigma;

};

#endif //TIMEDERIVATIVESUPG_H
