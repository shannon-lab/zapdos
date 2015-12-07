#ifndef OUTFLOWBC_H
#define OUTFLOWBC_H

#include "IntegratedBC.h"

class OutflowBC;

template<>
InputParameters validParams<OutflowBC>();

class OutflowBC : public IntegratedBC
{
public:

  OutflowBC(const InputParameters & parameters);

protected:
  // Input Parameters
  Real _vx;
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};

#endif //OUTFLOWBC_H
