//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef NODEANDSIDESETBETWEENSUBDOMAINS_H
#define NODEANDSIDESETBETWEENSUBDOMAINS_H

#include "MeshModifier.h"

class NodeAndSidesetBetweenSubdomains;

template <>
InputParameters validParams<NodeAndSidesetBetweenSubdomains>();

class NodeAndSidesetBetweenSubdomains : public MeshModifier
{
public:
  NodeAndSidesetBetweenSubdomains(const InputParameters & parameters);

  virtual ~NodeAndSidesetBetweenSubdomains();

  virtual void modify();

protected:
};

#endif /* NODEANDSIDESETBETWEENSUBDOMAINS_H */
