#ifndef PHYSICALIONBC_H
#define PHYSICALIONBC_H

#include "IntegratedBC.h"

class PhysicalIonBC;

template<>
InputParameters validParams<PhysicalIonBC>();

class PhysicalIonBC : public IntegratedBC
{
public:

  PhysicalIonBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
   virtual Real computeQpJacobian();
  //  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Members unique to class  

  Real _a;
  Real _muArp;
  
  // coupled variables

  VariableGradient & _grad_potential;
};

#endif //PHYSICALIONBC_H
