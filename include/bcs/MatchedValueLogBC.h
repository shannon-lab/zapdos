//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef MATCHEDVALUELOGBC_H
#define MATCHEDVALUELOGBC_H

#include "NodalBC.h"

// Forward Declarations
class MatchedValueLogBC;

template <>
InputParameters validParams<MatchedValueLogBC>();

/**
 * Implements a simple coupled boundary condition where u=v on the boundary.
 */
class MatchedValueLogBC : public NodalBC
{
public:
  MatchedValueLogBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const VariableValue & _v;

  /// The id of the coupled variable
  unsigned int _v_num;
  Real _H;
};

#endif // MATCHEDVALUELOGBC_H
