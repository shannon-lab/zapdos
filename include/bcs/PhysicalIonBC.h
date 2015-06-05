#ifndef PHYSICALIONBC_H
#define PHYSICALIONBC_H

#include "IntegratedBC.h"

class PhysicalIonBC;

template<>
InputParameters validParams<PhysicalIonBC>();

class PhysicalIonBC : public IntegratedBC
{
public:

  PhysicalIonBC(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  // Input Parameters

  const Real & _reflection_coeff;

  // Members unique to class  

  Real _a;
  
  // Material Properties

  MaterialProperty<RealVectorValue> & _advection_velocity_ip;
  MaterialProperty<Real> & _muip;
  MaterialProperty<Real> & _v_thermal_ip;
};

#endif //PHYSICALIONBC_H
