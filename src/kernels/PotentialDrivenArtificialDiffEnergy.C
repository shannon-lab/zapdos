#include "PotentialDrivenArtificialDiffEnergy.h"

template<>
InputParameters validParams<PotentialDrivenArtificialDiffEnergy>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredParam<std::string>("var_name_string","The name of the kernel variable. Required to import the correct mobility from the material properties file.");
  params.addRequiredCoupledVar("potential","The potential for calculating the advection velocity.");
  params.addRequiredCoupledVar("em","The electron density.");
  params.addParam<bool>("consistent",false,"Whether to use consistent stabilization");
  params.addParam<Real>("delta",0.5,"Scaling parameter for artificial diffusivity");
  return params;
}

PotentialDrivenArtificialDiffEnergy::PotentialDrivenArtificialDiffEnergy(const InputParameters & parameters) :
    Kernel(parameters),

    // Input parameters

    _consistent(getParam<bool>("consistent")),
    _delta(getParam<Real>("delta")),

    // Coupled variables

    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _em(coupledValue("em")),
    _em_id(coupled("em")),
    _grad_em(coupledGradient("em")),

    // Material properties

    _mobility_em(getMaterialProperty<Real>("mu"+getParam<std::string>("var_name_string"))),

    // Variables unique to class
    
    _advection_velocity(0.0,0.0,0.0),
    _peclet_num(0.0),
    _alpha(0.0),
    _tau(0.0),
    _diffusivity(0.0),
    _mobility_el(0.0)
{
}

PotentialDrivenArtificialDiffEnergy::~PotentialDrivenArtificialDiffEnergy()
{
}

Real
PotentialDrivenArtificialDiffEnergy::computeQpResidual()
{
  _mobility_el = 5.0/3.0*_mobility_em[_qp];
  _advection_velocity = _mobility_el*-1.0*-_grad_potential[_qp];
  _diffusivity = _mobility_el*_u[_qp];
  _peclet_num = _current_elem->hmax() * std::max(_advection_velocity.size(),1e-16) / (2.0 * _diffusivity);
  _alpha = 1.0 / std::tanh(std::max(_peclet_num,1e-16)) - 1.0 / std::max(_peclet_num,1e-16);
  
  if (_consistent)
  {
    // Consistent diffusion formulation of tau
    _tau = _delta * _current_elem->hmax() * _alpha / std::max(_advection_velocity.size(),1e-16);
    return _tau*_advection_velocity*_grad_test[_i][_qp]*_advection_velocity*1.5*(_em[_qp]*_grad_u[_qp]+_u[_qp]*_grad_em[_qp]);    
  }
  else 
  {
    // Isotropic diffusion formulation of tau
    _tau = _delta * _current_elem->hmax() / std::max(_advection_velocity.size(),1e-16);
    return _tau*_advection_velocity*_grad_test[_i][_qp]*_advection_velocity*1.5*(_em[_qp]*_grad_u[_qp]+_u[_qp]*_grad_em[_qp]);    
  }
}

/*
Real
PotentialDrivenArtificialDiffEnergy::computeQpJacobian()
{
  _advection_velocity = _mobility_el*-1.0*-_grad_potential[_qp];
  _diffusivity = _mobility_el*_Te[_qp];
  _peclet_num = _current_elem->hmax() * std::max(_advection_velocity.size(),1e-16) / (2.0 * _diffusivity);
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
PotentialDrivenArtificialDiffEnergy::computeQpOffDiagJacobian(unsigned int jvar)
{
  // Current off-diag jacobian is only correct for inconsistent formulation since I haven't written the derivatives out with respect to the electront temperature for the consistent formulation.

  if (jvar == _potential_id)
    {
      _advection_velocity = _mobility_el*-1.0*-_grad_potential[_qp];
      _diffusivity = _mobility_el*_Te[_qp];
      _peclet_num = _current_elem->hmax() * std::max(_advection_velocity.size(),1e-16) / (2.0 * _diffusivity);
      _alpha = 1.0 / std::tanh(std::max(_peclet_num,1e-16)) - 1.0 / std::max(_peclet_num,1e-16);
      if (!_consistent)
	{
	  return _delta * _current_elem->hmax() * std::pow(_mobility_el,2)*_grad_u[_qp]*_grad_test[_i][_qp] * (1.0 / -std::max(std::pow(_advection_velocity.size(),2),1e-16)*_mobility_el*_grad_potential[_qp]*_grad_phi[_j][_qp]/std::sqrt(std::max(_grad_potential[_qp]*_grad_potential[_qp],1e-16))*-_grad_potential[_qp]*-_grad_potential[_qp] + 1.0 / std::max(_advection_velocity.size(),1e-16)*2.0*_grad_potential[_qp]*_grad_phi[_j][_qp]);
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
*/
