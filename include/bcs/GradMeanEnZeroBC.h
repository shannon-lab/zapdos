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

   const MaterialProperty<Real> & _mumean_en;
   const MaterialProperty<Real> & _d_mumean_en_d_actual_mean_en;
   const MaterialProperty<Real> & _sgnmean_en;
   const MaterialProperty<Real> & _diffmean_en;
   const MaterialProperty<Real> & _d_diffmean_en_d_actual_mean_en;
   /* const MaterialProperty<Real> & _vthermal_ip; */
   Real _a;

  // coupled variables

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
  const VariableGradient & _grad_em;
  const VariableValue & _em;
  unsigned int _em_id;

  Real _actual_mean_en;
};

#endif //GRADMEANENZEROBC_H
