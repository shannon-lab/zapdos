#include "PhysicalIonBC.h"

template<>
InputParameters validParams<PhysicalIonBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredCoupledVar("potential","The electrical potential");
    return params;
}

PhysicalIonBC::PhysicalIonBC(const InputParameters & parameters) :
  IntegratedBC(parameters),

  // Variables unique to class

  _a(0.0),
  _muArp(3.42/1e2),

  // coupled variables

  _grad_potential(coupledGradient("potential"))
{}

Real
PhysicalIonBC::computeQpResidual()
{
  if ( _normals[_qp]*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  return _test[_i][_qp]*(_a*_muArp*-_grad_potential[_qp]*std::exp(_u[_qp])*_normals[_qp]);
}

Real
PhysicalIonBC::computeQpJacobian()
{
  if ( _normals[_qp]*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  return _test[_i][_qp]*(_a*_muArp*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]*_normals[_qp]);
}

// Real
// PhysicalIonBC::computeQpOffDiagJacobian(unsigned int jvar)
// {
//   if (jvar == _potential_id) {
//     if ( _normals[_qp]*1.0*-_grad_potential[_qp] > 0.0) {
//       _a = 1.0;
//     }
//     else {
//       _a = 0.0;
//     }
//     return _test[_i][_qp]*(_a*_muArp[_qp]*-_grad_phi[_j][_qp]*_normals[_qp]*std::max(0.0,_u[_qp]));
//   }
//   else {
//     return 0.0;
//   }
//   }
