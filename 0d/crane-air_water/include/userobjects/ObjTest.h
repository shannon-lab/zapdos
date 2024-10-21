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

#pragma once

#include "GeneralUserObject.h"

// Forward Declarations
class ObjTest;

template <>
InputParameters validParams<ObjTest>();

class ObjTest : public GeneralUserObject
{
public:
  ObjTest(const InputParameters & parameters);

  Real reaction_coefficient() const;

  virtual void initialize();

  virtual void execute();

  virtual void finalize();

protected:
  Real _reaction_coefficient;
};
