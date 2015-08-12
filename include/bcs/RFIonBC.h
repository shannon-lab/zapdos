#ifndef RFIONBC_H
#define RFIONBC_H

#include "IntegratedBC.h"

class RFIonBC;

template<>
InputParameters validParams<RFIonBC>();

class RFIonBC : public IntegratedBC
{
public:

  RFIonBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
   virtual Real computeQpJacobian();
   virtual Real computeQpOffDiagJacobian(unsigned int jvar);

   const MaterialProperty<Real> & _muip;
   const MaterialProperty<Real> & _vthermal_ip;
   Real _a;
  
  // coupled variables

  VariableGradient & _grad_potential;
  unsigned int _potential_id;
};

#endif //RFIONBC_H
