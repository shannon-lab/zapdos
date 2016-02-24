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

   const MaterialProperty<Real> & _mumean_en;
   const MaterialProperty<Real> & _d_mumean_en_d_actual_mean_en;
   const MaterialProperty<Real> & _mem;
  Real _a;
  Real _b;

  // Coupled variables
  
  /* const VariableValue & _Arp; */
  /* const VariableGradient & _grad_Arp; */
  const VariableGradient & _grad_potential;  
  unsigned int _potential_id;
  const VariableValue & _em;
  unsigned int _em_id;
};

#endif //PHYSICALELECTRONENERGYBC_H
