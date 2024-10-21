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

#include "Material.h"

class SuperelasticReactionRate;

template <>
InputParameters validParams<SuperelasticReactionRate>();

class SuperelasticReactionRate : public Material
{
public:
  SuperelasticReactionRate(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  MaterialProperty<Real> & _reaction_rate;
  MaterialProperty<Real> & _enthalpy_reaction;
  const MaterialProperty<Real> & _reversible_rate;
  const std::vector<Real> & _coefficients;
  const std::vector<std::string> & _participants;
  const VariableValue & _Tgas;

  Real _power_coefficient;
  std::vector<Real> delta_a;
  Real _equilibrium_constant;

};
