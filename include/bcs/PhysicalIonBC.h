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
  //  virtual Real computeQpJacobian();
  //  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  const Real & _reflection_coeff;

  // Members unique to class  

  Real _a;
  
  // Material Properties

  const MaterialProperty<Real> & _muArp;
  const MaterialProperty<Real> & _k_boltz;
  const MaterialProperty<Real> & _T_gas;
  const MaterialProperty<Real> & _mArp;
  const MaterialProperty<Real> & _tc;
  const MaterialProperty<Real> & _Vc;
  const MaterialProperty<Real> & _rc;

  // coupled variables

  VariableGradient & _grad_potential;
  //  unsigned int _potential_id;
};

#endif //PHYSICALIONBC_H
