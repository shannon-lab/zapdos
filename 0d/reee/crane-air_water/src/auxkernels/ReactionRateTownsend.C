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

#include "ReactionRateTownsend.h"

registerMooseObject("CraneApp", ReactionRateTownsend);

template <>
InputParameters
validParams<ReactionRateTownsend>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("mean_en", "The electron mean energy.");
  params.addRequiredCoupledVar("potential", "The potential.");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addCoupledVar("target", "The coupled target. If none, assumed to be background gas from BOLSIG+.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<std::string>("reaction", "Stores the full reaction equation.");
  params.addRequiredParam<std::string>("reaction_coefficient_name",
                                       "Stores the name of the reaction rate/townsend coefficient, "
                                       "unique to each individual reaction.");
  return params;
}

ReactionRateTownsend::ReactionRateTownsend(const InputParameters & parameters)
  : AuxKernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _reaction_coeff_name(getParam<std::string>("reaction_coefficient_name")),
    _reaction_name(getParam<std::string>("reaction")),
    _diffem(getMaterialProperty<Real>("diffem")),
    _muem(getMaterialProperty<Real>("muem")),
    // _alpha(getMaterialProperty<Real>("alpha_iz")),
    _alpha(getMaterialProperty<Real>(_reaction_coeff_name)),
    // _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_iz_d_actual_mean_en")),
    _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_alpha_d_en_" + _reaction_name)),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en")),
    _mean_en(coupledValue("mean_en")),
    _grad_potential(coupledGradient("potential")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em")),
    _mean_en_id(coupled("mean_en")),
    _potential_id(coupled("potential")),
    _em_id(coupled("em")),
    _target(isCoupled("target") ? coupledValue("target") : _zero),
    _target_id(isCoupled("target") ? coupled("target") : 12345678) 
{
}

Real
ReactionRateTownsend::computeValue()
{

  Real electron_flux_mag = (-_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
                            _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units)
                               .norm();
  return _alpha[_qp] * electron_flux_mag;

}
