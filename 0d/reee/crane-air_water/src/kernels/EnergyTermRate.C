#include "EnergyTermRate.h"

registerMooseObject("CraneApp", EnergyTermRate);

template <>
InputParameters
validParams<EnergyTermRate>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("v", "The first reactant species density.");
  params.addCoupledVar("w", "The second reactant species density.");
  params.addRequiredParam<std::string>("reaction", "The reaction that is adding/removing energy.");
  params.addParam<Real>("threshold_energy", 0.0, "Energy required for reaction to take place.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

EnergyTermRate::EnergyTermRate(
    const InputParameters & parameters)
  : Kernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _threshold_energy(getParam<Real>("threshold_energy")),
    _n_gas(getMaterialProperty<Real>("n_gas")),
    _rate_coefficient(getMaterialProperty<Real>("k_"+getParam<std::string>("reaction"))),
    _v(coupledValue("v")),
    _w(isCoupled("w") ? coupledValue("w") : _zero),
    _v_id(coupled("v")),
    _w_id(isCoupled("w") ? coupled("w") : 0)
{
}

EnergyTermRate::~EnergyTermRate() {}

Real
EnergyTermRate::computeQpResidual()
{
  if (isCoupled("w"))
    return -_test[_i][_qp] * _rate_coefficient[_qp] * _v[_qp] * _w[_qp] * _threshold_energy;
  else
    return -_test[_i][_qp] * _rate_coefficient[_qp] * _n_gas[_qp] * _v[_qp] * _threshold_energy;
}

Real
EnergyTermRate::computeQpJacobian()
{
  // Temporary - requires actual contribution from the rate coefficient
  return 0.0;
  // if (isCoupled("v"))
  //   return -_test[_i][_qp] * d_iz_d_mean_en * _v[_qp] * _w[_qp] * _threshold_energy;
  // else
  //   return -_test[_i][_qp] * d_iz_d_mean_en * _n_gas[_qp] * _w[_qp] * _threshold_energy;
}

Real
EnergyTermRate::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (isCoupled("w"))
  {
    if (jvar == _w_id)
    {
      return -_test[_i][_qp] * _v[_qp] * _threshold_energy * _rate_coefficient[_qp] * _phi[_j][_qp];
    }
    if (jvar == _v_id)
    {
      return -_test[_i][_qp] * _threshold_energy * _rate_coefficient[_qp] * _w[_qp] * _phi[_j][_qp];
    }
    else
      return 0.0;
  }
  else
  {
    if (jvar == _v_id)
      return -_test[_i][_qp] * _n_gas[_qp] * _threshold_energy * _n_gas[_qp] * _rate_coefficient[_qp] * _phi[_j][_qp];
    else
      return 0.0;
  }

}
