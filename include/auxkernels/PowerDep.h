#ifndef POWERDEP_H
#define POWERDEP_H

#include "AuxKernel.h"

class PowerDep;

template<>
InputParameters validParams<PowerDep>();

class PowerDep : public AuxKernel
{
public:
  PowerDep(const InputParameters & parameters);

  virtual ~PowerDep() {}
  virtual Real computeValue();

protected:
  MooseVariable & _density_var;
  VariableValue & _density_log;
  VariableGradient & _grad_density_log;
  VariableGradient & _grad_potential;
  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sgn;
  const MaterialProperty<Real> & _diff;
  bool _art_diff;
  std::string _potential_units;
  RealVectorValue _current;
  Real _voltage_scaling;
};

#endif //POWERDEP_H
