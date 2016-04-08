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

#ifndef ELECTRONENERGYLOSSFROMELASTIC_H
#define ELECTRONENERGYLOSSFROMELASTIC_H

#include "Kernel.h"

class ElectronEnergyLossFromElastic;

template<>
InputParameters validParams<ElectronEnergyLossFromElastic>();

class ElectronEnergyLossFromElastic : public Kernel
{
public:
  ElectronEnergyLossFromElastic(const InputParameters & parameters);
  virtual ~ElectronEnergyLossFromElastic();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _alpha_iz;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;
  const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _mGas;
  const MaterialProperty<Real> & _alpha_el;
  const MaterialProperty<Real> & _d_el_d_actual_mean_en;

  const VariableGradient & _grad_potential;
  const VariableValue & _em;
  const VariableGradient & _grad_em;
  unsigned int _potential_id;
  unsigned int _em_id;
};


#endif /* ELECTRONENERGYLOSSFROMELASTIC_H */
