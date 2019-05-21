//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef AXISYMMETRICCURLZ_H
#define AXISYMMETRICCURLZ_H

#include "Kernel.h"

class AxisymmetricCurlZ;

template <>
InputParameters validParams<AxisymmetricCurlZ>();

class AxisymmetricCurlZ : public Kernel
{
public:
  AxisymmetricCurlZ(const InputParameters & parameters);
  virtual ~AxisymmetricCurlZ();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};

#endif /* AXISYMMETRICCURLZ_H */
