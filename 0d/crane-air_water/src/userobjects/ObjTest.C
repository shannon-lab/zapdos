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

#include "ObjTest.h"

registerMooseObject("CraneApp", ObjTest);

template <>
InputParameters
validParams<ObjTest>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params.addRequiredParam<Real>("reaction_coefficient", "The area of the electrode or plasma.");
  return params;
}

ObjTest::ObjTest(const InputParameters & parameters)
  : GeneralUserObject(parameters),
    _reaction_coefficient(getParam<Real>("reaction_coefficient"))
{
}

Real
ObjTest::reaction_coefficient() const
{
  return _reaction_coefficient;
}

void
ObjTest::initialize()
{
}

void
ObjTest::execute()
{
}

void
ObjTest::finalize()
{
}
