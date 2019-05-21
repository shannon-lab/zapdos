//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ELECTRONTIMEDERIVATIVE_H
#define ELECTRONTIMEDERIVATIVE_H

#include "TimeKernel.h"

// Forward Declaration
class ElectronTimeDerivative;

template <>
InputParameters validParams<ElectronTimeDerivative>();

class ElectronTimeDerivative : public TimeKernel
{
public:
  ElectronTimeDerivative(const InputParameters & parameters);

  /* virtual void computeJacobian(); */

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  /* virtual Real computeQpOffDiagJacobian(unsigned int jvar); */

  bool _lumping;
};

#endif // ELECTRONTIMEDERIVATIVE_H
