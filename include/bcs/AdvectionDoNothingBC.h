#ifndef ADVECTIONDONOTHINGBC_H
#define ADVECTIONDONOTHINGBC_H

#include "IntegratedBC.h"

class AdvectionDoNothingBC;

template<>
InputParameters validParams<AdvectionDoNothingBC>();

class AdvectionDoNothingBC : public IntegratedBC
{
public:

  AdvectionDoNothingBC(const std::string & name, InputParameters parameters);

protected:
  // Input Parameters
  Function & _velocity;

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};

#endif //ADVECTIONDONOTHINGBC_H
