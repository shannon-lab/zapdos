#include "ProductSecondOrder.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ProductSecondOrder);

template <>
InputParameters
validParams<ProductSecondOrder>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("v", "The first variable that is reacting to create u.");
  params.addRequiredCoupledVar("w", "The second variable that is reacting to create u.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<bool>("_v_eq_u", false, "Whether or not v and u are the same variable.");
  params.addParam<bool>("_w_eq_u", false, "Whether or not w and u are the same variable.");
  return params;
}

ProductSecondOrder::ProductSecondOrder(const InputParameters & parameters)
  : Kernel(parameters),
    _v(coupledValue("v")),
    _w(coupledValue("w")),
    _v_id(coupled("v")),
    _w_id(coupled("w")),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("_v_eq_u")),
    _w_eq_u(getParam<bool>("_w_eq_u"))
{
}

Real
ProductSecondOrder::computeQpResidual()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _v[_qp] * _w[_qp];
}

Real
ProductSecondOrder::computeQpJacobian()
{
  if (_v_eq_u && _w_eq_u)
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 2.0 * _v[_qp] *
           _phi[_j][_qp];
  }
  else if (_v_eq_u && !_w_eq_u)
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _w[_qp] * _phi[_j][_qp];
  }
  else if (!_v_eq_u && _w_eq_u)
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _v[_qp] * _phi[_j][_qp];
  }
  else
  {
    return 0.0;
  }
  /*
  Real power, eq_u_mult, gas_mult;
  power = 0.0;
  eq_u_mult = 1.0;
  gas_mult = 1.0;

  if (_v_eq_u)
  {
    power += 1.0;
    eq_u_mult *= _v[_qp];
  }
  else
    gas_mult *= _v[_qp];

  if (_w_eq_u)
  {
    power += 1.0;
    eq_u_mult *= _w[_qp];
  }
  else
    gas_mult *= _w[_qp];

  if (!_v_eq_u && !_w_eq_u)
  {
    return 0.0;
  }
  else
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * power * _reaction_coeff[_qp] *
           std::pow(eq_u_mult, power - 1) * gas_mult * _phi[_j][_qp];
  }
  */
}

Real
ProductSecondOrder::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (_v_eq_u && !_w_eq_u)
  {
    if (jvar == _w_id)
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _v[_qp] *
             _phi[_j][_qp];
    else
      return 0.0;
  }
  else if (!_v_eq_u && _w_eq_u)
  {
    if (jvar == _w_id)
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _w[_qp] *
             _phi[_j][_qp];
    else
      return 0.0;
  }
  else if (!_v_eq_u && !_w_eq_u)
  {
    if (jvar == _v_id && jvar == _w_id)
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 2.0 * _v[_qp] *
             _phi[_j][_qp];
    else if (jvar == _v_id && jvar != _w_id)
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _w[_qp] *
             _phi[_j][_qp];
    else if (jvar != _v_id && jvar == _w_id)
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _v[_qp] *
             _phi[_j][_qp];
    else
      return 0.0;
  }
  else
    return 0.0;
  /*
  Real eq_u_mult, j_mult, power;
  eq_u_mult = 1.0;
  j_mult = 1.0;
  power = 0.0;

  if (_v_eq_u)
  {
    eq_u_mult *= _v[_qp];
  }
  else if (jvar == _v_id)
  {
    power += 1.0;
    j_mult *= _v[_qp];
  }

  if (_w_eq_u)
  {
    eq_u_mult *= _w[_qp];
  }
  else if (jvar == _w_id)
  {
    power += 1.0;
    j_mult *= _w[_qp];
  }

  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::pow(j_mult, power) *
         eq_u_mult * _phi[_j][_qp];

  */

  /*if (_v_eq_u && _w_eq_u)
  {
    return 0.0;
  }
  else if (!_v_eq_u && jvar == _v_id)
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * *_phi[_j][_qp];
  }
  else if ((isCoupled("w") && !_w_eq_u) && !isCoupled("v"))
  {
    if (jvar == _w_id)
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * mult1 * _phi[_j][_qp];
    else
      return 0.0;
  }
  else if (isCoupled("v") && isCoupled("w"))
  {
    if (!_v_eq_u && !_w_eq_u)
    {
      if (_v_id != _w_id)
      {
        if (jvar == _v_id)
          return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * mult2 *
                 _phi[_j][_qp];
        else if (jvar == _w_id)
          return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * mult1 *
                 _phi[_j][_qp];
        else
          return 0.0;
      }
      else
      {
        if (jvar == _v_id)
          return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 2.0 * mult1 *
                 _phi[_j][_qp];
        else
          return 0.0;
      }
    }
    else if (_v_eq_u && !_w_eq_u)
    {
      if (jvar == _w_id)
        return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * mult1 *
               _phi[_j][_qp];
      else
        return 0.0;
    }
    else if (!_v_eq_u && _w_eq_u)
    {
      if (jvar == _v_id)
        return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * mult2 *
               _phi[_j][_qp];
      else
        return 0.0;
    }
    else
      return 0.0;
  }
  else
  {
    // std::cout << getParam<std::string>("reaction") << ": " << _v_eq_u << ", " << _w_eq_u <<
    // std::endl;
    mooseError("ProductSecondOrder, computeQpOffDiagJacobian: this is not yet implemented for the "
               "current case.");
  }*/
}
