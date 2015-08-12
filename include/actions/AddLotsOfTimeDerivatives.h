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

#ifndef ADDLOTSOFTIMEDERIVATIVES_H
#define ADDLOTSOFTIMEDERIVATIVES_H

#include "AddVariableAction.h"
#include "Action.h"

class AddLotsOfTimeDerivatives;

template<>
InputParameters validParams<AddLotsOfTimeDerivatives>();


class AddLotsOfTimeDerivatives : public AddVariableAction
{
public:
  AddLotsOfTimeDerivatives(InputParameters params);

  virtual void act();
};

#endif // ADDLOTSOFTIMEDERIVATIVES_H
