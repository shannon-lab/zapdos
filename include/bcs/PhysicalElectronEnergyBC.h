#ifndef PHYSICALELECTRONENERGYBC_H
#define PHYSICALELECTRONENERGYBC_H

#include "IntegratedBC.h"

class PhysicalElectronEnergyBC;

template<>
InputParameters validParams<PhysicalElectronEnergyBC>();

class PhysicalElectronEnergyBC : public IntegratedBC
{
public:

  PhysicalElectronEnergyBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
   virtual Real computeQpJacobian();
   virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  /* const Real _se_energy; */
  /* const Real _se_coeff; */

   const MaterialProperty<Real> & _muel;
   const MaterialProperty<Real> & _mem;
  Real _a;
  Real _b;

  // Coupled variables
  
  /* VariableValue & _Arp; */
  /* VariableGradient & _grad_Arp; */
  VariableGradient & _grad_potential;  
  unsigned int _potential_id;
  /* VariableValue & _em; */
};

#endif //PHYSICALELECTRONENERGYBC_H
