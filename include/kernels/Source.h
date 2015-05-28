#ifndef SOURCE_H
#define SOURCE_H

#include "Kernel.h"

class Source;

template<>
InputParameters validParams<Source>();

class Source : public Kernel
{
 public:
  Source(const std::string & name, InputParameters parameters);
  virtual ~Source();

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  // Material properties

  MaterialProperty<Real> & _source;
  MaterialProperty<Real> & _jacobian;
};

#endif /* SOURCE_H */
