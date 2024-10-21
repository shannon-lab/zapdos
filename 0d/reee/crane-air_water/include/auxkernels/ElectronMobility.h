#pragma once

#include "AuxScalarKernel.h"
#include "SplineInterpolation.h"

// Forward Declarations
class ElectronMobility;

template <>
InputParameters validParams<ElectronMobility>();

class ElectronMobility : public AuxScalarKernel
{
public:
  ElectronMobility(const InputParameters & parameters);
  virtual ~ElectronMobility();

protected:
  virtual Real computeValue();

  SplineInterpolation _mobility;

  const VariableValue & _reduced_field;
};
