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

#include "SuperelasticRateCoefficientScalar.h"

registerMooseObject("CraneApp", SuperelasticRateCoefficientScalar);

template <>
InputParameters
validParams<SuperelasticRateCoefficientScalar>()
{
  InputParameters params = validParams<AuxScalarKernel>();
  params.addRequiredCoupledVar("forward_coefficient", "The forward rate coefficient that is being reversed.");
  params.addCoupledVar("Tgas", 0, "The gas temperature in Kelvin (if it is a variable.).");
  params.addParam<Real>("Tgas_const", 0, "The gas temperature in Kelvin (if constant).");
  params.addRequiredParam<UserObjectName>("polynomial_provider",
      "The name of the UserObject that can provide the polynomial coefficients.");
  return params;
}

SuperelasticRateCoefficientScalar::SuperelasticRateCoefficientScalar(const InputParameters & parameters)
  : AuxScalarKernel(parameters),
    _forward_coefficient(coupledScalarValue("forward_coefficient")),
    _Tgas(coupledScalarValue("Tgas")),
    _Tgas_const(getParam<Real>("Tgas_const")),
    _polynomial(getUserObject<PolynomialCoefficients>("polynomial_provider"))
{
}

Real
SuperelasticRateCoefficientScalar::computeValue()
{
  Real equilibrium_constant;
  Real Tgas;
  if (isCoupledScalar("Tgas"))
    Tgas = _Tgas[_i];
  else
    Tgas = _Tgas_const;

  equilibrium_constant = std::pow(1.0, _polynomial.power_coefficient()) * std::exp(_polynomial.delta_a(0)*(std::log(Tgas - 1)) +
  (_polynomial.delta_a(1)/2.0)*Tgas + (_polynomial.delta_a(2)/6.0)*std::pow(Tgas, 2.0) + (_polynomial.delta_a(3)/12.0)*std::pow(Tgas, 3.0) +
  (_polynomial.delta_a(4)/20.0)*std::pow(Tgas, 4.0) - _polynomial.delta_a(5)*std::pow(Tgas, -1.0) + _polynomial.delta_a(6));

  return _forward_coefficient[_i] / equilibrium_constant;
}
