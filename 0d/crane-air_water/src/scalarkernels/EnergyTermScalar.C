#include "EnergyTermScalar.h"

registerMooseObject("CraneApp", EnergyTermScalar);

template <>
InputParameters
validParams<EnergyTermScalar>()
{
  InputParameters params = validParams<ODEKernel>();
  // params.addRequiredCoupledVar("gas_density", "The gas density.");
  params.addCoupledVar("v", 0, "Coupled variable 1.");
  params.addCoupledVar("w", 0, "Coupled variable 2.");
  params.addCoupledVar("rate_coefficient", 0, "Coupled reaction coefficient (if equation-based).");
  params.addRequiredParam<Real>("threshold_energy", "The energy change of the reaction.");
  params.addParam<Real>("energy_scaling", 1.0, "Convert energy units for consistency.");
  params.addRequiredParam<Real>("n_gas", "The gas density.");
  params.addParam<bool>("v_eq_u", false, "Whether or not u = v.");
  params.addParam<bool>("w_eq_u", false, "Whether or not u = w.");
  params.addParam<bool>("rate_constant_equation", false, "True if rate constant is provided by equation.");
  return params;
}

EnergyTermScalar::EnergyTermScalar(const InputParameters & parameters)
  : ODEKernel(parameters),
    _energy_change(getParam<Real>("threshold_energy")),
    _energy_scale(getParam<Real>("energy_scaling")),
    _v_var(isCoupledScalar("v") ? coupledScalar("v") : -1),
    _v(coupledScalarValue("v")),
    _w_var(isCoupledScalar("w") ? coupledScalar("w") : -1),
    _w(coupledScalarValue("w")),
    _rate_coefficient(coupledScalarValue("rate_coefficient")),
    _n_gas(getParam<Real>("n_gas")),
    _v_eq_u(getParam<bool>("v_eq_u")),
    _w_eq_u(getParam<bool>("w_eq_u")),
    _rate_constant_equation(getParam<bool>("rate_constant_equation"))
{
}

Real
EnergyTermScalar::computeQpResidual()
{
  Real mult1, mult2;
  if (isCoupledScalar("v"))
    mult1 = _v[_i];
  else
    mult1 = _n_gas;

  if (isCoupledScalar("w"))
    mult2 = _w[_i];
  else
    mult2 = _n_gas;

  return -_rate_coefficient[_i] * mult1 * mult2 * _energy_change * _energy_scale;
}

Real
EnergyTermScalar::computeQpJacobian()
{
  // Need to calculate derivative of _rate_coefficient[_i] w.r.t. _u[_i] somehow.
  // Maybe a DerivativeParsedAux class?
  return 0.0;
}

Real
EnergyTermScalar::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real power, mult1, mult2, deriv_factor, other_factor;
  Real rate_constant;
  power = 0;
  other_factor = 1;
  deriv_factor = 1;
  if (isCoupledScalar("v"))
    mult1 = _v[_i];
  else
    mult1 = _n_gas;

  if (isCoupledScalar("w"))
    mult2 = _w[_i];
  else
    mult2 = _n_gas;

  if (jvar == _v_var && !_v_eq_u)
  {
    power += 1;
    deriv_factor = mult1;
  }
  else
    other_factor *= mult1;

  if (jvar == _w_var && !_w_eq_u)
  {
    power += 1;
    deriv_factor = mult2;
  }
  else
    other_factor *= mult2;

  rate_constant = _rate_coefficient[_i];

  return -rate_constant * other_factor * power
    * std::pow(deriv_factor, power-1) * _energy_change * _energy_scale;
}
