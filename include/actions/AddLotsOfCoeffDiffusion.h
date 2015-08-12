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

#ifndef ADDLOTSOFCOEFFDIFFUSION_H
#define ADDLOTSOFCOEFFDIFFUSION_H

#include "AddVariableAction.h"
#include "Action.h"

class AddLotsOfCoeffDiffusion;

template<>
InputParameters validParams<AddLotsOfCoeffDiffusion>();


class AddLotsOfCoeffDiffusion : public AddVariableAction
{
public:
  AddLotsOfCoeffDiffusion(InputParameters params);

  virtual void act();
};

#endif // ADDLOTSOFCOEFFDIFFUSION_H
