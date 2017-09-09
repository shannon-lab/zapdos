#ifndef DRIFTDIFFUSIONUSERDONOTHINGBC_H
#define DRIFTDIFFUSIONUSERDONOTHINGBC_H

#include "DriftDiffusionDoNothingBC.h"

class DriftDiffusionUserDoNothingBC;

template <>
InputParameters validParams<DriftDiffusionUserDoNothingBC>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class DriftDiffusionUserDoNothingBC : public DriftDiffusionDoNothingBC
{
public:
  DriftDiffusionUserDoNothingBC(const InputParameters & parameters);

protected:
  MooseArray<Real> _mu;
  MooseArray<Real> _sign;
  MooseArray<Real> _diffusivity;
};

#endif /* DRIFTDIFFUSIONUSERDONOTHINGBC_H */
