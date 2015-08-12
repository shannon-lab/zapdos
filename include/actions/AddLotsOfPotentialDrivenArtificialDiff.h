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

#ifndef ADDLOTSOFPOTENTIALDRIVENARTIFICIALDIFF_H
#define ADDLOTSOFPOTENTIALDRIVENARTIFICIALDIFF_H

#include "AddVariableAction.h"
#include "Action.h"

class AddLotsOfPotentialDrivenArtificialDiff;

template<>
InputParameters validParams<AddLotsOfPotentialDrivenArtificialDiff>();


class AddLotsOfPotentialDrivenArtificialDiff : public AddVariableAction
{
public:
  AddLotsOfPotentialDrivenArtificialDiff(InputParameters params);

  virtual void act();
};

#endif // ADDLOTSOFPOTENTIALDRIVENARTIFICIALDIFF_H
