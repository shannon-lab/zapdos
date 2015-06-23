#ifndef PHYSICALELECTRONBC_H
#define PHYSICALELECTRONBC_H

#include "IntegratedBC.h"

class PhysicalElectronBC;

template<>
InputParameters validParams<PhysicalElectronBC>();

class PhysicalElectronBC : public IntegratedBC
{
public:

  PhysicalElectronBC(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  const Real & _reflection_coeff;
  const Real & _se_coeff;

  // Members unique to class  

  Real _a;
  Real _d_vthermal_em_d_Te;

  // Material Properties

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _muip;
  const MaterialProperty<Real> & _D_ip;
  const MaterialProperty<Real> & _k_boltz;
  const MaterialProperty<Real> & _m_em;

  // Coupled variables
  
  VariableValue & _ip;
  unsigned int _ip_id;
  VariableGradient & _grad_ip;
  VariableValue & _Te;
  unsigned int _Te_id;
  VariableGradient & _grad_potential;
  unsigned int _potential_id;
};

#endif //PHYSICALELECTRONBC_H
