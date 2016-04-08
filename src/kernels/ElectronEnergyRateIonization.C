#include "ElectronEnergyRateIonization.h"


template<>
InputParameters validParams<ElectronEnergyRateIonization>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("mean_en","The electron mean energy.");
  params.addRequiredCoupledVar("em", "The electron density");
  return params;
}


ElectronEnergyRateIonization::ElectronEnergyRateIonization(const InputParameters & parameters) :
    Kernel(parameters),

    _kiz(getMaterialProperty<Real>("kiz")),
    _d_kiz_d_actual_mean_en(getMaterialProperty<Real>("d_kiz_d_actual_mean_en")),
    _Eiz(getMaterialProperty<Real>("Eiz")),

    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),
    _em(coupledValue("em")),
    _em_id(coupled("em"))
{
}

ElectronEnergyRateIonization::~ElectronEnergyRateIonization()
{
}

Real
ElectronEnergyRateIonization::computeQpResidual()
{
  return -_test[_i][_qp] * _kiz[_qp] * _n_gas[_qp] * std::exp(_em[_qp]) * -_Eiz[_qp];
}

Real
ElectronEnergyRateIonization::computeQpJacobian()
{
    _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
    _d_kiz_d_mean_en = _d_kiz_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp];

    return -_test[_i][_qp] * _n_gas[_qp] * std::exp(_em[_qp]) * _d_kiz_d_mean_en * -_Eiz[_qp];
}

Real
ElectronEnergyRateIonization::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
  {
    _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
    _d_kiz_d_em = _d_kiz_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp];

    return -_test[_i][_qp] * _n_gas[_qp] * (_d_kiz_d_em * std::exp(_em[_qp]) + _kiz[_qp] * std::exp(_em[_qp]) * _phi[_j][_qp]) * -_Eiz[_qp];
  }

  else
    return 0.0;
}
