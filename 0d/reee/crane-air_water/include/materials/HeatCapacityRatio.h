/****************************************************************/
/*                      DO NOT MODIFY THIS HEADER               */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*              (c) 2010 Battelle Energy Alliance, LLC          */
/*                      ALL RIGHTS RESERVED                     */
/*                                                              */
/*              Prepared by Battelle Energy Alliance, LLC       */
/*              Under Contract No. DE-AC07-05ID14517            */
/*              With the U. S. Department of Energy             */
/*                                                              */
/*              See COPYRIGHT for full restrictions             */
/****************************************************************/
#pragma once

// #include "Material.h"
#include "SpeciesSum.h"

class HeatCapacityRatio;

template <>
InputParameters validParams<HeatCapacityRatio>();

class HeatCapacityRatio : public SpeciesSum
{
public:
  HeatCapacityRatio(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();
  MaterialProperty<Real> & _gamma_heat;
  const std::vector<std::string> & _species;
  const MaterialProperty<Real> & _species_sum;
  const VariableValue & _Tgas;
  std::vector<std::vector<Real>> _polynomial_coefficients;
  std::vector<Real> _molar_heat_capacity;

private:
  std::vector<const VariableValue *> _vals;

};
