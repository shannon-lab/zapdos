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
#include "Test2.h"

template<>
InputParameters validParams<Test2>()
{
  InputParameters params = validParams<Material>();
  return params;
}


Test2::Test2(const InputParameters & parameters) :
  Material(parameters),

  // Declare material properties. 
  _diff(declareProperty<Real>("diff"))
{
}

void
Test2::computeQpProperties()
{
  _diff[_qp] = 4.;
}
