#ifndef ALPHATIMESHSIZE_H
#define ALPHATIMESHSIZE_H

#include "AuxKernel.h"

//Forward Declarations
class AlphaTimesHSize;

template<>
InputParameters validParams<AlphaTimesHSize>();

/**
 * Constant auxiliary value
 */
class AlphaTimesHSize : public AuxKernel
{
public:
  AlphaTimesHSize(const InputParameters & parameters);

  virtual ~AlphaTimesHSize() {}

protected:

  virtual Real computeValue();

  // Material Properties
  
  const MaterialProperty<Real> & _potential_mult;

  // Coupled variables
  
  VariableGradient & _grad_potential;
};

#endif //ALPHATIMESHSIZE_H
