#include "IonRateIonization.h"


template<>
InputParameters validParams<IonRateIonization>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("mean_en","The electron mean energy.");
  params.addRequiredCoupledVar("em", "The electron density");
  return params;
}


IonRateIonization::IonRateIonization(const InputParameters & parameters) :
    Kernel(parameters),

    _kiz(getMaterialProperty<Real>("kiz")),
    _d_kiz_d_actual_mean_en(getMaterialProperty<Real>("d_kiz_d_actual_mean_en")),

    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),
    _em(coupledValue("em")),
    _em_id(coupled("em"))
{
}

IonRateIonization::~IonRateIonization()
{
}

Real
IonRateIonization::computeQpResidual()
{
  return -_test[_i][_qp] * _kiz[_qp] * _n_gas[_qp] * std::exp(_em[_qp]);
}

Real
IonRateIonization::computeQpJacobian()
{
  return 0.;
}

Real
IonRateIonization::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _mean_en_id)
  {
    _actual_mean_en = std::exp(_mean_en[_qp] - _em[_qp]);
    _d_kiz_d_mean_en = _d_kiz_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp];

    return -_test[_i][_qp] * _n_gas[_qp] * std::exp(_em[_qp]) * _d_kiz_d_mean_en;
  }

  else if (jvar == _em_id)
  {
    _actual_mean_en = std::exp(_mean_en[_qp] - _em[_qp]);
    _d_kiz_d_em = _d_kiz_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp];

    return -_test[_i][_qp] * _n_gas[_qp] * (_d_kiz_d_em * std::exp(_em[_qp]) + _kiz[_qp] * std::exp(_em[_qp]) * _phi[_j][_qp]);
  }

  else
    return 0.0;
}
