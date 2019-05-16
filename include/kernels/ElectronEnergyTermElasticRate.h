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

#ifndef ELECTRONENERGYTERMELASTICRATE_H
#define ELECTRONENERGYTERMELASTICRATE_H

#include "Kernel.h"

class ElectronEnergyTermElasticRate;

template <>
InputParameters validParams<ElectronEnergyTermElasticRate>();

class ElectronEnergyTermElasticRate : public Kernel
{
public:
  ElectronEnergyTermElasticRate(const InputParameters & parameters);
  virtual ~ElectronEnergyTermElasticRate();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  const MaterialProperty<Real> & _rate_coefficient;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;

  const VariableValue & _electron;
  const VariableValue & _target;
  unsigned int _electron_id;
  unsigned int _target_id;

  const MaterialProperty<Real> & _massIncident;
  const MaterialProperty<Real> & _massTarget;
};

#endif /* ELECTRONENERGYTERMELASTICRATE_H */
