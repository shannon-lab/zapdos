#include "PlasmaDielectricConstantCoeffField.h"

registerMooseObject("ZapdosApp", PlasmaDielectricConstantCoeffField);

InputParameters
PlasmaDielectricConstantCoeffField::validParams()
{
  InputParameters params = ADVectorKernel::validParams();
  params.addClassDescription(
      "PlasmaDielectricConstantSecondTimeDerivative implementation for time harmonic electric "
      "field. Only for time-harmonic field solves when the plasma is transient!");
  MooseEnum component("real imaginary", "real");
  params.addParam<MooseEnum>(
      "component",
      component,
      "Component of the field variable, real or imaginary (default = real).");
  params.addRequiredCoupledVar("real_field", "Real field variable");
  params.addRequiredCoupledVar("imaginary_field", "Imaginary field variable");
  params.addRequiredParam<Real>("driving_frequency", "Driving frequency of the system (in Hz).");
  return params;
}

PlasmaDielectricConstantCoeffField::PlasmaDielectricConstantCoeffField(
    const InputParameters & parameters)
  : ADVectorKernel(parameters),
    _frequency(getParam<Real>("driving_frequency")),
    _real_var(getVectorVar("real_field", 0)),
    _imag_var(getVectorVar("imaginary_field", 0)),
    _real_value(adCoupledVectorValue("real_field")),
    _imag_value(adCoupledVectorValue("imaginary_field")),
    _component(getParam<MooseEnum>("component")),
    _eps_r_real(getADMaterialProperty<Real>("plasma_dielectric_constant_real")),
    _eps_r_real_dot(getADMaterialProperty<Real>("plasma_dielectric_constant_real_dot")),
    _eps_r_real_dot_dot(getADMaterialProperty<Real>("plasma_dielectric_constant_real_dot_dot")),
    _eps_r_imag(getADMaterialProperty<Real>("plasma_dielectric_constant_imag")),
    _eps_r_imag_dot(getADMaterialProperty<Real>("plasma_dielectric_constant_imag_dot")),
    _eps_r_imag_dot_dot(getADMaterialProperty<Real>("plasma_dielectric_constant_imag_dot_dot")),
    _c(3e8)
{
}

ADReal
PlasmaDielectricConstantCoeffField::computeQpResidual()
{
  ADRealVectorValue term = 0.0;
  Real omega = 2 * libMesh::pi * _frequency;
  if (_component == REAL)
  {
    term = _eps_r_real_dot_dot[_qp] * _real_value[_qp] -
           _eps_r_imag_dot_dot[_qp] * _imag_value[_qp] -
           2.0 * omega * _eps_r_real_dot[_qp] * _imag_value[_qp] -
           2.0 * omega * _eps_r_imag_dot[_qp] * _real_value[_qp] -
           std::pow(omega, 2) * _eps_r_real[_qp] * _real_value[_qp] -
           std::pow(omega, 2) * _eps_r_imag[_qp] * _imag_value[_qp];
  }
  else if (_component == IMAGINARY)
  {
    term = _eps_r_real_dot_dot[_qp] * _imag_value[_qp] +
           _eps_r_imag_dot_dot[_qp] * _real_value[_qp] +
           2.0 * omega * _eps_r_real_dot[_qp] * _real_value[_qp] -
           2.0 * omega * _eps_r_imag_dot[_qp] * _imag_value[_qp] +
           std::pow(omega, 2) * _eps_r_real[_qp] * _imag_value[_qp] +
           std::pow(omega, 2) * _eps_r_imag[_qp] * _real_value[_qp];
  }

  return _test[_i][_qp] * term / std::pow(_c, 2);
}
