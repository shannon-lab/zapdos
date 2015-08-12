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

#ifndef ADDLOTSOFSOURCES_H
#define ADDLOTSOFSOURCES_H

#include "AddVariableAction.h"
#include "Action.h"

class AddLotsOfSources;

template<>
InputParameters validParams<AddLotsOfSources>();


class AddLotsOfSources : public AddVariableAction
{
public:
  AddLotsOfSources(InputParameters params);

  virtual void act();
};

#endif // ADDLOTSOFSOURCES_H
