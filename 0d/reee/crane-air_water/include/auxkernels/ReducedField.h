#pragma once

#include "AuxScalarKernel.h"
#include "SplineInterpolation.h"

// Forward Declarations
class ReducedField;

template <>
InputParameters validParams<ReducedField>();

class ReducedField : public AuxScalarKernel
{
public:
  ReducedField(const InputParameters & parameters);
  virtual ~ReducedField();

protected:
  virtual Real computeValue();

  const VariableValue & _mobility;
};
