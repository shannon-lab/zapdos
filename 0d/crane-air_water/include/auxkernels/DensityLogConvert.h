#pragma once

#include "AuxKernel.h"

class DensityLogConvert;

template <>
InputParameters validParams<DensityLogConvert>();

class DensityLogConvert : public AuxKernel
{
public:
  DensityLogConvert(const InputParameters & parameters);

  virtual ~DensityLogConvert() {}

protected:
  virtual Real computeValue() override;

  const VariableValue & _density_log;
  bool _convert_moles;
  // const MaterialProperty<Real> & _N_A;
};
