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

#ifndef NEUMANNCIRCUITVOLTAGE_H
#define NEUMANNCIRCUITVOLTAGE_H

#include "IntegratedBC.h"
#include "ProvideMobility.h"

//Forward Declarations
class NeumannCircuitVoltage;
class Function;

template<>
InputParameters validParams<NeumannCircuitVoltage>();

/**
 * Boundary condition of a Neumann style whose value is computed by a user-defined function
 */
class NeumannCircuitVoltage : public IntegratedBC
{
public:
  NeumannCircuitVoltage(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  /// The function being used for setting the value
  Function & _V_bat;
  const ProvideMobility & _data;
VariableValue & _ip;
const MaterialProperty<Real> & _se_coeff;
const MaterialProperty<Real> & _muip;
};

#endif // NEUMANNCIRCUITVOLTAGE_H
