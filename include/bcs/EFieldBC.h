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

#ifndef EFIELDBC_H
#define EFIELDBC_H

#include "IntegratedBC.h"


class EFieldBC;

template<>
InputParameters validParams<EFieldBC>();

/**
 * Implements a simple constant Neumann BC where grad(u)=value on the boundary.
 * Uses the term produced from integrating the diffusion operator by parts.
 */
class EFieldBC : public IntegratedBC
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  EFieldBC(const InputParameters & parameters);


protected:
  virtual Real computeQpResidual();

  // Input Parameters

  const Real & _x_boundary_e_field;
  const Real & _y_boundary_e_field;
  const Real & _z_boundary_e_field;

  // Material Properties

  const MaterialProperty<Real> & _eps_r;
  const MaterialProperty<Real> & _potential_mult;

  // Members unique to object

  RealVectorValue _e_field;
};


#endif //EFIELDBC_H
