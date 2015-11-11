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
#include "Test.h"

template<>
InputParameters validParams<Test>()
{
  InputParameters params = validParams<Material>();
  return params;
}


Test::Test(const InputParameters & parameters) :
  Material(parameters),

  // Declare material properties. 
  _diff(declareProperty<Real>("diff"))
{
}

void
Test::computeQpProperties()
{
  _diff[_qp] = 1.;
}
