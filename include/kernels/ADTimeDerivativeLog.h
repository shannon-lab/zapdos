//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ADTimeDerivative.h"

class ADTimeDerivativeLog;

declareADValidParams(ADTimeDerivativeLog);

class ADTimeDerivativeLog : public ADTimeDerivative
{
public:
  static InputParameters validParams();

  ADTimeDerivativeLog(const InputParameters & parameters);

protected:
  // virtual ADRealVectorValue precomputeQpResidual() override;
  virtual ADReal precomputeQpResidual() override;

private:
};
