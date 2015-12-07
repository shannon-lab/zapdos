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

  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sgn;
  const MaterialProperty<Real> & _mu_neighbor;
  const MaterialProperty<Real> & _sgn_neighbor;

  unsigned int _potential_id;
  VariableGradient & _grad_potential;

private:

};

#endif //DGEFIELDADVECTION_H
