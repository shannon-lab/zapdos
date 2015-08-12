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

#ifndef ADDLOTSOFVARIABLES_H
#define ADDLOTSOFVARIABLES_H

#include "AddVariableAction.h"
#include "Action.h"

class AddLotsOfVariables;

template<>
InputParameters validParams<AddLotsOfVariables>();


class AddLotsOfVariables : public AddVariableAction
{
public:
  AddLotsOfVariables(InputParameters params);

  virtual void act();
};

#endif // ADDLOTSOFVARIABLES_H
