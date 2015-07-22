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
  //  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  /* const Real _se_energy; */
  /* const Real _se_coeff; */

  // Members unique to class  

  Real _a;
  Real _muel;

  // Coupled variables
  
  /* VariableValue & _Arp; */
  /* VariableGradient & _grad_Arp; */
  VariableGradient & _grad_potential;  
  VariableValue & _em;
};

#endif //PHYSICALELECTRONENERGYBC_H
