#ifndef IONSRCTERM_H
#define IONSRCTERM_H

#include "AuxKernel.h"

//Forward Declarations
class IonSrcTerm;

template<>
InputParameters validParams<IonSrcTerm>();

/**
 * Constant auxiliary value
 */
class IonSrcTerm : public AuxKernel
{
public:
  IonSrcTerm(const InputParameters & parameters);

  virtual ~IonSrcTerm() {}

protected:

  virtual Real computeValue();

  // Material Properties
  
  const MaterialProperty<Real> & _potential_mult;
  const MaterialProperty<Real> & _velocity_coeff;

  // Coupled variables
  
  const VariableValue & _electron_density;
  const VariableGradient & _grad_potential;
};

#endif //IONSRCTERM_H
