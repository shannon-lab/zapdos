#ifndef DCELECTRONBC_H
#define DCELECTRONBC_H

#include "IntegratedBC.h"

class DCElectronBC;

template<>
InputParameters validParams<DCElectronBC>();

class DCElectronBC : public IntegratedBC
{
public:

  DCElectronBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  /* const Real & _se_coeff; */

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _mem;
  const MaterialProperty<Real> & _se_coeff;
  const MaterialProperty<Real> & _muip;
  const MaterialProperty<Real> & _vthermal_em;

  Real _a;
  Real _b;

  // Coupled variables
  
  VariableValue & _Arp;
  unsigned int _Arp_id;
  VariableGradient & _grad_Arp;
  VariableGradient & _grad_potential;
  unsigned int _potential_id;
  VariableValue & _mean_en;
  unsigned int _mean_en_id;
};

#endif //DCELECTRONBC_H
