#ifndef AXISYMMETRICCURLZ_H
#define AXISYMMETRICCURLZ_H

#include "Kernel.h"

class AxisymmetricCurlZ;

template<>
InputParameters validParams<AxisymmetricCurlZ>();

class AxisymmetricCurlZ : public Kernel
{
public:
  AxisymmetricCurlZ(const InputParameters & parameters);
  virtual ~AxisymmetricCurlZ();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

};


#endif /* AXISYMMETRICCURLZ_H */
