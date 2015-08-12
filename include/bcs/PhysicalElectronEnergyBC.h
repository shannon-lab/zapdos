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
  //  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  /* const Real _se_energy; */
  /* const Real _se_coeff; */

  // Members unique to class  

  Real _a;
  Real _b;
  Real _muel;
  Real _e;
  Real _m_el;

  // Coupled variables
  
  /* VariableValue & _Arp; */
  /* VariableGradient & _grad_Arp; */
  VariableGradient & _grad_potential;  
  /* VariableValue & _em; */
};

#endif //PHYSICALELECTRONENERGYBC_H
