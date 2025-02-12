//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADDGKernel.h"

class DGEFieldAdvection : public ADDGKernel
{
public:
  static InputParameters validParams();

  DGEFieldAdvection(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual(Moose::DGResidualType type) override;

  const ADMaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sgn;
  const ADMaterialProperty<Real> & _mu_neighbor;
  const MaterialProperty<Real> & _sgn_neighbor;

  const ADMaterialProperty<RealVectorValue> & _electric_field;
  const ADMaterialProperty<RealVectorValue> & _electric_field_neighbor;
};
