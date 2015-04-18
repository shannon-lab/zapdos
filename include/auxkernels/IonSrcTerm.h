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
  IonSrcTerm(const std::string & name, InputParameters parameters);

  virtual ~IonSrcTerm() {}

protected:

  virtual Real computeValue();

  // Material Properties
  
  MaterialProperty<Real> & _potential_mult;
  MaterialProperty<Real> & _velocity_coeff;

  // Coupled variables
  
  VariableValue & _electron_density;
  VariableGradient & _grad_potential;
};

#endif //IONSRCTERM_H
