/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
#ifndef AIR_H_
#define AIR_H_

#include "Material.h"

// A helper class from MOOSE that linear interpolates x,y data
#include "LinearInterpolation.h"

class Air;

template<>
InputParameters validParams<Air>();

/**
 * Material objects inherit from Material and override computeQpProperties.
 *
 * Their job is to declare properties for use by other objects in the
 * calculation such as Kernels and BoundaryConditions.
 */
class Air : public Material
{
public:
  Air(const std::string & name, InputParameters parameters);

protected:
  /**
   * Necessary override.  This is where the values of the properties
   * are computed.
   */
  virtual void computeQpProperties();

  /// The radius of the balls in the column
  const Real & _velocity_multiplier;
  const Real & _relative_permittivity;

  /// Coefficient in expression for velocity
  MaterialProperty<Real> & _velocity_coeff;
  MaterialProperty<Real> & _permittivity;
  MaterialProperty<Real> & _coulomb_charge;
};

#endif //AIR_H
