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

  // Coupled variables

  MooseVariable & _ip_var;
  const VariableValue & _ip;
  unsigned int _ip_id;
  const VariableGradient & _grad_ip;
  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
  const VariableValue & _mean_en;
  unsigned int _mean_en_id;

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _mem;
  const MaterialProperty<Real> & _se_coeff;
  const MaterialProperty<Real> & _muip;
  const MaterialProperty<Real> & _vthermal_em;

  Real _a;
  Real _b;

};

#endif //DCELECTRONBC_H
