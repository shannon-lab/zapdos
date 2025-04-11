#pragma once

#include "ADMaterial.h"

/**
 * Material object that provides an interface to an external electromagnetic
 * field solver for all Zapdos objects via the "field" material property. Default
 * is an electrostatic interface, where the `potential` coupled variable parameter
 * must be provided.
 */
class FieldSolverMaterial : public ADMaterial
{
public:
  static InputParameters validParams();

  FieldSolverMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// Gradient of coupled electrostatic potential
  const ADVariableGradient & _grad_potential;

  /// Coupled electric field variable
  const ADVectorVariableValue & _electric_field;

  /// Electric field material property
  ADMaterialProperty<RealVectorValue> & _field;

  /// Variable that holds user solver setting (electrostatic or electromagnetic)
  const MooseEnum _mode;
};
