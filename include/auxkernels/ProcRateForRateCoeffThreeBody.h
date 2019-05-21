//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef PROCRATEFORRATECOEFFTHREEBODY_H
#define PROCRATEFORRATECOEFFTHREEBODY_H

#include "AuxKernel.h"

class ProcRateForRateCoeffThreeBody;

template <>
InputParameters validParams<ProcRateForRateCoeffThreeBody>();

class ProcRateForRateCoeffThreeBody : public AuxKernel
{
public:
  ProcRateForRateCoeffThreeBody(const InputParameters & parameters);

  virtual ~ProcRateForRateCoeffThreeBody() {}
  virtual Real computeValue();

protected:


  const VariableValue & _v;
  const VariableValue & _w;
  const VariableValue & _vv;
  const MaterialProperty<Real> & _reaction_coeff;
};

#endif // ProcRateForRateCoeffThreeBody_H
