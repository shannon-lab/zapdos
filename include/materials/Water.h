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

#include "ADMaterial.h"

class Water : public ADMaterial
{
public:
  static InputParameters validParams();

  Water(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  // Input Parameters

  const Real & _user_relative_permittivity;
  const Real & _user_potential_mult;
  const Real & _user_electron_mult;

  // Material Properties

  MaterialProperty<Real> & _cw;
  MaterialProperty<Real> & _electron_mult;
  MaterialProperty<Real> & _potential_mult;
  MaterialProperty<Real> & _N_A;
  MaterialProperty<Real> & _eps_r;
  MaterialProperty<Real> & _eps_0;
  MaterialProperty<Real> & _e;
  MaterialProperty<Real> & _k;
  MaterialProperty<Real> & _T;
  ADMaterialProperty<Real> & _kemliq;
  ADMaterialProperty<Real> & _kem;
  ADMaterialProperty<Real> & _kemliqemliq;
  ADMaterialProperty<Real> & _kemem;
  MaterialProperty<Real> & _k3;
  MaterialProperty<Real> & _k4;
  MaterialProperty<Real> & _k5;
  MaterialProperty<Real> & _k6;
  MaterialProperty<Real> & _k7;
  MaterialProperty<Real> & _k8;
  MaterialProperty<Real> & _k9;
  MaterialProperty<Real> & _k10;
  MaterialProperty<Real> & _k11;
  MaterialProperty<Real> & _k12;
  MaterialProperty<Real> & _k13;
  MaterialProperty<Real> & _k14;
  MaterialProperty<Real> & _k15;
  MaterialProperty<Real> & _k16;
  MaterialProperty<Real> & _k17;
  MaterialProperty<Real> & _k18;
  MaterialProperty<Real> & _k19;
  MaterialProperty<Real> & _k20;
  MaterialProperty<Real> & _k21;
  MaterialProperty<Real> & _k22;
  MaterialProperty<Real> & _k23;
  MaterialProperty<Real> & _k24;
  MaterialProperty<Real> & _k25;
  MaterialProperty<Real> & _k26;
  MaterialProperty<Real> & _k27;
  MaterialProperty<Real> & _k28;
  MaterialProperty<Real> & _k29;
  MaterialProperty<Real> & _k30;
  MaterialProperty<Real> & _k31;
  MaterialProperty<Real> & _k32;
  MaterialProperty<Real> & _k33;
  MaterialProperty<Real> & _k34;
  MaterialProperty<Real> & _k35;
  MaterialProperty<Real> & _k36;
  MaterialProperty<Real> & _k37;
  MaterialProperty<Real> & _k38;
  MaterialProperty<Real> & _k39;
  ADMaterialProperty<Real> & _diffemliq;
  ADMaterialProperty<Real> & _diffem;
  ADMaterialProperty<Real> & _diffpotentialliq;
  ADMaterialProperty<Real> & _diffpotential;
  MaterialProperty<Real> & _DH;
  ADMaterialProperty<Real> & _diffOHm;
  MaterialProperty<Real> & _DH2Op;
  MaterialProperty<Real> & _DOH;
  MaterialProperty<Real> & _DH2;
  MaterialProperty<Real> & _DOm;
  ADMaterialProperty<Real> & _diffH3Op;
  MaterialProperty<Real> & _DH2O2;
  MaterialProperty<Real> & _DHO2m;
  MaterialProperty<Real> & _DO2;
  MaterialProperty<Real> & _DO2m;
  MaterialProperty<Real> & _DO;
  MaterialProperty<Real> & _DHO2;
  MaterialProperty<Real> & _DO3;
  MaterialProperty<Real> & _DO3m;
  MaterialProperty<Real> & _zem;
  MaterialProperty<Real> & _zH;
  MaterialProperty<Real> & _zOHm;
  MaterialProperty<Real> & _zH2Op;
  MaterialProperty<Real> & _zOH;
  MaterialProperty<Real> & _zH2;
  MaterialProperty<Real> & _zOm;
  MaterialProperty<Real> & _zH3Op;
  MaterialProperty<Real> & _zH2O2;
  MaterialProperty<Real> & _zHO2m;
  MaterialProperty<Real> & _zO2;
  MaterialProperty<Real> & _zO2m;
  MaterialProperty<Real> & _zO;
  MaterialProperty<Real> & _zHO2;
  MaterialProperty<Real> & _zO3;
  MaterialProperty<Real> & _zO3m;
  ADMaterialProperty<Real> & _muemliq;
  ADMaterialProperty<Real> & _muem;
  ADMaterialProperty<Real> & _muH;
  ADMaterialProperty<Real> & _muOHm;
  ADMaterialProperty<Real> & _muH2Op;
  ADMaterialProperty<Real> & _muOH;
  ADMaterialProperty<Real> & _muH2;
  ADMaterialProperty<Real> & _muOm;
  ADMaterialProperty<Real> & _muH3Op;
  ADMaterialProperty<Real> & _muH2O2;
  ADMaterialProperty<Real> & _muHO2m;
  ADMaterialProperty<Real> & _muO2;
  ADMaterialProperty<Real> & _muO2m;
  ADMaterialProperty<Real> & _muO;
  ADMaterialProperty<Real> & _muHO2;
  ADMaterialProperty<Real> & _muO3;
  ADMaterialProperty<Real> & _muO3m;
  MaterialProperty<Real> & _Dunity;
  MaterialProperty<Real> & _muunity;
  MaterialProperty<Real> & _munegunity;
  MaterialProperty<Real> & _eps;
  MaterialProperty<Real> & _sgnemliq;
  MaterialProperty<Real> & _sgnem;
  MaterialProperty<Real> & _sgnOHm;
  MaterialProperty<Real> & _sgnH3Op;
  MaterialProperty<Real> & _sgnNap;
  MaterialProperty<Real> & _sgnClm;
  ADMaterialProperty<Real> & _muNap;
  ADMaterialProperty<Real> & _muClm;
  ADMaterialProperty<Real> & _diffNap;
  ADMaterialProperty<Real> & _diffClm;

  ADMaterialProperty<Real> & _EField;
  ADMaterialProperty<Real> & _OHm_lin;
  ADMaterialProperty<Real> & _H3Op_lin;

private:
  const ADVariableValue & _emliq;
  const ADVariableValue & _H;
  const ADVariableValue & _OHm;
  const ADVariableValue & _H2Op;
  const ADVariableValue & _OH;
  const ADVariableValue & _H2;
  const ADVariableValue & _Om;
  const ADVariableValue & _H3Op;
  const ADVariableValue & _H2O2;
  const ADVariableValue & _HO2m;
  const ADVariableValue & _O2;
  const ADVariableValue & _O2m;
  const ADVariableValue & _O;
  const ADVariableValue & _HO2;
  const ADVariableValue & _O3;
  const ADVariableValue & _O3m;

  const ADMaterialProperty<RealVectorValue> & _electric_field;
};
