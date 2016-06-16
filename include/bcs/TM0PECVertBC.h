#ifndef TM0PECVERTBC_H
#define TM0PECVERTBC_H

#include "IntegratedBC.h"

class TM0PECVertBC;

template<>
InputParameters validParams<TM0PECVertBC>();

class TM0PECVertBC : public IntegratedBC
{
public:

  TM0PECVertBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};

#endif //TM0PECVERTBC_H
