#pragma once

#include "ADVectorKernel.h"

/**
 *
 */
class PlasmaDielectricConstantCoeffField : public ADVectorKernel
{
public:
  static InputParameters validParams();

  PlasmaDielectricConstantCoeffField(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// System driving frequency (in Hz)
  const Real _frequency;

  /// Real field variable value
  const ADVectorVariableValue & _real_value;
  /// Imaginary field variable value
  const ADVectorVariableValue & _imag_value;

  /// Field component (real or imaginary)
  MooseEnum _component;

  /// Plasma dielectric constant, real component
  const ADMaterialProperty<Real> & _eps_r_real;
  /// Plasma dielectric constant first time derivative, real component
  const ADMaterialProperty<Real> & _eps_r_real_dot;
  /// Plasma dielectric constant second time derivative, real component
  const ADMaterialProperty<Real> & _eps_r_real_dot_dot;
  /// Plasma dielectric constant, imaginary component
  const ADMaterialProperty<Real> & _eps_r_imag;
  /// Plasma dielectric constant first time derivative, imaginary component
  const ADMaterialProperty<Real> & _eps_r_imag_dot;
  /// Plasma dielectric constant second time derivative, imaginary component
  const ADMaterialProperty<Real> & _eps_r_imag_dot_dot;

  /// Speed of light (in DielectricConstantSecondTimeDerivative, used to represent 1 / sqrt(mu_0 * eps_0))
  const int _c;

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
