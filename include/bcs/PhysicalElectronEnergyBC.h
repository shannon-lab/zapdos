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
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  // Members unique to class  

  Real _a;
  RealVectorValue _advection_velocity;
  Real _v_thermal_em;
  Real _d_v_thermal_em_d_Te;
  
  // Material Properties

  const MaterialProperty<Real> & _advection_coeff;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _m_em;

  // Coupled variables
  
  unsigned int _potential_id;
  VariableGradient & _grad_potential;  
  unsigned int _em_id;
  VariableValue & _em;
};

#endif //PHYSICALELECTRONENERGYBC_H
