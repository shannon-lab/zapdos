#include "ElectronProductSecondOrderLog.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ElectronProductSecondOrderLog);

template <>
InputParameters
validParams<ElectronProductSecondOrderLog>()
{
  InputParameters params = validParams<Kernel>();
  params.addCoupledVar("electron", "The electron species variable.");
  params.addCoupledVar("target", "The target species variable.");
  params.addRequiredCoupledVar("energy",
                               "The energy variable. (Required for jacobian term. Ignore if "
                               "reaction rate is a constant value.)");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<bool>("_electron_eq_u", false, "If v == u.");
  params.addParam<bool>("_target_eq_u", false, "If w == u.");
  // params.addParam<bool>("v_electron", false, "If v corresponds to electrons.");
  // params.addParam<bool>("w_electron", false, "If w corresponds to electrons.");
  return params;
}

ElectronProductSecondOrderLog::ElectronProductSecondOrderLog(const InputParameters & parameters)
  : Kernel(parameters),
    _electron(isCoupled("electron") ? coupledValue("electron") : _zero),
    _target(isCoupled("target") ? coupledValue("target") : _zero),
    _energy(coupledValue("energy")),
    _electron_id(isCoupled("electron") ? coupled("electron") : 0),
    _target_id(isCoupled("target") ? coupled("target") : 0),
    _energy_id(coupled("energy")),
    _n_gas(getMaterialProperty<Real>("n_gas")),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _d_k_d_en(getMaterialProperty<Real>("d_k_d_en_" + getParam<std::string>("reaction"))),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _electron_eq_u(getParam<bool>("_electron_eq_u")),
    _target_eq_u(getParam<bool>("_target_eq_u")),
    _target_coupled(isCoupled("target") ? true : false)
{
}

Real
ElectronProductSecondOrderLog::computeQpResidual()
{
  Real mult2;

  if (_target_coupled)
    mult2 = std::exp(_target[_qp]);
  else
  {
    mult2 = _n_gas[_qp];
  }
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_electron[_qp]) *
         mult2;
}

Real
ElectronProductSecondOrderLog::computeQpJacobian()
{
  Real mult2;
  Real actual_mean_en, d_ame_d_electron;

  if (!_target_eq_u && !_electron_eq_u)
  {
    return 0.0;
  }
  else
  {
    if (_target_coupled)
      mult2 = std::exp(_target[_qp]);
    else
      mult2 = _n_gas[_qp];

    if (_electron_eq_u)
    {
      actual_mean_en = std::exp(_energy[_qp] - _electron[_qp]);
      d_ame_d_electron = -actual_mean_en;
    }
    else
      d_ame_d_electron = 0.0;

    return -_test[_i][_qp] * _stoichiometric_coeff *
           (_reaction_coeff[_qp] + (_d_k_d_en[_qp] * d_ame_d_electron)) * std::exp(_electron[_qp]) *
           mult2 * _phi[_j][_qp];
  }
  // else
  // {
  // power = 0.0;
  // gas_mult = 1.0;
  // k_deriv_mult = 0;
  //
  // if (_target_coupled)
  //   mult2 = std::exp(_target[_qp]);
  // else
  //   mult2 = _n_gas[_qp];
  //
  // if (_electron_eq_u)
  // {
  //   power += 1.0;
  //   actual_mean_en = std::exp(_energy[_qp] - _electron[_qp]);
  //   d_ame_d_electron = -actual_mean_en;  // Multiplied by _phi[_j][_qp] at the end
  // }
  // else
  //   d_ame_d_electron = 0.0;
  //
  // if (_target_coupled && _target_eq_u)
  //   power += 1.0;
  //
  // gas_mult *= std::exp(_electron[_qp]) * mult2;
  //
  // return -_test[_i][_qp] * _stoichiometric_coeff * power * (_reaction_coeff[_qp] +
  // (_d_k_d_en[_qp] * d_ame_d_electron)) * gas_mult * _phi[_j][_qp];
  // }
}

Real
ElectronProductSecondOrderLog::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real mult2, actual_mean_en, d_ame_d_electron, d_ame_d_energy;
  // Real rate_constant;

  if (_target_coupled)
    mult2 = std::exp(_target[_qp]);
  else
    mult2 = _n_gas[_qp];

  if (!_electron_eq_u && jvar == _electron_id)
  {
    actual_mean_en = std::exp(_energy[_qp] - _electron[_qp]);
    d_ame_d_electron = -actual_mean_en;

    return -_test[_i][_qp] * _stoichiometric_coeff *
           (_reaction_coeff[_qp] + (_d_k_d_en[_qp] * d_ame_d_electron)) * std::exp(_electron[_qp]) *
           mult2 * _phi[_j][_qp];
  }
  else if (_target_coupled && !_target_eq_u && jvar == _target_id)
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] *
           std::exp(_electron[_qp]) * mult2 * _phi[_j][_qp];
  }
  else if (jvar == _energy_id)
  {
    actual_mean_en = std::exp(_energy[_qp] - _electron[_qp]);
    d_ame_d_energy = actual_mean_en;

    return -_test[_i][_qp] * _stoichiometric_coeff * (_d_k_d_en[_qp] * d_ame_d_energy) *
           std::exp(_electron[_qp]) * mult2 * _phi[_j][_qp];
  }
  else
    return 0.0;

  // if (!_electron_eq_u && jvar==_electron_id)
  // {
  //   power += 1;
  //   actual_mean_en = std::exp(_energy[_qp] - _electron[_qp]);
  //   d_ame_d_electron = -actual_mean_en;
  // }
  // else
  //   d_ame_d_electron = 0.0;
  //
  //
  // if (_target_coupled && !_target_eq_u && jvar==_target_id)
  //   power += 1;
  //
  // // Since these are in exponential form, the exp(dens1 + dens2) term always exists regardless!
  // gas_mult = mult1 * mult2;
  //
  // return -_test[_i][_qp] * _stoichiometric_coeff * (_reaction_coeff[_qp] + (_d_k_d_en[_qp] *
  // d_ame_d_electron)) * gas_mult * power * _phi[_j][_qp];
}
