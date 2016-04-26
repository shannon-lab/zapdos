#ifndef CIRCUITDIRICHLETPOTENTIAL_H
#define CIRCUITDIRICHLETPOTENTIAL_H

#include "NodalBC.h"

class CircuitDirichletPotential;
class Function;

template<>
InputParameters validParams<CircuitDirichletPotential>();

/**
 * Boundary condition of a Dirichlet type
 *
 * Sets the value at the node to the value of a Postprocessor
 */
class CircuitDirichletPotential : public NodalBC
{
public:
  CircuitDirichletPotential(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  /// The value for this BC
  const PostprocessorValue & _current;
  Function & _surface_potential;
  std::string _surface;
  Real _resist;
  Real _coulomb_charge;
  Real _N_A;
  std::string _potential_units;
  Real _r_units;
  bool _convert_moles;
  Real _A;

  Real _current_sign;
  Real _voltage_scaling;
};

#endif /* CIRCUITDIRICHLETPOTENTIAL_H */
