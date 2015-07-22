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
  virtual Real computeQpJacobian();
  //  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  /* const Real & _se_coeff; */

  // Members unique to class  

  Real _a;
  Real _muem;

  // Coupled variables
  
  /* VariableValue & _Arp; */
  /* VariableGradient & _grad_Arp; */
  /* VariableValue & _Te; */
  VariableGradient & _grad_potential;
};

#endif //PHYSICALELECTRONBC_H
