//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef PRODUCTFIRSTORDERRXN_H
#define PRODUCTFIRSTORDERRXN_H

#include "Kernel.h"

// Forward Declaration
class ProductFirstOrderRxn;

template <>
InputParameters validParams<ProductFirstOrderRxn>();

class ProductFirstOrderRxn : public Kernel
{
public:
  ProductFirstOrderRxn(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  MooseVariable & _coupled_var;
  const VariableValue & _v;
  unsigned int _v_id;

  // The reaction coefficient
  const MaterialProperty<Real> & _reaction_coeff;
};
#endif // PRODUCTFIRSTORDERRXN_H
