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

#ifndef NODEANDSIDESETBETWEENSUBDOMAINS_H
#define NODEANDSIDESETBETWEENSUBDOMAINS_H

#include "MeshModifier.h"

class NodeAndSidesetBetweenSubdomains;

template<>
InputParameters validParams<NodeAndSidesetBetweenSubdomains>();

class NodeAndSidesetBetweenSubdomains :
  public MeshModifier
{
public:
  NodeAndSidesetBetweenSubdomains(const InputParameters & parameters);

  virtual ~NodeAndSidesetBetweenSubdomains();

  virtual void modify();

protected:

};

#endif /* NODEANDSIDESETBETWEENSUBDOMAINS_H */
