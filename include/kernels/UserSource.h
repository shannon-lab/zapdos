#ifndef USERSOURCE_H
#define USERSOURCE_H

#include "Kernel.h"

class UserSource;

template <>
InputParameters validParams<UserSource>();

class UserSource : public Kernel
{
public:
  UserSource(const InputParameters & parameters);
  virtual ~UserSource();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _source;
};

#endif /* USERSOURCE_H */
