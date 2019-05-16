#include "ElectronEnergyTermElasticRate.h"

registerMooseObject("ZapdosApp", ElectronEnergyTermElasticRate);

template <>
InputParameters
validParams<ElectronEnergyTermElasticRate>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("electron_species", "The impacting (electron) species.");
  params.addRequiredCoupledVar("target_species", "The target species in this elasic reaction.");
  params.addRequiredParam<std::string>("reaction", "The reaction that is adding/removing energy.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredCoupledVar("potential", "The potential.");
  return params;
}

ElectronEnergyTermElasticRate::ElectronEnergyTermElasticRate(
    const InputParameters & parameters)
  : Kernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _rate_coefficient(getMaterialProperty<Real>("k_"+getParam<std::string>("reaction"))),
    _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_k_d_en_"+getParam<std::string>("reaction"))),
    _electron(coupledValue("electron_species")),
    _target(coupledValue("target_species")),
    _electron_id(coupled("electron_species")),
    _target_id(coupled("target_species")),
    _massIncident(getMaterialProperty<Real>("mass"+(*getVar("electron_species",0)).name())),
    _massTarget(getMaterialProperty<Real>("mass"+(*getVar("target_species",0)).name()))
{
}

ElectronEnergyTermElasticRate::~ElectronEnergyTermElasticRate() {}

Real
ElectronEnergyTermElasticRate::computeQpResidual()
{
  Real energy_elastic = -3.0 * (_massIncident[_qp] / _massTarget[_qp]) * 2.0 / 3.0 * std::exp(_u[_qp] - _electron[_qp]);

  return -_test[_i][_qp] * _rate_coefficient[_qp] * std::exp(_target[_qp]) * std::exp(_electron[_qp]) * energy_elastic;
}

Real
ElectronEnergyTermElasticRate::computeQpJacobian()
{
  Real actual_mean_en = std::exp(_u[_qp] - _electron[_qp]);
  Real d_actual_mean_en_d_mean_en = std::exp(_u[_qp] - _electron[_qp]) * _phi[_j][_qp];
  Real d_iz_d_mean_en = _d_iz_d_actual_mean_en[_qp] * d_actual_mean_en_d_mean_en;
  Real energy_elastic = -3.0 * (_massIncident[_qp] / _massTarget[_qp]) * 2.0 / 3.0 * std::exp(_u[_qp] - _electron[_qp]);
  Real d_elastic_d_en = -3.0 * (_massIncident[_qp] / _massTarget[_qp]) * 2.0 / 3.0 * std::exp(_u[_qp] - _electron[_qp]) * _phi[_j][_qp];

  // return -_test[_i][_qp] * d_iz_d_mean_en * std::exp(_v[_qp]) * std::exp(_em[_qp]) * _energy_change;
  return -_test[_i][_qp] * std::exp(_target[_qp] + _electron[_qp]) * (_rate_coefficient[_qp] * d_elastic_d_en + _d_iz_d_actual_mean_en[_qp] * energy_elastic);
}

Real
ElectronEnergyTermElasticRate::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real actual_mean_en = std::exp(_u[_qp] - _electron[_qp]);
  Real energy_elastic = -3.0 * (_massIncident[_qp] / _massTarget[_qp]) * 2.0 / 3.0 * std::exp(_u[_qp] - _electron[_qp]);
  // Real d_elastic_d_em = 3.0 * (_massIncident[_qp] / _massTarget[_qp]) * 2.0 / 3.0 * std::exp(_u[_qp] - _electron[_qp]) * _phi[_j][_qp];


  if (jvar == _electron_id)
  {
    return -2.0 * _test[_i][_qp] * std::exp(_electron[_qp] + _target[_qp]) * energy_elastic * _phi[_j][_qp];
  }
  if (jvar == _target_id)
  {
    return -_test[_i][_qp] * std::exp(_electron[_qp] + _target[_qp]) * energy_elastic * _phi[_j][_qp];
  }
  else
    return 0.0;

}
