#include "SideTotFluxIntegral.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", SideTotFluxIntegral);

template <>
InputParameters
validParams<SideTotFluxIntegral>()
{
  InputParameters params = validParams<SideIntegralVariablePostprocessor>();
  // params.addRequiredParam<std::string>("diffusivity", "The name of the diffusivity material
  // property that will be used in the flux computation.");
  params.addRequiredParam<std::string>(
      "mobility",
      "The name of the mobility material property that will be used in the flux computation.");
  params.addRequiredCoupledVar("potential", "The potential that drives the advective flux.");
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<Real>(
      "user_velocity", -1., "Optional parameter if user wants to specify the thermal velocity");
  return params;
}

SideTotFluxIntegral::SideTotFluxIntegral(const InputParameters & parameters)
  : SideIntegralVariablePostprocessor(parameters),
    // _diffusivity(parameters.get<std::string>("diffusivity")),
    // _diffusion_coef(getMaterialProperty<Real>(_diffusivity)),
    _mobility(parameters.get<std::string>("mobility")),
    _mobility_coef(getMaterialProperty<Real>(_mobility)),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    _kb(getMaterialProperty<Real>("k_boltz")),
    _T_heavy(getMaterialProperty<Real>("T_heavy")),
    _mass(getMaterialProperty<Real>("mass" + _variable->name())),
    _v_thermal(0),
    _user_velocity(getParam<Real>("user_velocity")),
    _e(getMaterialProperty<Real>("e")),
    _sgn(getMaterialProperty<Real>("sgn" + _variable->name())),
    _a(0.5),

    _grad_potential(coupledGradient("potential"))
{
}

Real
SideTotFluxIntegral::computeQpIntegral()
{
  // Output units for base case are: mol / (m^2 * s)

  if (_user_velocity > 0.)
    _v_thermal = _user_velocity;
  else
    _v_thermal = std::sqrt(8 * _kb[_qp] * _T_heavy[_qp] / (M_PI * _mass[_qp]));

  if (_normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0)
    _a = 1.0;
  else
    _a = 0.0;

  // return -_mobility_coef[_qp] * _grad_potential[_qp] * _normals[_qp] * std::exp(_u[_qp])
  // -_diffusion_coef[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _normals[_qp];

  return (1. - _r) / (1. + _r) * 0.5 * _v_thermal * std::exp(_u[_qp]) +
         (1. - _r) / (1. + _r) *
             ((2 * _a - 1) * _sgn[_qp] * _mobility_coef[_qp] * -_grad_potential[_qp] * _r_units *
              std::exp(_u[_qp]) * _normals[_qp]);
}
