#pragma once

#include "ADKernel.h"

/**
 * ADKernel implementation of $\\nabla \\times (\\frac{1}{\\eps_r} \\nabla \\times H)$
 * for a TM mode in 2D cylindrical coordinates, where $H = H_{\\phi}$ (a scalar
 * component into the page) and $\\eps_r$ is determined by a plasma dielectric
 * constant.
 */
class HPhiCylindricalPlasmaCurlCurl : public ADKernel
{
public:
  static InputParameters validParams();
  HPhiCylindricalPlasmaCurlCurl(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// System driving frequency (in Hz)
  const Real _frequency;

  /// Real field variable value
  const ADVariableValue & _real_value;
  /// Real field variable gradient
  const ADVariableGradient & _real_grad;
  /// Imaginary field variable value
  const ADVariableValue & _imag_value;
  /// Imaginary field variable gradient
  const ADVariableGradient & _imag_grad;

  /// Field component (real or imaginary)
  MooseEnum _component;

  /// Plasma dielectric constant, real component
  const ADMaterialProperty<Real> & _eps_r_real;
  /// Plasma dielectric constant gradient, real component
  const ADMaterialProperty<RealVectorValue> & _eps_r_real_grad;
  /// Plasma dielectric constant, imaginary component
  const ADMaterialProperty<Real> & _eps_r_imag;
  /// Plasma dielectric constant gradient, imaginary component
  const ADMaterialProperty<RealVectorValue> & _eps_r_imag_grad;

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
