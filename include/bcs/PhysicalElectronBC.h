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
  //  virtual Real computeQpJacobian();
  //  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  const Real & _reflection_coeff;
  const Real & _se_coeff;

  // Members unique to class  

  Real _a;
  //  Real _d_vthermal_em_d_Te;

  // Material Properties

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _muArp;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _mem;
  const MaterialProperty<Real> & _tc;
  const MaterialProperty<Real> & _Vc;
  const MaterialProperty<Real> & _rc;
  //  const MaterialProperty<Real> & _D_Arp;

  // Coupled variables
  
  VariableValue & _Arp;
  VariableGradient & _grad_Arp;
  VariableValue & _Te;
  VariableGradient & _grad_potential;
  /*  unsigned int _Arp_id;
  unsigned int _potential_id;
  unsigned int _Te_id;*/
};

#endif //PHYSICALELECTRONBC_H
