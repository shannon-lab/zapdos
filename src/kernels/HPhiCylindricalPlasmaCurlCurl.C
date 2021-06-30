#include "HPhiCylindricalPlasmaCurlCurl.h"

registerMooseObject("ZapdosApp", HPhiCylindricalPlasmaCurlCurl);

InputParameters
HPhiCylindricalPlasmaCurlCurl::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "ADKernel implementation of $\\nabla \\times (\\frac{1}{\\eps_r} \\nabla \\times H)$ for a TM mode in "
      "2D cylindrical coordinates, where $H = H_{\\phi}$ (a scalar component into the page) and $\\eps_r$ is "
      "determined by a plasma dielectric constant.");
  MooseEnum component("real imaginary", "real");
  params.addParam<MooseEnum>(
      "component",
      component,
      "Component of the H field variable, real or imaginary (default = real).");
  params.addRequiredCoupledVar("real_field", "Real field variable.");
  params.addRequiredCoupledVar("imaginary_field", "Imaginary field variable.");
  params.addRequiredParam<Real>("driving_frequency", "Driving frequency of the system (in Hz).");
  return params;
}

HPhiCylindricalPlasmaCurlCurl::HPhiCylindricalPlasmaCurlCurl(const InputParameters & parameters)
  : ADKernel(parameters),
  _frequency(getParam<Real>("driving_frequency")),
  _real_value(adCoupledValue("real_field")),
  _real_grad(adCoupledGradient("real_field")),
  _imag_value(adCoupledValue("imag_field")),
  _imag_grad(adCoupledGradient("imag_field")),
  _component(getParam<MooseEnum>("component")),
  _eps_r_real(getADMaterialProperty<Real>("plasma_dielectric_constant_real")),
  _eps_r_real_grad(getADMaterialProperty<RealVectorValue>("plasma_dielectric_constant_real_grad")),
  _eps_r_imag(getADMaterialProperty<Real>("plasma_dielectric_constant_imag")),
  _eps_r_imag_grad(getADMaterialProperty<RealVectorValue>("plasma_dielectric_constant_imag_grad"))
{
}

ADReal
HPhiCylindricalPlasmaCurlCurl::computeQpResidual()
{
  // Initialize needed ADReals
  ADReal term1 = 0.0;
  ADReal term2 = 0.0;
  ADReal term3 = 0.0;
  ADReal term4 = 0.0;
  ADReal term5 = 0.0;

  // Set values needed often in component calculations below
  ADReal inverse_eps_r_real = _eps_r_real[_qp] / (std::pow(_eps_r_real[_qp], 2) + std::pow(_eps_r_imag[_qp], 2));
  ADReal inverse_eps_r_imag = -_eps_r_imag[_qp] / (std::pow(_eps_r_real[_qp], 2) + std::pow(_eps_r_imag[_qp], 2));
  ADReal inverse_eps_r_squared_real = std::pow(inverse_eps_r_real, 2) - std::pow(inverse_eps_r_imag, 2);
  ADReal inverse_eps_r_squared_imag = -2.0 * inverse_eps_r_real * inverse_eps_r_imag;

  if (_component == REAL)
  {
    term1 = -_grad_test[_i][_qp] * (inverse_eps_r_real * _real_grad[_qp] + inverse_eps_r_imag * _imag_grad[_qp]);
    term2 = _test[_i][_qp] * (-1.0 / std::pow(_q_point[_qp](0), 2)) * (_real_value[_qp] * inverse_eps_r_real + _imag_value[_qp] * inverse_eps_r_imag);
    term3 = _test[_i][_qp] * (-1.0 / _q_point[_qp](0)) * ((inverse_eps_r_squared_real * _real_value[_qp] - inverse_eps_r_squared_imag * _imag_value[_qp]) * _eps_r_real_grad[_qp](0) - (inverse_eps_r_squared_real * _imag_value[_qp] + inverse_eps_r_squared_imag * _real_value[_qp]) * _eps_r_imag_grad[_qp](0));
    term4 = _test[_i][_qp] * -1.0 * ((inverse_eps_r_squared_real * _eps_r_real_grad[_qp](0) - inverse_eps_r_squared_imag * _eps_r_imag_grad[_qp](0)) * _real_grad[_qp](0) - (inverse_eps_r_squared_real * _eps_r_imag_grad[_qp](0) + inverse_eps_r_squared_imag * _eps_r_real_grad[_qp](0)) * _imag_grad[_qp](0));
    term5 = _test[_i][_qp] * -1.0 * ((inverse_eps_r_squared_real * _eps_r_real_grad[_qp](1) - inverse_eps_r_squared_imag * _eps_r_imag_grad[_qp](1)) * _real_grad[_qp](1) - (inverse_eps_r_squared_real * _eps_r_imag_grad[_qp](1) + inverse_eps_r_squared_imag * _eps_r_real_grad[_qp](1)) * _imag_grad[_qp](1));
  }
  else if (_component == IMAGINARY)
  {
    term1 = -_grad_test[_i][_qp] * (inverse_eps_r_real * _imag_grad[_qp] - inverse_eps_r_imag * _real_grad[_qp]);
    term2 = _test[_i][_qp] * (-1.0 / std::pow(_q_point[_qp](0), 2)) * (_imag_value[_qp] * inverse_eps_r_real - _real_value[_qp] * inverse_eps_r_imag);
    term3 = _test[_i][_qp] * (-1.0 / _q_point[_qp](0)) * ((inverse_eps_r_squared_real * _real_value[_qp] - inverse_eps_r_squared_imag * _imag_value[_qp]) * _eps_r_imag_grad[_qp](0) + (inverse_eps_r_squared_real * _imag_value[_qp] + inverse_eps_r_squared_imag * _real_value[_qp]) * _eps_r_real_grad[_qp](0));
    term4 = _test[_i][_qp] * -1.0 * ((inverse_eps_r_squared_real * _eps_r_real_grad[_qp](0) - inverse_eps_r_squared_imag * _eps_r_imag_grad[_qp](0)) * _imag_grad[_qp](0) + (inverse_eps_r_squared_real * _eps_r_imag_grad[_qp](0) + inverse_eps_r_squared_imag * _eps_r_real_grad[_qp](0)) * _real_grad[_qp](0));
    term5 = _test[_i][_qp] * -1.0 * ((inverse_eps_r_squared_real * _eps_r_real_grad[_qp](1) - inverse_eps_r_squared_imag * _eps_r_imag_grad[_qp](1)) * _imag_grad[_qp](1) + (inverse_eps_r_squared_real * _eps_r_imag_grad[_qp](1) + inverse_eps_r_squared_imag * _eps_r_real_grad[_qp](1)) * _real_grad[_qp](1));
  }

  return term1 + term2 + term3 + term4 + term5;
}
