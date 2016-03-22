#ifndef CIRCUITDIRICHLETPOTENTIAL_H
#define CIRCUITDIRICHLETPOTENTIAL_H

#include "NodalBC.h"

class CircuitDirichletPotential;

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

  /// The value for this BC
  const PostprocessorValue & _current;
  Real _surface_potential;
  std::string _surface;
  Real _current_sign;
};

#endif /* CIRCUITDIRICHLETPOTENTIAL_H */
