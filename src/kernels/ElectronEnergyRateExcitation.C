#include "ElectronEnergyRateExcitation.h"


template<>
InputParameters validParams<ElectronEnergyRateExcitation>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("em", "The electron density");
  return params;
}


ElectronEnergyRateExcitation::ElectronEnergyRateExcitation(const InputParameters & parameters) :
    Kernel(parameters),

    _kex(getMaterialProperty<Real>("kex")),
    _d_kex_d_actual_mean_en(getMaterialProperty<Real>("d_kex_d_actual_mean_en")),
    _Eex(getMaterialProperty<Real>("Eex")),

    _em(coupledValue("em")),
    _em_id(coupled("em"))
{
}

ElectronEnergyRateExcitation::~ElectronEnergyRateExcitation()
{
}

Real
ElectronEnergyRateExcitation::computeQpResidual()
{
  return -_test[_i][_qp] * _kex[_qp] * _n_gas[_qp] * std::exp(_em[_qp]) * -_Eex[_qp];
}

Real
ElectronEnergyRateExcitation::computeQpJacobian()
{
    _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
    _d_kex_d_mean_en = _d_kex_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp];

    return -_test[_i][_qp] * _n_gas[_qp] * std::exp(_em[_qp]) * _d_kex_d_mean_en * -_Eex[_qp];
}

Real
ElectronEnergyRateExcitation::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
  {
    _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
    _d_kex_d_em = _d_kex_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp];

    return -_test[_i][_qp] * _n_gas[_qp] * (_d_kex_d_em * std::exp(_em[_qp]) + _kex[_qp] * std::exp(_em[_qp]) * _phi[_j][_qp]) * -_Eex[_qp];
  }

  else
    return 0.0;
}
