#ifndef PHYSICALELECTRONENERGYBC_H
#define PHYSICALELECTRONENERGYBC_H

#include "IntegratedBC.h"

class PhysicalElectronEnergyBC;

template<>
InputParameters validParams<PhysicalElectronEnergyBC>();

class PhysicalElectronEnergyBC : public IntegratedBC
{
public:

  PhysicalElectronEnergyBC(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  //  virtual Real computeQpJacobian();
  //  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  const Real _se_energy;
  const Real _se_coeff;

  // Members unique to class  

  Real _a;
  //  RealVectorValue _advection_velocity;
  //  Real _v_thermal_em;
  //  Real _d_v_thermal_em_d_Te;
  
  // Material Properties

  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _mem;
  const MaterialProperty<Real> & _muArp;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _muel;
  const MaterialProperty<Real> & _tc;
  const MaterialProperty<Real> & _Vc;
  const MaterialProperty<Real> & _rc;
  const MaterialProperty<Real> & _Tec;
  const MaterialProperty<Real> & _k_boltz;
  const MaterialProperty<Real> & _T_gas;
  // Coupled variables
  
  VariableValue & _Arp;
  VariableGradient & _grad_Arp;
  VariableGradient & _grad_potential;  
  VariableValue & _em;
  /*  unsigned int _Arp_id;
  unsigned int _potential_id;
  unsigned int _em_id;*/
};

#endif //PHYSICALELECTRONENERGYBC_H
