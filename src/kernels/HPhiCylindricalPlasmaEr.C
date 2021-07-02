#include "HPhiCylindricalPlasmaEr.h"

registerMooseObject("ZapdosApp", HPhiCylindricalPlasmaEr);

InputParameters
HPhiCylindricalPlasmaEr::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "ADKernel implementation of Faraday's Law of Induction, calculating $E_r$ for a TM mode in "
      "2D cylindrical coordinates, where $H = H_{\\phi}$ (a scalar component into the page) and "
      "$\\eps_r$ is determined by a plasma dielectric constant.");
  MooseEnum component("real imaginary", "real");
  params.addParam<MooseEnum>(
      "component",
      component,
      "Component of the H field variable, real or imaginary (default = real).");
  params.addRequiredCoupledVar("real_field", "Real field variable.");
  params.addRequiredCoupledVar("imaginary_field", "Imaginary field variable.");
  params.addRequiredCoupledVar("real_Hphi", "Real HPhi field variable.");
  params.addRequiredCoupledVar("imaginary_HPhi", "Imaginary HPhi field variable.");
  params.addRequiredParam<Real>("driving_frequency", "Driving frequency of the system (in Hz).");
  return params;
}

HPhiCylindricalPlasmaEr::HPhiCylindricalPlasmaEr(const InputParameters & parameters)
  : ADKernel(parameters),
    _frequency(getParam<Real>("driving_frequency")),
    _real_value(adCoupledValue("real_field")),
    _imag_value(adCoupledValue("imaginary_field")),
    _real_Hphi_grad(adCoupledGradient("real_Hphi")),
    _imag_HPhi_grad(adCoupledGradient("imaginary_HPhi")),
    _component(getParam<MooseEnum>("component")),
    _eps_r_real(getADMaterialProperty<Real>("plasma_dielectric_constant_real")),
    _eps_r_imag(getADMaterialProperty<Real>("plasma_dielectric_constant_imag")),
    _eps0(8.8542e-12)
{
}

ADReal
HPhiCylindricalPlasmaEr::computeQpResidual()
{
  ADReal res = 0.0;
  Real omega = 2 * libMesh::pi * _frequency;

  if (_component == REAL)
  {
    res = _test[_i][_qp] * (_real_Hphi_grad[_qp](1) - omega * _eps0 *
                                                          (_eps_r_real[_qp] * _imag_value[_qp] +
                                                           _eps_r_imag[_qp] * _real_value[_qp]));
  }
  else if (_component == IMAGINARY)
  {
    res = _test[_i][_qp] * (_imag_HPhi_grad[_qp](1) + omega * _eps0 *
                                                          (_eps_r_real[_qp] * _real_value[_qp] -
                                                           _eps_r_imag[_qp] * _imag_value[_qp]));
  }

  return res;
}
