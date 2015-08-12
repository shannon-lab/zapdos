/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
#include "Air.h"

template<>
InputParameters validParams<Air>()
{
  InputParameters params = validParams<Material>();

  params.addParam<Real>("user_relative_permittivity", 1.0, "Multiplies the permittivity of free space.");
  params.addParam<Real>("user_potential_mult",1.0,"Scaling for potential");
  params.addParam<Real>("user_density_mult",1.0,"Scaling for densities");
  //  params.addParam<Real>("delta",0.5,"Scaling parameter for artificial diffusivity");
  //  params.addParam<bool>("consistent",false,"Whether to use consistent stabilization vs. inconsistent isotropic diffusion");  
  params.addCoupledVar("potential", "The potential for calculating the electron velocity");
  params.addCoupledVar("em", "Species concentration needed to calculate the poisson source");
  params.addCoupledVar("ip", "Species concentration needed to calculate the poisson source");
  return params;
}


Air::Air(const InputParameters & parameters) :
    Material(parameters),

    // Input parameters

    _user_relative_permittivity(getParam<Real>("user_relative_permittivity")),
    _user_potential_mult(getParam<Real>("user_potential_mult")),
    _user_density_mult(getParam<Real>("user_density_mult")),
    //    _delta(getParam<Real>("delta")),
    //    _consistent(getParam<bool>("consistent")),
    
    // Coupled variables
    
    _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _grad_zero),
    _em(isCoupled("em") ? coupledValue("em") : _zero),
    _ip(isCoupled("ip") ? coupledValue("ip") : _zero),
    _grad_em(isCoupled("em") ? coupledGradient("em") : _grad_zero),
    _grad_ip(isCoupled("ip") ? coupledGradient("ip") : _grad_zero),
// Functions

//  _peclet_num(declareProperty<Real>("peclet_num")),
//_alpha(declareProperty<Real>("alpha")),
//_velocity(declareProperty<RealVectorValue>("velocity")),
//_velocity_norm(declareProperty<RealVectorValue>("velocity_norm")),
//_diffusivity(declareProperty<Real>("diffusivity")),
//_tau(declareProperty<Real>("tau"))


// Declare material properties.  This returns references that we
// hold onto as member variables

  _potential_mult(declareProperty<Real>("potential_mult")),
  _density_mult(declareProperty<Real>("density_mult")),
  _N_A(declareProperty<Real>("N_A")),
  _eps_r(declareProperty<Real>("eps_r")),
  _eps_0(declareProperty<Real>("eps_0")),
  _e(declareProperty<Real>("e")),
  _Dem(declareProperty<Real>("Dem")),
  _Dip(declareProperty<Real>("Dip")),
  _zem(declareProperty<Real>("zem")),
  _zip(declareProperty<Real>("zip")),
  _muem(declareProperty<Real>("muem")),
  _muip(declareProperty<Real>("muip")),
  _alpha_0(declareProperty<Real>("alpha_0")),
  _E_0(declareProperty<Real>("E_0")),
  _s(declareProperty<Real>("s")),
  _sem(declareProperty<Real>("sem")),
  _sip(declareProperty<Real>("sip")),
  _spotential(declareProperty<Real>("spotential")),
  _Jac_em(declareProperty<Real>("Jac_em")),
  _Jac_ip(declareProperty<Real>("Jac_ip")),
  _Jac_potential(declareProperty<Real>("Jac_potential")),
  _EField(declareProperty<RealVectorValue>("EField")),
  _gamma_em(declareProperty<RealVectorValue>("gamma_em")),
  _gamma_ip(declareProperty<RealVectorValue>("gamma_ip")),
  _k_boltz(declareProperty<Real>("k_boltz")),
  _T_em(declareProperty<Real>("T_em")),
  _T_ip(declareProperty<Real>("T_ip")),
  _m_em(declareProperty<Real>("m_em")),
  _m_ip(declareProperty<Real>("m_ip")),
  _v_thermal_em(declareProperty<Real>("v_thermal_em")),
  _v_thermal_ip(declareProperty<Real>("v_thermal_ip")),
  _advection_velocity_em(declareProperty<RealVectorValue>("advection_velocity_em")),
  _advection_velocity_ip(declareProperty<RealVectorValue>("advection_velocity_ip")),
  _h_size(declareProperty<Real>("h_size"))
{
  /*  if (isCoupled("potential"))
    {
      _coupling = true;
    }
  else
    {
      _coupling = false;
      }*/
}

