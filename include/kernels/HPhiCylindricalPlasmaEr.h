#pragma once

#include "ADKernel.h"

/**
 * ADKernel implementation of Faraday's Law of Induction, calculating $E_r$ for a TM mode in
 * 2D cylindrical coordinates, where $H = H_{\\phi}$ (a scalar component into the page) and
 * $\\eps_r$ is determined by a plasma dielectric constant.
 */
class HPhiCylindricalPlasmaEr : public ADKernel
{
public:
  static InputParameters validParams();
  HPhiCylindricalPlasmaEr(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// System driving frequency (in Hz)
  const Real _frequency;

  /// Real field variable value
  const ADVariableValue & _real_value;
  /// Imaginary field variable value
  const ADVariableValue & _imag_value;

  /// Hphi coupled variable gradient, real component
  const ADVariableGradient & _real_Hphi_grad;
  ///HPhi coupled variable gradient, imaginary component
  const ADVariableGradient & _imag_HPhi_grad;

  /// Field component (real or imaginary)
  MooseEnum _component;

  /// Plasma dielectric constant, real component
  const ADMaterialProperty<Real> & _eps_r_real;
  /// Plasma dielectric constant, imaginary component
  const ADMaterialProperty<Real> & _eps_r_imag;

  /// Vacuum permittivity
  const Real _eps0;

private:
  /**
   * Enum used in comparisons with _component. Enum-to-enum comparisons are a bit
   * more lightweight, so we should create another enum with the possible choices.
   */
  enum ComponentEnum
  {
    REAL,
    IMAGINARY
  };
};
