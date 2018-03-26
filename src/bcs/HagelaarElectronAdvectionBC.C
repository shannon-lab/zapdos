#include "HagelaarElectronAdvectionBC.h"

registerMooseObject("ZapdosApp", HagelaarElectronAdvectionBC);

template <>
InputParameters
validParams<HagelaarElectronAdvectionBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("mean_en", "The mean energy.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

HagelaarElectronAdvectionBC::HagelaarElectronAdvectionBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),

    _muem(getMaterialProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _a(0.5),
    //      _v_thermal(0),
    //      _d_v_thermal_d_u(0),
    //      _d_v_thermal_d_mean_en(0),
    _actual_mean_en(0)
{
}

Real
HagelaarElectronAdvectionBC::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  //      _v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI *
  //      _massem[_qp]));

  return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) *
         (-(2 * _a - 1) * _muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) *
          _normals[_qp]);
}

Real
HagelaarElectronAdvectionBC::computeQpJacobian()
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  _actual_mean_en = std::exp(_mean_en[_qp] - _u[_qp]);
  //      _v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI *
  //      _massem[_qp]));
  //      _d_v_thermal_d_u = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] -
  //      _u[_qp]) / (M_PI * _massem[_qp]) * -_phi[_j][_qp];

  return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) *
         (-(2 * _a - 1) * _muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) *
              _phi[_j][_qp] * _normals[_qp] -
          (2. * _a - 1.) * _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp] *
              -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) * _normals[_qp]);
}

Real
HagelaarElectronAdvectionBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
      _a = 1.0;
    else
      _a = 0.0;

    //              _v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp])
    //              / (M_PI * _massem[_qp]));

    return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) *
           (-(2 * _a - 1) * _muem[_qp] * -_grad_phi[_j][_qp] * _r_units * std::exp(_u[_qp]) *
            _normals[_qp]);
  }

  else if (jvar == _mean_en_id)
  {
    if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    //              _v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp])
    //              / (M_PI * _massem[_qp]));
    //              _d_v_thermal_d_mean_en  = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 *
    //              std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]) * _phi[_j][_qp];
    _actual_mean_en = std::exp(_mean_en[_qp] - _u[_qp]);

    return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) *
           (-(2 * _a - 1) * _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp] *
            -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) * _normals[_qp]);
  }

  else
    return 0.0;
}