void
Air::computeQpProperties()
{  
  _density_mult[_qp] = _user_density_mult;
  _potential_mult[_qp] = _user_potential_mult;
  _N_A[_qp] = 6.02e23;
  _eps_r[_qp]   = _user_relative_permittivity;
  _eps_0[_qp]   = 8.85e-12;
  _e[_qp]	= 1.6e-19;  // coulombic charge
  _Dem[_qp] = 1800.0/(1.0e4); // Ebert article, Morrow review
  _Dip[_qp] = 0.046/(1.0e4); // Morrow review
  _zem[_qp] = -1.0;
  _zip[_qp] = 1.0;
  _T_em[_qp] = 11000;
  _T_ip[_qp] = 300;
  _muem[_qp] = _zem[_qp]*380.0/(1.0e4); // Ebert article
  _muip[_qp] = _zip[_qp]*380.0/(1.0e4)*(_T_em[_qp]/_T_ip[_qp])*(_Dip[_qp]/_Dem[_qp]); // Assuming Einstein relationship
  _alpha_0[_qp] = 4332.0*100.0; // Ebert article
  _E_0[_qp] = 2.0e7; // Ebert article
  
  _s[_qp] = std::max(_em[_qp],0.0)*std::abs(_muem[_qp])*_grad_potential[_qp].size()*_potential_mult[_qp]*_alpha_0[_qp]*std::exp(-_E_0[_qp]/(_grad_potential[_qp].size()*_potential_mult[_qp]+1.0));
  _sem[_qp] = _s[_qp];
  _sip[_qp] = _s[_qp];
  _spotential[_qp] = _N_A[_qp]*_e[_qp]/(_eps_r[_qp]*_eps_0[_qp]*_potential_mult[_qp])*(std::max(_em[_qp],0.0)*_zem[_qp]+std::max(_ip[_qp],0.0)*_zip[_qp]);
  _Jac_em[_qp] = std::abs(_muem[_qp])*_grad_potential[_qp].size()*_potential_mult[_qp]*_alpha_0[_qp]*std::exp(-_E_0[_qp]/(_grad_potential[_qp].size()*_potential_mult[_qp]+1.0));
  _Jac_ip[_qp] = 0.0;
  _Jac_potential[_qp] = 0.0;

  _EField[_qp] = -_grad_potential[_qp];
  _gamma_em[_qp] = _muem[_qp]*_EField[_qp]*_em[_qp]-_Dem[_qp]*_grad_em[_qp];
  _gamma_ip[_qp] = _muip[_qp]*_EField[_qp]*_ip[_qp]-_Dip[_qp]*_grad_ip[_qp];
  _k_boltz[_qp] = 1.38e-23;
  _m_em[_qp] = 9.11e-31;
  _m_ip[_qp] = 29.0*1.66e-27;
  _v_thermal_em[_qp] = 1.6*std::sqrt(_k_boltz[_qp]*_T_em[_qp]/_m_em[_qp]);
  _v_thermal_ip[_qp] = 1.6*std::sqrt(_k_boltz[_qp]*_T_ip[_qp]/_m_ip[_qp]);
  _advection_velocity_em[_qp] = _muem[_qp]*_EField[_qp];
  _advection_velocity_ip[_qp] = _muip[_qp]*_EField[_qp];
  _h_size[_qp] = _current_elem->hmax();
  // The following commented section should be moved to a kernel so that different stabilization can be used
  // for different variables.

  /*  if (_coupling)
    {
      _velocity[_qp] = _grad_potential[_qp];
    }
  else
    { 
      _velocity[_qp](0) = 0.0;
      _velocity[_qp](1) = 0.0;
      _velocity[_qp](2) = 0.0;
      }

    _velocity_norm_vector[_qp] = _velocity[_qp] / _velocity[_qp].size();  
    _peclet_num[_qp] = _current_elem->hmax() * _velocity[_qp].size() / (2.0 * _diffusivity[_qp]);
  _alpha[_qp] = 1.0 / std::tanh(_peclet_num[_qp]) - 1.0 / _peclet_num[_qp];
  
  if (_consistent)
  {
    // Consistent diffusion formulation of tau
    _tau[_qp] = _delta * _current_elem->hmax() * _alpha[_qp] / _velocity[_qp].size();
  }
  else if (!_consistent)
  {
    // Isotropic diffusion formulation of tau

    _tau[_qp] = _delta * _current_elem->hmax() / _velocity[_qp].size();
    }*/
}
