

#pragma once

#include "Material.h"

// Forward Declarations
class ParticleConservation;

template <>
InputParameters validParams<ParticleConservation>();


class ParticleConservation : public Material
{
public:
  static InputParameters validParams();

  ParticleConservation(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;


private:

  const MaterialProperty<Real> & _gas_temp;
  const MaterialProperty<Real> & _gas_pressure;
  std::vector<const VariableValue *>  _other_densities;
  ADMaterialProperty<Real> & _conserved_density;
  unsigned int _num_ions;
};
