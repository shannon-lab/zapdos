#pragma once

#include "ADTimeKernel.h"

/**
 *
 */
class PlasmaDielectricConstantSecondTimeDerivative : public ADVectorTimeKernel
{
public:
  static InputParameters validParams();

  PlasmaDielectricConstantSecondTimeDerivative(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Real field variable
  VectorMooseVariable * _real_var;
  /// Imaginary field variable
  VectorMooseVariable * _imag_var;
  /// Real field variable value
  const ADVectorVariableValue & _real_value;
  /// Imaginary field variable value
  const ADVectorVariableValue & _imag_value;
  /// Real field second time derivative
  const ADVectorVariableValue & _real_dot_dot;
  /// Imaginary field second time derivative
  const ADVectorVariableValue & _imag_dot_dot;

  /// Field component (real or imaginary)
  MooseEnum _component;

  /// Plasma dielectric constant, real component
  const ADMaterialProperty<Real> & _eps_r_real;
  /// Plasma dielectric constant second time derivative, real component
  const ADMaterialProperty<Real> & _eps_r_real_dot_dot;
  /// Plasma dielectric constant, imaginary component
  const ADMaterialProperty<Real> & _eps_r_imag;
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
