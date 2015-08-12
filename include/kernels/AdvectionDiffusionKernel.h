#ifndef ADVECTIONDIFFUSIONKERNEL_H
#define ADVECTIONDIFFUSIONKERNEL_H

#include "Kernel.h"

class AdvectionDiffusionKernel;

template<>
InputParameters validParams<AdvectionDiffusionKernel>();

class AdvectionDiffusionKernel : public Kernel
{
  public:
    AdvectionDiffusionKernel(const InputParameters & parameters);
    virtual ~AdvectionDiffusionKernel();

  protected:
    
    virtual Real computeQpResidual();
    virtual Real computeQpJacobian();
    RealVectorValue _a;
    Real _diff;
    Real _alpha;
    Real _Pe;
    Real _vd_mag;
    Real _delta;
};

#endif /* ADVECTIONDIFFUSIONKERNEL_H */



