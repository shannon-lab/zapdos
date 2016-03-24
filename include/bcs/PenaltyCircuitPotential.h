#ifndef PENALTYCIRCUITPOTENTIAL_H
#define PENALTYCIRCUITPOTENTIAL_H

#include "IntegratedBC.h"

class PenaltyCircuitPotential;

template<>
InputParameters validParams<PenaltyCircuitPotential>();

/**
 * Boundary condition of a Dirichlet type
 *
 * Sets the value at the node to the value of a Postprocessor
 */
class PenaltyCircuitPotential : public IntegratedBC
{
public:
  PenaltyCircuitPotential(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  /// The value for this BC
  const PostprocessorValue & _current;
  Real _surface_potential;
  std::string _surface;
  Real _current_sign;
  Real _p;
};

#endif /* PENALTYCIRCUITPOTENTIAL_H */
