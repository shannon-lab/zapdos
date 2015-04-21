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
  AlphaTimesHSize(const std::string & name, InputParameters parameters);

  virtual ~AlphaTimesHSize() {}

protected:

  virtual Real computeValue();

  // Material Properties
  
  MaterialProperty<Real> & _potential_mult;

  // Coupled variables
  
  VariableGradient & _grad_potential;
};

#endif //ALPHATIMESHSIZE_H
