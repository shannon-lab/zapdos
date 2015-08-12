#ifndef SOMETIMESADVECTIONBC_H
#define SOMETIMESADVECTIONBC_H

#include "IntegratedBC.h"

class SometimesAdvectionBC;

template<>
InputParameters validParams<SometimesAdvectionBC>();

class SometimesAdvectionBC : public IntegratedBC
{
public:

  SometimesAdvectionBC(const InputParameters & parameters);

protected:
  // Input Parameters
  Function & _velocity;

  Real _a;

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};

#endif //SOMETIMESADVECTIONBC_H
