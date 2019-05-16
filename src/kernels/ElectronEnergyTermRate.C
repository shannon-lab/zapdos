#include "ElectronEnergyTermRate.h"

registerMooseObject("ZapdosApp", ElectronEnergyTermRate);

template <>
InputParameters
validParams<ElectronEnergyTermRate>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addCoupledVar("v", "The second reactant species.");
  params.addParam<bool>("elastic_collision", false, "If the collision is elastic.");
  params.addRequiredParam<std::string>("reaction", "The reaction that is adding/removing energy.");
  params.addParam<Real>("threshold_energy", 0.0, "Energy required for reaction to take place.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

ElectronEnergyTermRate::ElectronEnergyTermRate(
    const InputParameters & parameters)
  : Kernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _elastic(getParam<bool>("elastic_collision")),
    _threshold_energy(getParam<Real>("threshold_energy")),
    // _elastic_energy(getMaterialProperty<Real>("energy_elastic_" + getParam<std::string>("reaction"))),
    _n_gas(getMaterialProperty<Real>("n_gas")),
    _rate_coefficient(getMaterialProperty<Real>("k_"+getParam<std::string>("reaction"))),
    _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_k_d_en_"+getParam<std::string>("reaction"))),
    _em(coupledValue("em")),
    _v(isCoupled("v") ? coupledValue("v") : _zero),
    _grad_em(coupledGradient("em")),
    _em_id(coupled("em")),
    _v_id(isCoupled("v") ? coupled("v") : 0)
{
  if (!_elastic && !isParamValid("threshold_energy"))
    mooseError("ElectronEnergyTerm: Elastic collision set to false, but no threshold energy for this reaction is provided!");
  // if (_elastic)
  //   _energy_change = _elastic_energy[_qp];
  // else
  //   _energy_change = _threshold_energy;
  _energy_change = _threshold_energy;
}

ElectronEnergyTermRate::~ElectronEnergyTermRate() {}

Real
ElectronEnergyTermRate::computeQpResidual()
{
  // if (_elastic)
  //   _energy_change = _elastic_energy[_qp];
  // else
  //   _energy_change = _threshold_energy;

  if (isCoupled("v"))
    return -_test[_i][_qp] * _rate_coefficient[_qp] * std::exp(_v[_qp]) * std::exp(_em[_qp]) * _energy_change;
  else
    return -_test[_i][_qp] * _rate_coefficient[_qp] * _n_gas[_qp] * std::exp(_em[_qp]) * _energy_change;
}

Real
ElectronEnergyTermRate::computeQpJacobian()
{
  // if (_elastic)
  //   _energy_change = _elastic_energy[_qp];
  // else
  //   _energy_change = _threshold_energy;

  Real actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
  Real d_actual_mean_en_d_mean_en = std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];
  Real d_iz_d_mean_en = _d_iz_d_actual_mean_en[_qp] * d_actual_mean_en_d_mean_en;

  if (isCoupled("v"))
    return -_test[_i][_qp] * d_iz_d_mean_en * std::exp(_v[_qp]) * std::exp(_em[_qp]) * _energy_change;
  else
    return -_test[_i][_qp] * d_iz_d_mean_en * _n_gas[_qp] * std::exp(_em[_qp]) * _energy_change;
}

Real
ElectronEnergyTermRate::computeQpOffDiagJacobian(unsigned int jvar)
{
  // if (_elastic)
  //   _energy_change = _elastic_energy[_qp];
  // else
  //   _energy_change = _threshold_energy;

  Real actual_mean_en = std::exp(_u[_qp] - _em[_qp]);

  if (isCoupled("v"))
  {
    if (jvar == _em_id)
    {
      return -_test[_i][_qp] * std::exp(_em[_qp]) * std::exp(_v[_qp]) * _phi[_j][_qp] * _energy_change;
    }
    if (jvar == _v_id)
    {
      return -_test[_i][_qp] * std::exp(_em[_qp]) * std::exp(_v[_qp]) * _phi[_j][_qp] * _energy_change;
    }
    else
      return 0.0;
  }
  else
  {
    if (jvar == _em_id)
      return -_test[_i][_qp] * std::exp(_em[_qp]) * _n_gas[_qp] * _phi[_j][_qp] * _energy_change;
    else
      return 0.0;
  }

}
