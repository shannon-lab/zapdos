#ifndef ELECTRONARTDIFFUSIVEFLUX_H
#define ELECTRONARTDIFFUSIVEFLUX_H

#include "AuxKernel.h"

class ElectronArtDiffusiveFlux;

template<>
InputParameters validParams<ElectronArtDiffusiveFlux>();

class ElectronArtDiffusiveFlux : public AuxKernel
{
public:
  ElectronArtDiffusiveFlux(const InputParameters & parameters);
  
  virtual ~ElectronArtDiffusiveFlux() {}
  
protected:

  virtual Real computeValue();
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _diffem;
  Real _alpha;
  Real _Pe;
  Real _vd_mag;
  Real _delta;
  VariableGradient & _grad_potential;
  VariableValue & _em;
  VariableGradient & _grad_em;
};

#endif //ELECTRONARTDIFFUSIVEFLUX_H
