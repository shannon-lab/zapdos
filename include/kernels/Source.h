#ifndef SOURCE_H
#define SOURCE_H

#include "Kernel.h"

class Source;

template<>
InputParameters validParams<Source>();

class Source : public Kernel
{
 public:
  Source(const InputParameters & parameters);
  virtual ~Source();

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  // Material properties

  const MaterialProperty<Real> & _source;
  const MaterialProperty<Real> & _jacobian;
};

#endif /* SOURCE_H */
