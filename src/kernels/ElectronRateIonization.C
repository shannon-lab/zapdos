#include "ElectronRateIonization.h"


template<>
InputParameters validParams<ElectronRateIonization>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("mean_en","The electron mean energy.");
  return params;
}


ElectronRateIonization::ElectronRateIonization(const InputParameters & parameters) :
    Kernel(parameters),

    _kiz(getMaterialProperty<Real>("kiz")),
    _d_kiz_d_actual_mean_en(getMaterialProperty<Real>("d_kiz_d_actual_mean_en")),
    _n_gas(getMaterialProperty<Real>("n_gas")),

    _actual_mean_en(0),
    _d_kiz_d_mean_en(0),
    _d_kiz_d_em(0),

    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en"))
{
}

ElectronRateIonization::~ElectronRateIonization()
{
}

Real
ElectronRateIonization::computeQpResidual()
{
  return -_test[_i][_qp] * _kiz[_qp] * _n_gas[_qp] * std::exp(_u[_qp]);
}

Real
ElectronRateIonization::computeQpJacobian()
{
  _actual_mean_en = std::exp(_mean_en[_qp] - _u[_qp]);
  _d_kiz_d_em = _d_kiz_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp];

  return -_test[_i][_qp] * _n_gas[_qp] * (_d_kiz_d_em * std::exp(_u[_qp]) + _kiz[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp]);
}

Real
ElectronRateIonization::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _mean_en_id)
  {
    _actual_mean_en = std::exp(_mean_en[_qp] - _u[_qp]);
    _d_kiz_d_mean_en = _d_kiz_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp];

    return -_test[_i][_qp] * _n_gas[_qp] * std::exp(_u[_qp]) * _d_kiz_d_mean_en;
  }

  else
    return 0.0;
}
