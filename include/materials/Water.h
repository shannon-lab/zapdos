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

/*
 *  Material properties of water species
 */
class Water : public ADMaterial
{
public:
  static InputParameters validParams();

  Water(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// User defined relative permittivity of the medium
  const Real & _user_relative_permittivity;
  /// User defined scaling for the potential
  const Real & _user_potential_mult;
  /// User defined scaling for the electrons
  const Real & _user_electron_mult;

  /// Scaling factor for e+H2O and 2e + 2H2O reactions
  MaterialProperty<Real> & _cw;
  /// Scaling for the electrons
  MaterialProperty<Real> & _electron_mult;
  /// Scaling for the potential
  MaterialProperty<Real> & _potential_mult;
  /// Relative permittivity of the medium
  MaterialProperty<Real> & _eps_r;
  /// Coupled water temperature variable (defaulted to 300k)
  const VariableValue & _T_water;
  /// Water temperature
  MaterialProperty<Real> & _T;
  /*
   * Reaction coefficient for:
   * e + H2O-->H + OH-
   */
  ADMaterialProperty<Real> & _kemliq;
  /// Defined the same as _kemliq
  ADMaterialProperty<Real> & _kem;
  /*
   * Reaction coefficient for:
   * 2e + 2H2O-->H2 + 2OH-
   */
  ADMaterialProperty<Real> & _kemliqemliq;
  /// Defined the same as _kemliqemliq
  ADMaterialProperty<Real> & _kemem;
  /*
   * Reaction coefficient for:
   * e + H + H2O-->H2 + OH-
   */
  MaterialProperty<Real> & _k4;
  /*
   * Reaction coefficient for:
   * e + OH-->OH-
   */
  MaterialProperty<Real> & _k5;
  /*
   * Reaction coefficient for:
   * e + O- + H2O --> 2OH-
   */
  MaterialProperty<Real> & _k6;
  /*
   * Reaction coefficient for:
   * e + H3O+ --> H2 + H2O
   */
  MaterialProperty<Real> & _k7;
  /*
   * Reaction coefficient for:
   * e + H2O2 --> OH + OH-
   */
  MaterialProperty<Real> & _k8;
  /*
   * Reaction coefficient for:
   * e + HO2- + H2O --> OH + 2OH-
   */
  MaterialProperty<Real> & _k9;
  /*
   * Reaction coefficient for:
   * e + O2 --> O2-
   */
  MaterialProperty<Real> & _k10;
  /*
   * Reaction coefficient for:
   * e + O --> O-
   */
  MaterialProperty<Real> & _k11;
  /*
   * Reaction coefficient for:
   * H + H2O --> H2 + OH
   */
  MaterialProperty<Real> & _k12;
  /*
   * Reaction coefficient for:
   * 2H --> H2
   */
  MaterialProperty<Real> & _k13;
  /*
   * Reaction coefficient for:
   * H + OH --> H2O
   */
  MaterialProperty<Real> & _k14;
  /*
   * Reaction coefficient for:
   * H + OH- --> H2O + e
   */
  MaterialProperty<Real> & _k15;
  /*
   * Reaction coefficient for:
   * H + H2O2 --> OH + H2O
   */
  MaterialProperty<Real> & _k16;
  /*
   * Reaction coefficient for:
   * H2 + H2O2 --> H + OH + H2O
   */
  MaterialProperty<Real> & _k17;
  /*
   * Reaction coefficient for:
   * H + O2 --> HO2
   */
  MaterialProperty<Real> & _k18;
  /*
   * Reaction coefficient for:
   * H + HO2 --> H2O2
   */
  MaterialProperty<Real> & _k19;
  /*
   * Reaction coefficient for:
   * O + H2O --> 2OH
   */
  MaterialProperty<Real> & _k20;
  /*
   * Reaction coefficient for:
   * O + O2 --> O3
   */
  MaterialProperty<Real> & _k21;
  /*
   * Reaction coefficient for:
   * 2OH --> H2O2
   */
  MaterialProperty<Real> & _k22;
  /*
   * Reaction coefficient for:
   * OH + O- --> HO2-
   */
  MaterialProperty<Real> & _k23;
  /*
   * Reaction coefficient for:
   * OH + H2 --> H + H2O
   */
  MaterialProperty<Real> & _k24;
  /*
   * Reaction coefficient for:
   * OH + OH- --> O- + H2O
   */
  MaterialProperty<Real> & _k25;
  /*
   * Reaction coefficient for:
   * OH + HO2 --> H2O + O2
   */
  MaterialProperty<Real> & _k26;
  /*
   * Reaction coefficient for:
   * OH + O2- --> OH- + O2
   */
  MaterialProperty<Real> & _k27;
  /*
   * Reaction coefficient for:
   * O- + H2O --> OH- + OH
   */
  MaterialProperty<Real> & _k28;
  /*
   * Reaction coefficient for:
   * O- + H2 --> OH- + H
   */
  MaterialProperty<Real> & _k29;
  /*
   * Reaction coefficient for:
   * O- + H2O2 --> O2- + H2O
   */
  MaterialProperty<Real> & _k30;
  /*
   * Reaction coefficient for:
   * O- + HO2- --> O2- + OH-
   */
  MaterialProperty<Real> & _k31;
  /*
   * Reaction coefficient for:
   * O- + O2- --> O3-
   */
  MaterialProperty<Real> & _k32;
  /*
   * Reaction coefficient for:
   * O- + O2- + H2O --> 2OH- + O2
   */
  MaterialProperty<Real> & _k33;
  /*
   * Reaction coefficient for:
   * OH + H2O2 --> H2O + HO2
   */
  MaterialProperty<Real> & _k34;
  /*
   * Reaction coefficient for:
   * OH + HO2- --> OH- + HO2
   */
  MaterialProperty<Real> & _k35;
  /*
   * Reaction coefficient for:
   * H2O+ + H2O --> H3O+ + OH
   */
  MaterialProperty<Real> & _k36;
  /*
   * Reaction coefficient for:
   * H3O+ + OH- --> H + OH + H2O
   */
  MaterialProperty<Real> & _k37;
  /*
   * Reaction coefficient for:
   * HO2 + H2O --> H3O+ + O2-
   */
  MaterialProperty<Real> & _k38;
  /*
   * Reaction coefficient for:
   * H3O+ O2- --> HO2 + H2O
   */
  MaterialProperty<Real> & _k39;
  /// Diffusion coefficient for hydrated electron
  ADMaterialProperty<Real> & _diffemliq;
  /// Diffusion coefficient for electron (defined the same as _diffemliq)
  ADMaterialProperty<Real> & _diffem;
  /// Diffusion coefficient for potential in water (defined as the permittivity of the medium)
  ADMaterialProperty<Real> & _diffpotentialliq;
  /// Diffusion coefficient for potential (defined the same as _diffpotentialliq)
  ADMaterialProperty<Real> & _diffpotential;
  /// Diffusion coefficient for H radical
  MaterialProperty<Real> & _DH;
  /// Diffusion coefficient for OH- ion
  ADMaterialProperty<Real> & _diffOHm;
  /// Diffusion coefficient for H2O+ ion
  MaterialProperty<Real> & _DH2Op;
  /// Diffusion coefficient for OH radical
  MaterialProperty<Real> & _DOH;
  /// Diffusion coefficient for H2 molecule
  MaterialProperty<Real> & _DH2;
  /// Diffusion coefficient for O- ion
  MaterialProperty<Real> & _DOm;
  /// Diffusion coefficient for H3O+ ion
  ADMaterialProperty<Real> & _diffH3Op;
  /// Diffusion coefficient for H2O2 molecule
  MaterialProperty<Real> & _DH2O2;
  /// Diffusion coefficient for HO2- ion
  MaterialProperty<Real> & _DHO2m;
  /// Diffusion coefficient for O2 molecule
  MaterialProperty<Real> & _DO2;
  /// Diffusion coefficient for O2- ion
  MaterialProperty<Real> & _DO2m;
  /// Diffusion coefficient for O radical
  MaterialProperty<Real> & _DO;
  /// Diffusion coefficient for HO2 radical
  MaterialProperty<Real> & _DHO2;
  /// Diffusion coefficient for O3 molecule
  MaterialProperty<Real> & _DO3;
  /// Diffusion coefficient for O3- ion
  MaterialProperty<Real> & _DO3m;
  /// Charge of hydrated electron
  MaterialProperty<Real> & _zem;
  /// Charge of H radical
  MaterialProperty<Real> & _zH;
  /// Charge of OH- ion
  MaterialProperty<Real> & _zOHm;
  /// Charge of H2O+ ion
  MaterialProperty<Real> & _zH2Op;
  /// Charge of OH radical
  MaterialProperty<Real> & _zOH;
  /// Charge of H2 molecule
  MaterialProperty<Real> & _zH2;
  /// Charge of O- ion
  MaterialProperty<Real> & _zOm;
  /// Charge of H3O+ ion
  MaterialProperty<Real> & _zH3Op;
  /// Charge of H2O2 molecule
  MaterialProperty<Real> & _zH2O2;
  /// Charge of HO2- ion
  MaterialProperty<Real> & _zHO2m;
  /// Charge of O2 molecule
  MaterialProperty<Real> & _zO2;
  /// Charge of O2- ion
  MaterialProperty<Real> & _zO2m;
  /// Charge of O radical
  MaterialProperty<Real> & _zO;
  /// Charge of HO2 radical
  MaterialProperty<Real> & _zHO2;
  /// Charge of O3 molecule
  MaterialProperty<Real> & _zO3;
  /// Charge of O3- ion
  MaterialProperty<Real> & _zO3m;
  /// Mobility coefficient for hydrated electron
  ADMaterialProperty<Real> & _muemliq;
  /// Mobility coefficient for electron (defined the same as _diffemliq)
  ADMaterialProperty<Real> & _muem;
  /// Mobility coefficient for H radical
  ADMaterialProperty<Real> & _muH;
  /// Mobility coefficient for OH- ion
  ADMaterialProperty<Real> & _muOHm;
  /// Mobility coefficient for H2O+ ion
  ADMaterialProperty<Real> & _muH2Op;
  /// Mobility coefficient for OH radical
  ADMaterialProperty<Real> & _muOH;
  /// Mobility coefficient for H2 molecule
  ADMaterialProperty<Real> & _muH2;
  /// Mobility coefficient for O- ion
  ADMaterialProperty<Real> & _muOm;
  /// Mobility coefficient for H3O+ ion
  ADMaterialProperty<Real> & _muH3Op;
  /// Mobility coefficient for H2O2 molecule
  ADMaterialProperty<Real> & _muH2O2;
  /// Mobility coefficient for HO2- ion
  ADMaterialProperty<Real> & _muHO2m;
  /// Mobility coefficient for O2 molecule
  ADMaterialProperty<Real> & _muO2;
  /// Mobility coefficient for O2- ion
  ADMaterialProperty<Real> & _muO2m;
  /// Mobility coefficient for O radical
  ADMaterialProperty<Real> & _muO;
  /// Mobility coefficient for HO2 radical
  ADMaterialProperty<Real> & _muHO2;
  /// Mobility coefficient for O3 molecule
  ADMaterialProperty<Real> & _muO3;
  /// Mobility coefficient for O3- ion
  ADMaterialProperty<Real> & _muO3m;
  /// Diffusion coefficient of unity
  MaterialProperty<Real> & _Dunity;
  /// Mobility coefficient of unity
  MaterialProperty<Real> & _muunity;
  /// Negative charge sign of unity
  MaterialProperty<Real> & _munegunity;
  /// Permittivity of the medium
  MaterialProperty<Real> & _eps;
  /// Charge of hydrated electron
  MaterialProperty<Real> & _sgnemliq;
  /// Charge of electrons
  MaterialProperty<Real> & _sgnem;
  /// Charge of OH- ion
  MaterialProperty<Real> & _sgnOHm;
  /// Charge of H3O+ ion
  MaterialProperty<Real> & _sgnH3Op;
  /// Defined the same as _sgnH3Op
  MaterialProperty<Real> & _sgnNap;
  /// Defined the same as _sgnOHm
  MaterialProperty<Real> & _sgnClm;
  /// Defined the same as _muH3Op
  ADMaterialProperty<Real> & _muNap;
  /// Defined the same as _muOHm
  ADMaterialProperty<Real> & _muClm;
  /// Defined the same as _diffH3Op
  ADMaterialProperty<Real> & _diffNap;
  /// Defined the same as _diffOHm
  ADMaterialProperty<Real> & _diffClm;

  /// Electrostatic electric field
  ADMaterialProperty<Real> & _EField;
  /// Converting logarithmic form of OH- ion into mol/m^3
  ADMaterialProperty<Real> & _OHm_lin;
  /// Converting logarithmic form of H3O+ ion ion into mol/m^3
  ADMaterialProperty<Real> & _H3Op_lin;

private:
  /// Coupled hydrated electron
  const ADVariableValue & _emliq;
  /// Coupled H radical
  const ADVariableValue & _H;
  /// Coupled OH- ion
  const ADVariableValue & _OHm;
  /// Coupled H2O+ ion
  const ADVariableValue & _H2Op;
  /// Coupled OH radical
  const ADVariableValue & _OH;
  /// Coupled H2 molecule
  const ADVariableValue & _H2;
  /// Coupled O- ion
  const ADVariableValue & _Om;
  /// Coupled H3O+ ion
  const ADVariableValue & _H3Op;
  /// Coupled H2O2 molecule
  const ADVariableValue & _H2O2;
  /// Coupled HO2- ion
  const ADVariableValue & _HO2m;
  /// Coupled O2 molecule
  const ADVariableValue & _O2;
  /// Coupled O2- ion
  const ADVariableValue & _O2m;
  /// Coupled O radical
  const ADVariableValue & _O;
  /// Coupled HO2 radical
  const ADVariableValue & _HO2;
  /// Coupled O3 molecule
  const ADVariableValue & _O3;
  /// Coupled O3- ion
  const ADVariableValue & _O3m;

  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;
};
