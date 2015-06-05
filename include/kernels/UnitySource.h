#ifndef UNITYSOURCE_H
#define UNITYSOURCE_H

#include "Kernel.h"

class UnitySource;

template<>
InputParameters validParams<UnitySource>();

class UnitySource : public Kernel
{
 public:
  UnitySource(const std::string & name, InputParameters parameters);
  virtual ~UnitySource();

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};

#endif /* UNITYSOURCE_H */
