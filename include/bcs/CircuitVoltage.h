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

#ifndef CIRCUITVOLTAGE_H
#define CIRCUITVOLTAGE_H

#include "NodalBC.h"

//Forward Declarations
class CircuitVoltage;
class Function;

template<>
InputParameters validParams<CircuitVoltage>();

/**
 * Defines a boundary condition that forces the value to be a user specified
 * function at the boundary.
 */
class CircuitVoltage : public NodalBC
{
public:
  CircuitVoltage(const std::string & name, InputParameters parameters);

protected:
  /**
   * Evaluate the function at the current quadrature point and timestep.
   */
  Real f();

  /**
   * returns (u - the function)
   */
  virtual Real computeQpResidual();

  /// The function being used for evaluation
  Function & _func;
  VariableValue & _ip;
  VariableGradient & _grad_ip;
  const MaterialProperty<Real> & _muip;
  const MaterialProperty<Real> & _diffip;
  const MaterialProperty<Real> & _electrode_area;
  const MaterialProperty<Real> & _ballast_resist;
  const MaterialProperty<Real> & _e;
};

#endif //CIRCUITVOLTAGE_H
