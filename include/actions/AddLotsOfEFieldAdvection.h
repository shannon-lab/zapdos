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

#ifndef ADDLOTSOFEFIELDADVECTION_H
#define ADDLOTSOFEFIELDADVECTION_H

#include "AddVariableAction.h"
#include "Action.h"

class AddLotsOfEFieldAdvection;

template<>
InputParameters validParams<AddLotsOfEFieldAdvection>();


class AddLotsOfEFieldAdvection : public AddVariableAction
{
public:
  AddLotsOfEFieldAdvection(InputParameters params);

  virtual void act();
};

#endif // ADDLOTSOFEFIELDADVECTION_H
