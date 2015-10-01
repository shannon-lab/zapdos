#include "CoupledIntegratedBC.h"

template<>
InputParameters validParams<CoupledIntegratedBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("coupled_var","The interface variable to couple in.");
  return params;
}

CoupledIntegratedBC::CoupledIntegratedBC(const InputParameters & parameters) :
  IntegratedBC(parameters),
  _grad_coupled_var(coupledGradient("coupled_var")),
  _coupled_var_id(coupled("coupled_var"))
{}

Real
CoupledIntegratedBC::computeQpResidual()
{
  return _test[_i][_qp]*_grad_coupled_var[_qp]*_normals[_qp];
}

Real
CoupledIntegratedBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _coupled_var_id)
    return _test[_i][_qp]*_grad_phi[_j][_qp]*_normals[_qp];
  else
    return 0.0;
}


