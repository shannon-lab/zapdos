#ifndef DRIFTDIFFUSIONUSER_H
#define DRIFTDIFFUSIONUSER_H

#include "DriftDiffusion.h"

class DriftDiffusionUser;

template<>
InputParameters validParams<DriftDiffusionUser>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class DriftDiffusionUser : public DriftDiffusion
{
public:
  DriftDiffusionUser(const InputParameters & parameters);

protected:
  MooseArray<Real> _mu;
  MooseArray<Real> _sign;
  MooseArray<Real> _diffusivity;
};


#endif /* DRIFTDIFFUSIONUSER_H */
