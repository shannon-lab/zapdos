#ifndef DGEFIELDADVECTION_H
#define DGEFIELDADVECTION_H

#include "DGKernel.h"
#include <cmath>

//Forward Declarations
class DGEFieldAdvection;

template<>
InputParameters validParams<DGEFieldAdvection>();

class DGEFieldAdvection : public DGKernel
{
public:
	DGEFieldAdvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);
  virtual Real computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar);

  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sgn;
  const MaterialProperty<Real> & _mu_neighbor;
  const MaterialProperty<Real> & _sgn_neighbor;

  MooseVariable & _potential_var;
  unsigned int _potential_id;
  const VariableGradient & _grad_potential;
  const VariableGradient & _grad_potential_neighbor;
  const VariablePhiGradient & _grad_phi_pot;
  const VariablePhiGradient & _grad_phi_neighbor_pot;

private:

};

#endif //DGEFIELDADVECTION_H
