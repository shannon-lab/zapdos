#include "ElectronReactantSecondOrderLog.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ElectronReactantSecondOrderLog);

template <>
InputParameters
validParams<ElectronReactantSecondOrderLog>()
{
  InputParameters params = validParams<Kernel>();
  params.addCoupledVar("v", "The first variable that is reacting to create u.");
  params.addRequiredCoupledVar("energy", "The energy variable. (For jacobian calculation.)");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<bool>("_v_eq_electron", false, "Whether or not v is the electron variable.");
  return params;
}

ElectronReactantSecondOrderLog::ElectronReactantSecondOrderLog(const InputParameters & parameters)
  : Kernel(parameters),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _d_k_d_en(getMaterialProperty<Real>("d_k_d_en_" + getParam<std::string>("reaction"))),
    _v(isCoupled("v") ? coupledValue("v") : _zero),
    _energy(coupledValue("energy")),
    _v_id(isCoupled("v") ? coupled("v") : 0),
    _energy_id(coupled("energy")),
    _n_gas(getMaterialProperty<Real>("n_gas")),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_electron(getParam<bool>("_v_eq_electron"))
{
}

Real
ElectronReactantSecondOrderLog::computeQpResidual()
{
  if (isCoupled("v"))
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_v[_qp]) *
           std::exp(_u[_qp]);
  }
  else
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _n_gas[_qp] *
           std::exp(_u[_qp]);
}

Real
ElectronReactantSecondOrderLog::computeQpJacobian()
{
  // Note that if !_v_eq_electron, then by definition _var is the electron variable.
  Real d_ame_d_en, actual_mean_en;

  if (!_v_eq_electron)
  {
    actual_mean_en = std::exp(_energy[_qp] - _u[_qp]);
    d_ame_d_en = -actual_mean_en;
  }
  else
    d_ame_d_en = 0.0;

  if (isCoupled("v"))
    return -_test[_i][_qp] * _stoichiometric_coeff *
           (_reaction_coeff[_qp] + (_d_k_d_en[_qp] * d_ame_d_en)) * std::exp(_v[_qp]) *
           std::exp(_u[_qp]) * _phi[_j][_qp];
  else
    return -_test[_i][_qp] * _stoichiometric_coeff *
           (_reaction_coeff[_qp] + (_d_k_d_en[_qp] * d_ame_d_en)) * _n_gas[_qp] *
           std::exp(_u[_qp]) * _phi[_j][_qp];
}

Real
ElectronReactantSecondOrderLog::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real mult1, actual_mean_en, d_k_d_electron;

  if (isCoupled("v"))
    mult1 = std::exp(_v[_qp]);
  else
    mult1 = _n_gas[_qp];

  if (isCoupled("v") && jvar == _v_id)
  {
    // if _v_eq_electron, then dk/den needs to be taken into account.
    // if !_v_eq_electron, dk/den is taken into account in the on-diagonal jacobian term.
    if (_v_eq_electron)
    {
      actual_mean_en = std::exp(_energy[_qp] - _v[_qp]);
      d_k_d_electron = -actual_mean_en;

      return -_test[_i][_qp] * _stoichiometric_coeff *
             (_reaction_coeff[_qp] + (_d_k_d_en[_qp] * d_k_d_electron)) * std::exp(_u[_qp]) *
             mult1 * _phi[_j][_qp];
    }
    else
    {
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_u[_qp]) *
             mult1 * _phi[_j][_qp];
    }
  }
  else if (jvar == _energy_id)
  {
    if (_v_eq_electron)
      actual_mean_en = std::exp(_energy[_qp] - _v[_qp]);
    else
      actual_mean_en = std::exp(_energy[_qp] - _u[_qp]);

    return -_test[_i][_qp] * _stoichiometric_coeff * (_d_k_d_en[_qp] * actual_mean_en) *
           std::exp(_u[_qp]) * mult1 * _phi[_j][_qp];
  }
  else
    return 0.0;

  // if (isCoupled("v"))
  // {
  //   if (jvar == _v_id)
  //     return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_u[_qp]) *
  //     std::exp(_v[_qp]) * _phi[_j][_qp];
  //   else
  //     return 0.0;
  // }
  // else
  // {
  //   return 0.0;
  // }
}
