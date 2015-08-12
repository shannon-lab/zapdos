#ifndef DCIONBC_H
#define DCIONBC_H

#include "IntegratedBC.h"

class DCIonBC;

template<>
InputParameters validParams<DCIonBC>();

class DCIonBC : public IntegratedBC
{
public:

  DCIonBC(const std::string & name, InputParameters parameters);

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

#endif //DCIONBC_H
