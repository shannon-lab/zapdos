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

  /* const Real & _se_coeff; */

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _mem;
  const MaterialProperty<Real> & _se_coeff;
  const MaterialProperty<Real> & _muip;

  Real _a;
  Real _b;

  // Coupled variables
  
  VariableValue & _Arp;
  unsigned int _Arp_id;
  VariableGradient & _grad_Arp;
  VariableGradient & _grad_potential;
  unsigned int _potential_id;
};

#endif //PHYSICALELECTRONBC_H
