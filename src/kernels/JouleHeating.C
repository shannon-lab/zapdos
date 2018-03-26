#include "JouleHeating.h"

registerMooseObject("ZapdosApp", JouleHeating);

template <>
InputParameters
validParams<JouleHeating>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

JouleHeating::JouleHeating(const InputParameters & parameters)
  : Kernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Material properties

    _muem(getMaterialProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _diffem(getMaterialProperty<Real>("diffem")),
    _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en")),
    _potential_units(getParam<std::string>("potential_units")),

    // Coupled variables

    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em")),
    _em_id(coupled("em"))

// Unique variables
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;
}

Real
JouleHeating::computeQpResidual()
{
  return _test[_i][_qp] * -_grad_potential[_qp] * _r_units * _voltage_scaling *
         (-_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
          _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units);
}

Real
JouleHeating::computeQpJacobian()
{
  Real actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
  Real d_muem_d_mean_en = _d_muem_d_actual_mean_en[_qp] * actual_mean_en * _phi[_j][_qp];
  Real d_diffem_d_mean_en = _d_diffem_d_actual_mean_en[_qp] * actual_mean_en * _phi[_j][_qp];

  return _test[_i][_qp] * -_grad_potential[_qp] * _r_units * _voltage_scaling *
         (-d_muem_d_mean_en * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
          d_diffem_d_mean_en * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units);
}

Real
JouleHeating::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return _test[_i][_qp] * -_grad_potential[_qp] * _r_units * _voltage_scaling *
               (-_muem[_qp] * -_grad_phi[_j][_qp] * _r_units * std::exp(_em[_qp])) +
           _test[_i][_qp] * -_grad_phi[_j][_qp] * _r_units * _voltage_scaling *
               (-_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
                _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units);
  }
  else if (jvar == _em_id)
  {
    Real actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
    Real d_muem_d_em = _d_muem_d_actual_mean_en[_qp] * actual_mean_en * -_phi[_j][_qp];
    Real d_diffem_d_em = _d_diffem_d_actual_mean_en[_qp] * actual_mean_en * -_phi[_j][_qp];

    return _test[_i][_qp] * -_grad_potential[_qp] * _r_units * _voltage_scaling *
           (-_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) * _phi[_j][_qp] -
            d_muem_d_em * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
            _diffem[_qp] * (std::exp(_em[_qp]) * _phi[_j][_qp] * _grad_em[_qp] * _r_units +
                            std::exp(_em[_qp]) * _grad_phi[_j][_qp] * _r_units) -
            d_diffem_d_em * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units);
  }
  else
  {
    return 0.0;
  }
}
