#ifndef COEFFDIFFUSION_H
#define COEFFDIFFUSION_H

#include "Diffusion.h"

class CoeffDiffusion;

template<>
InputParameters validParams<CoeffDiffusion>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class CoeffDiffusion : public Diffusion
{
public:
  CoeffDiffusion(const InputParameters & parameters);
  virtual ~CoeffDiffusion();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const MaterialProperty<Real> & _diffusivity;
};


#endif /* COEFFDIFFUSION_H */
