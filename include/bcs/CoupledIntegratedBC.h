#ifndef COUPLEDINTEGRATEDBC_H
#define COUPLEDINTEGRATEDBC_H

#include "IntegratedBC.h"

class CoupledIntegratedBC;

template<>
InputParameters validParams<CoupledIntegratedBC>();

class CoupledIntegratedBC : public IntegratedBC
{
public:

  CoupledIntegratedBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled variables

  VariableGradient & _grad_coupled_var;
  unsigned int _coupled_var_id;
};

#endif //COUPLEDINTEGRATEDBC_H
