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
  
  // Material Properties

  const MaterialProperty<Real> & _v_thermal_em;
  const MaterialProperty<Real> & _advection_coeff;

  // Coupled variables
  
  unsigned int _potential_id;
  VariableGradient & _grad_potential;  
};

#endif //PHYSICALELECTRONENERGYBC_H
