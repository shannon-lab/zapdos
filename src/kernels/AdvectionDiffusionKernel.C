#include "AdvectionDiffusionKernel.h"

template<>
InputParameters validParams<AdvectionDiffusionKernel>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

AdvectionDiffusionKernel::AdvectionDiffusionKernel(const InputParameters & parameters) :
  Kernel(parameters),

  _a(1.0,0.0,0.0),
  _diff(0.0),
  _alpha(0.0),
  _Pe(0.0),
  _vd_mag(0.0),
  _delta(0.0)

{}

AdvectionDiffusionKernel::~AdvectionDiffusionKernel()
{}


Real
AdvectionDiffusionKernel::computeQpResidual()
{
  _vd_mag = _a.size();
  _Pe = _vd_mag*_current_elem->hmax()/_diff;
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  return -_grad_test[_i][_qp]*(_a*_u[_qp]-_diff*_grad_u[_qp])
	 -_grad_test[_i][_qp]*(-_delta*_grad_u[_qp]); // Diffusion stabilization
}

Real
AdvectionDiffusionKernel::computeQpJacobian()
{
  _vd_mag = _a.size();
  _Pe = _vd_mag*_current_elem->hmax()/_diff;
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  return -_grad_test[_i][_qp]*(_a*_phi[_j][_qp]-_diff*_grad_phi[_j][_qp])
	 -_grad_test[_i][_qp]*(-_delta*_grad_phi[_j][_qp]); // Diffusion stabilization
}
