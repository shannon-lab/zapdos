#ifndef DGTOTFLUXCONTPOTDRIVEN_H
#define DGTOTFLUXCONTPOTDRIVEN_H

#include "DGInterface.h"

//Forward Declarations
class DGTotFluxContPotDriven;

template<>
InputParameters validParams<DGTotFluxContPotDriven>();

/**
 * DG kernel for diffusion
 *
 * General DG kernel that this class can handle is:
 * \f$ { \nabla u * n_e} [v] + epsilon { \nabla v * n_e } [u] + (sigma / |e| * [u][v]) \f$
 *
 * \f$ [a] = [ a_1 - a_2 ] \f$
 * \f$ {a} = 0.5 * (a_1 + a_2) \f$
 *
 */
class DGTotFluxContPotDriven : public DGInterface
{
public:
  DGTotFluxContPotDriven(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  Real _epsilon;
  Real _sigma;
  Real _D;
  Real _D_neighbor;
};

#endif
