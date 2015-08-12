//****************************************************************/
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

#ifndef VELOCITYH_H
#define VELOCITYH_H

#include "AuxKernel.h"

//Forward Declarations
class VelocityH;

template<>
InputParameters validParams<VelocityH>();

/**
 * Constant auxiliary value
 */
class VelocityH : public AuxKernel
{
public:
  VelocityH(const InputParameters & parameters);

  virtual ~VelocityH() {}

protected:
  /**
   * AuxKernels MUST override computeValue.  computeValue() is called on
   * every quadrature point.  For Nodal Auxiliary variables those quadrature
   * points coincide with the nodes.
   */
  virtual Real computeValue();
  
  //int _component;

  // Coupling variables

  VariableGradient & _grad_some_var;
  VariableValue & _some_var;
  
  // Material properties

  const MaterialProperty<Real> & _tau; 
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

#endif //VELOCITYH_H
