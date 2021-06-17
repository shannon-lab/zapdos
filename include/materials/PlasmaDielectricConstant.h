#pragma once

#include "ADMaterial.h"

/**
 *
 */
class PlasmaDielectricConstant : public ADMaterial
{
public:
  static InputParameters validParams();

  PlasmaDielectricConstant(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  // Value of dielectric constant, real component
  ADMaterialProperty<Real> & _eps_r_real;
  // Second time derivative of dielectric constant, real component
  ADMaterialProperty<Real> & _eps_r_real_dot_dot;
  // Value of dielectric constant, imaginary component
  ADMaterialProperty<Real> & _eps_r_imag;
  // Second time derivative of dielectric constant, imaginary component
  ADMaterialProperty<Real> & _eps_r_imag_dot_dot;

  /// Electron charge
  const Real _elementary_charge;
  /// Electron mass
  const Real _electron_mass;
  /// Vacuum permittivity
  const Real _eps_vacuum;
  /// pi
  const Real _pi;

  /// Electron-neutral collision frequency (Hz)
  const Real & _nu;

  /// Operating frequency (Hz)
  const Real & _frequency;

  /// Electron density coupled variable
  const ADVariableValue & _em;

  /// Electron density variable
  MooseVariable * _em_var;

  /// Electron density first time derivative
  const ADVariableValue & _em_dot;

  /// Electron density second time derivative
  const ADVariableValue & _em_dot_dot;
};
