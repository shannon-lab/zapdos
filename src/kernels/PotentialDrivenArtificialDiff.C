#include "PotentialDrivenArtificialDiff.h"

template<>
InputParameters validParams<PotentialDrivenArtificialDiff>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredParam<std::string>("var_name_string","The name of the kernel variable. Required to import the correct mobility from the material properties file.");
  params.addRequiredCoupledVar("potential","The potential for calculating the advection velocity.");
  params.addParam<bool>("consistent",false,"Whether to use consistent stabilization");
  params.addParam<Real>("delta",0.5,"Scaling parameter for artificial diffusivity");
  return params;
}

PotentialDrivenArtificialDiff::PotentialDrivenArtificialDiff(const InputParameters & parameters) :
    Kernel(parameters),

    // Input parameters

    _consistent(getParam<bool>("consistent")),
    _delta(getParam<Real>("delta")),

    // Coupled variables

    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),

    // Material properties

    _mobility(getMaterialProperty<Real>("mu"+getParam<std::string>("var_name_string"))),
    _diffusivity(getMaterialProperty<Real>("D_"+getParam<std::string>("var_name_string"))),

    // Variables unique to class
    
    _advection_velocity(0.0,0.0,0.0),
    _peclet_num(0.0),
    _alpha(0.0),
    _tau(0.0)
{
}

PotentialDrivenArtificialDiff::~PotentialDrivenArtificialDiff()
{
}

Real
PotentialDrivenArtificialDiff::computeQpResidual()
{
  _advection_velocity = _mobility[_qp]*-_grad_potential[_qp];
  _peclet_num = _current_elem->hmax() * std::max(_advection_velocity.size(),1e-16) / (2.0 * _diffusivity[_qp]);
  _alpha = 1.0 / std::tanh(std::max(_peclet_num,1e-16)) - 1.0 / std::max(_peclet_num,1e-16);
  
  if (_consistent)
  {
    // Consistent diffusion formulation of tau
    _tau = _delta * _current_elem->hmax() * _alpha / std::max(_advection_velocity.size(),1e-16);
    return _tau*_advection_velocity*_grad_test[_i][_qp]*_advection_velocity*_grad_u[_qp];    
  }
  else 
  {
    // Isotropic diffusion formulation of tau
    _tau = _delta * _current_elem->hmax() / std::max(_advection_velocity.size(),1e-16);
    return _tau*_advection_velocity*_grad_test[_i][_qp]*_advection_velocity*_grad_u[_qp];
  }
}

Real
PotentialDrivenArtificialDiff::computeQpJacobian()
{
  _advection_velocity = _mobility[_qp]*-_grad_potential[_qp];
  _peclet_num = _current_elem->hmax() * std::max(_advection_velocity.size(),1e-16) / (2.0 * _diffusivity[_qp]);
  _alpha = 1.0 / std::tanh(std::max(_peclet_num,1e-16)) - 1.0 / std::max(_peclet_num,1e-16);
  
  if (_consistent)
  {
    // Consistent diffusion formulation of tau
    _tau = _delta * _current_elem->hmax() * _alpha / std::max(_advection_velocity.size(),1e-16);
    return _tau*_advection_velocity*_grad_test[_i][_qp]*_advection_velocity*_grad_phi[_j][_qp];    
  }
  else
  {
    // Isotropic diffusion formulation of tau
    _tau = _delta * _current_elem->hmax() / std::max(_advection_velocity.size(),1e-16);
    return _tau*_advection_velocity*_grad_test[_i][_qp]*_advection_velocity*_grad_phi[_j][_qp];    
  }
}

Real
PotentialDrivenArtificialDiff::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
    {
      _advection_velocity = _mobility[_qp]*-_grad_potential[_qp];
      _peclet_num = _current_elem->hmax() * std::max(_advection_velocity.size(),1e-16) / (2.0 * _diffusivity[_qp]);
      _alpha = 1.0 / std::tanh(std::max(_peclet_num,1e-16)) - 1.0 / std::max(_peclet_num,1e-16);
      if (!_consistent)
	{
	  return _delta * _current_elem->hmax() * std::pow(_mobility[_qp],2)*_grad_u[_qp]*_grad_test[_i][_qp] * (1.0 / -std::max(std::pow(_advection_velocity.size(),2),1e-16)*_mobility[_qp]*_grad_potential[_qp]*_grad_phi[_j][_qp]/std::sqrt(std::max(_grad_potential[_qp]*_grad_potential[_qp],1e-16))*-_grad_potential[_qp]*-_grad_potential[_qp] + 1.0 / std::max(_advection_velocity.size(),1e-16)*2.0*_grad_potential[_qp]*_grad_phi[_j][_qp]);
	}
      else
	{
	  return 0.0;
	}
    }
  else
    {
      return 0.0;
    }
}
