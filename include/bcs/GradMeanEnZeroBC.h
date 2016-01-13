#ifndef GRADMEANENZEROBC_H
#define GRADMEANENZEROBC_H

#include "IntegratedBC.h"

class GradMeanEnZeroBC;

template<>
InputParameters validParams<GradMeanEnZeroBC>();

class GradMeanEnZeroBC : public IntegratedBC
{
public:

  GradMeanEnZeroBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
   virtual Real computeQpJacobian();
   virtual Real computeQpOffDiagJacobian(unsigned int jvar);

   const MaterialProperty<Real> & _mu;
   const MaterialProperty<Real> & _sgn;
   const MaterialProperty<Real> & _diff;
   /* const MaterialProperty<Real> & _vthermal_ip; */
   Real _a;

  // coupled variables

  VariableGradient & _grad_potential;
  unsigned int _potential_id;
  VariableGradient & _grad_em;
  unsigned int _em_id;
};

#endif //GRADMEANENZEROBC_H
