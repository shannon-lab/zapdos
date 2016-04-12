#include "ElectronEnergyRateElastic.h"


template<>
InputParameters validParams<ElectronEnergyRateElastic>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("em", "The electron density");
  return params;
}


ElectronEnergyRateElastic::ElectronEnergyRateElastic(const InputParameters & parameters) :
    Kernel(parameters),

    _kel(getMaterialProperty<Real>("kel")),
    _d_kel_d_actual_mean_en(getMaterialProperty<Real>("d_kel_d_actual_mean_en")),
    _massem(getMaterialProperty<Real>("massem")),
    _massGas(getMaterialProperty<Real>("massGas")),
    _n_gas(getMaterialProperty<Real>("n_gas")),

    _actual_mean_en(0),
    _d_kel_d_mean_en(0),
    _d_kel_d_em(0),

    _em(coupledValue("em")),
    _em_id(coupled("em"))
{
}

ElectronEnergyRateElastic::~ElectronEnergyRateElastic()
{
}

Real
ElectronEnergyRateElastic::computeQpResidual()
{
  return -_test[_i][_qp] * _kel[_qp] * _n_gas[_qp] * std::exp(_em[_qp]) * -2. * _massem[_qp] / _massGas[_qp] * std::exp(_u[_qp] - _em[_qp]);
}

Real
ElectronEnergyRateElastic::computeQpJacobian()
{
    _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
    _d_kel_d_mean_en = _d_kel_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp];

    return -_test[_i][_qp] * _n_gas[_qp] * -2. * _massem[_qp] / _massGas[_qp] * std::exp(_em[_qp]) * (_d_kel_d_mean_en * std::exp(_u[_qp] - _em[_qp]) + _kel[_qp] * std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp]);
}

Real
ElectronEnergyRateElastic::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
  {
    _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
    _d_kel_d_em = _d_kel_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp];

    return -_test[_i][_qp] * _n_gas[_qp] * ((_d_kel_d_em * std::exp(_em[_qp]) + _kel[_qp] * std::exp(_em[_qp]) * _phi[_j][_qp]) * -2. * _massem[_qp] / _massGas[_qp] * std::exp(_u[_qp] - _em[_qp]) + _kel[_qp] * std::exp(_em[_qp]) * -2. * _massem[_qp] / _massGas[_qp] * std::exp(_u[_qp] - _em[_qp]) * -_phi[_j][_qp]);
  }

  else
    return 0.0;
}
