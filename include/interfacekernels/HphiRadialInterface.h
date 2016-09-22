#ifndef HPHIRADIALINTERFACE_H
#define HPHIRADIALINTERFACE_H

#include "InterfaceKernel.h"

//Forward Declarations
class HphiRadialInterface;

template<>
InputParameters validParams<HphiRadialInterface>();

/**
 * DG kernel for interfacing diffusion between two variables on adjacent blocks
 */
class HphiRadialInterface : public InterfaceKernel
{
public:
  HphiRadialInterface(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  const MaterialProperty<Real> & _eps_r_neighbor;
  const MaterialProperty<Real> & _eps_r;
};

#endif
