//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Water.h"

registerMooseObject("ZapdosApp", Water);

InputParameters
Water::validParams()
{
  InputParameters params = ADMaterial::validParams();

  params.addParam<Real>(
      "user_relative_permittivity", 78.5, "The relative permittivity of the medium.");
  params.addParam<Real>("user_potential_mult", 1, "Scaling for the potential.");
  params.addParam<Real>("user_electron_mult", 1, "Scaling for the electrons.");
  params.addCoupledVar("emliq", "electrons");
  params.addCoupledVar("H", "hydrogen atoms");
  params.addCoupledVar("OHm", "hydroxide ions");
  params.addCoupledVar("H2Op", "positive water ions");
  params.addCoupledVar("OH", "hydroxyl molecules");
  params.addCoupledVar("H2", "hydrogen molecules");
  params.addCoupledVar("Om", "atomic oxygen anions");
  params.addCoupledVar("H3Op", "positive hydronium cations");
  params.addCoupledVar("H2O2", "hydrogen peroxide molecules");
  params.addCoupledVar("HO2m", "HO2 anions");
  params.addCoupledVar("O2", "oxygen molecules");
  params.addCoupledVar("O2m", "molecular oxygen anions");
  params.addCoupledVar("O", "oxygen atoms");
  params.addCoupledVar("HO2", "HO2 molecules");
  params.addCoupledVar("O3", "ozone molecules");
  params.addCoupledVar("O3m", "ozone anions");
  params.addCoupledVar("potential", "The potential");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Material properties of water species");
  return params;
}

Water::Water(const InputParameters & parameters)
  : ADMaterial(parameters),

    // Retrieve input parameters

    _user_relative_permittivity(getParam<Real>("user_relative_permittivity")),
    _user_potential_mult(getParam<Real>("user_potential_mult")),
    _user_electron_mult(getParam<Real>("user_electron_mult")),

    // Declare material properties
    _cw(declareProperty<Real>("cw")),
    _electron_mult(declareProperty<Real>("electron_mult")),
    _potential_mult(declareProperty<Real>("potential_mult")),
    _N_A(declareProperty<Real>("N_A")),
    _eps_r(declareProperty<Real>("eps_r")),
    _eps_0(declareProperty<Real>("eps_0")),
    _e(declareProperty<Real>("e")),
    _k(declareProperty<Real>("k")),
    _T(declareProperty<Real>("T")),
    _kemliq(declareADProperty<Real>("kemliq")),
    _kem(declareADProperty<Real>("kem")),
    _kemliqemliq(declareADProperty<Real>("kemliqemliq")),
    _kemem(declareADProperty<Real>("kemem")),
    _k3(declareProperty<Real>("k3")),
    _k4(declareProperty<Real>("k4")),
    _k5(declareProperty<Real>("k5")),
    _k6(declareProperty<Real>("k6")),
    _k7(declareProperty<Real>("k7")),
    _k8(declareProperty<Real>("k8")),
    _k9(declareProperty<Real>("k9")),
    _k10(declareProperty<Real>("k10")),
    _k11(declareProperty<Real>("k11")),
    _k12(declareProperty<Real>("k12")),
    _k13(declareProperty<Real>("k13")),
    _k14(declareProperty<Real>("k14")),
    _k15(declareProperty<Real>("k15")),
    _k16(declareProperty<Real>("k16")),
    _k17(declareProperty<Real>("k17")),
    _k18(declareProperty<Real>("k18")),
    _k19(declareProperty<Real>("k19")),
    _k20(declareProperty<Real>("k20")),
    _k21(declareProperty<Real>("k21")),
    _k22(declareProperty<Real>("k22")),
    _k23(declareProperty<Real>("k23")),
    _k24(declareProperty<Real>("k24")),
    _k25(declareProperty<Real>("k25")),
    _k26(declareProperty<Real>("k26")),
    _k27(declareProperty<Real>("k27")),
    _k28(declareProperty<Real>("k28")),
    _k29(declareProperty<Real>("k29")),
    _k30(declareProperty<Real>("k30")),
    _k31(declareProperty<Real>("k31")),
    _k32(declareProperty<Real>("k32")),
    _k33(declareProperty<Real>("k33")),
    _k34(declareProperty<Real>("k34")),
    _k35(declareProperty<Real>("k35")),
    _k36(declareProperty<Real>("k36")),
    _k37(declareProperty<Real>("k37")),
    _k38(declareProperty<Real>("k38")),
    _k39(declareProperty<Real>("k39")),
    _diffemliq(declareADProperty<Real>("diffemliq")),
    _diffem(declareADProperty<Real>("diffem")),
    _diffpotentialliq(declareADProperty<Real>("diffpotentialliq")),
    _diffpotential(declareADProperty<Real>("diffpotential")),
    _DH(declareProperty<Real>("DH")),
    _diffOHm(declareADProperty<Real>("diffOHm")),
    _DH2Op(declareProperty<Real>("DH2Op")),
    _DOH(declareProperty<Real>("DOH")),
    _DH2(declareProperty<Real>("DH2")),
    _DOm(declareProperty<Real>("DOm")),
    _diffH3Op(declareADProperty<Real>("diffH3Op")),
    _DH2O2(declareProperty<Real>("DH2O2")),
    _DHO2m(declareProperty<Real>("DHO2m")),
    _DO2(declareProperty<Real>("DO2")),
    _DO2m(declareProperty<Real>("DO2m")),
    _DO(declareProperty<Real>("DO")),
    _DHO2(declareProperty<Real>("DHO2")),
    _DO3(declareProperty<Real>("DO3")),
    _DO3m(declareProperty<Real>("DO3m")),
    _zem(declareProperty<Real>("zem")),
    _zH(declareProperty<Real>("zH")),
    _zOHm(declareProperty<Real>("zOHm")),
    _zH2Op(declareProperty<Real>("zH2Op")),
    _zOH(declareProperty<Real>("zOH")),
    _zH2(declareProperty<Real>("zH2")),
    _zOm(declareProperty<Real>("zOm")),
    _zH3Op(declareProperty<Real>("zH3Op")),
    _zH2O2(declareProperty<Real>("zH2O2")),
    _zHO2m(declareProperty<Real>("zHO2m")),
    _zO2(declareProperty<Real>("zO2")),
    _zO2m(declareProperty<Real>("zO2m")),
    _zO(declareProperty<Real>("zO")),
    _zHO2(declareProperty<Real>("zHO2")),
    _zO3(declareProperty<Real>("zO3")),
    _zO3m(declareProperty<Real>("zO3m")),
    _muemliq(declareADProperty<Real>("muemliq")),
    _muem(declareADProperty<Real>("muem")),
    _muH(declareADProperty<Real>("muH")),
    _muOHm(declareADProperty<Real>("muOHm")),
    _muH2Op(declareADProperty<Real>("muH2Op")),
    _muOH(declareADProperty<Real>("muOH")),
    _muH2(declareADProperty<Real>("muH2")),
    _muOm(declareADProperty<Real>("muOm")),
    _muH3Op(declareADProperty<Real>("muH3Op")),
    _muH2O2(declareADProperty<Real>("muH2O2")),
    _muHO2m(declareADProperty<Real>("muHO2m")),
    _muO2(declareADProperty<Real>("muO2")),
    _muO2m(declareADProperty<Real>("muO2m")),
    _muO(declareADProperty<Real>("muO")),
    _muHO2(declareADProperty<Real>("muHO2")),
    _muO3(declareADProperty<Real>("muO3")),
    _muO3m(declareADProperty<Real>("muO3m")),
    _Dunity(declareProperty<Real>("Dunity")),
    _muunity(declareProperty<Real>("muunity")),
    _munegunity(declareProperty<Real>("munegunity")),
    _eps(declareProperty<Real>("eps")),
    _sgnemliq(declareProperty<Real>("sgnemliq")),
    _sgnem(declareProperty<Real>("sgnem")),
    _sgnOHm(declareProperty<Real>("sgnOHm")),
    _sgnH3Op(declareProperty<Real>("sgnH3Op")),
    _sgnNap(declareProperty<Real>("sgnNap")),
    _sgnClm(declareProperty<Real>("sgnClm")),
    _muNap(declareADProperty<Real>("muNap")),
    _muClm(declareADProperty<Real>("muClm")),
    _diffNap(declareADProperty<Real>("diffNap")),
    _diffClm(declareADProperty<Real>("diffClm")),

    // My materials version of aux variables
    _EField(declareADProperty<Real>("EField")),
    _OHm_lin(declareADProperty<Real>("OHm_lin")),
    _H3Op_lin(declareADProperty<Real>("H3Op_lin")),

    // Coupled Variables

    _emliq(isCoupled("emliq") ? adCoupledValue("emliq") : _ad_zero),
    _H(isCoupled("H") ? adCoupledValue("H") : _ad_zero),
    _OHm(isCoupled("OHm") ? adCoupledValue("OHm") : _ad_zero),
    _H2Op(isCoupled("H2Op") ? adCoupledValue("H2Op") : _ad_zero),
    _OH(isCoupled("OH") ? adCoupledValue("OH") : _ad_zero),
    _H2(isCoupled("H2") ? adCoupledValue("H2") : _ad_zero),
    _Om(isCoupled("Om") ? adCoupledValue("Om") : _ad_zero),
    _H3Op(isCoupled("H3Op") ? adCoupledValue("H3Op") : _ad_zero),
    _H2O2(isCoupled("H2O2") ? adCoupledValue("H2O2") : _ad_zero),
    _HO2m(isCoupled("HO2m") ? adCoupledValue("HO2m") : _ad_zero),
    _O2(isCoupled("O2") ? adCoupledValue("O2") : _ad_zero),
    _O2m(isCoupled("O2m") ? adCoupledValue("O2m") : _ad_zero),
    _O(isCoupled("O") ? adCoupledValue("O") : _ad_zero),
    _HO2(isCoupled("HO2") ? adCoupledValue("HO2") : _ad_zero),
    _O3(isCoupled("O3") ? adCoupledValue("O3") : _ad_zero),
    _O3m(isCoupled("O3m") ? adCoupledValue("O3m") : _ad_zero),

    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))

{
}

void
Water::computeQpProperties()
{
  _cw[_qp] = 56;
  _electron_mult[_qp] = _user_electron_mult;
  _potential_mult[_qp] = _user_potential_mult;
  _N_A[_qp] = 6.02e23;
  _eps_r[_qp] = 80.;
  // _eps_r[_qp] = 1.;
  _eps_0[_qp] = 8.85e-12;
  _eps[_qp] = _eps_r[_qp] * _eps_0[_qp];
  _e[_qp] = 1.6e-19;               // coulombic charge
  _k[_qp] = 1.38e-23;              // Boltzmanns constant
  _T[_qp] = 300;                   // Simulation temperature
  _kemliq[_qp] = 1.9e1 * _cw[_qp]; // e + H2O-->H + OH-
  _kem[_qp] = _kemliq[_qp];
  // _kemliqemliq[_qp]  = 6e11 * _cw[_qp] * _cw[_qp] / (_N_A[_qp] * 1000.);     // e + H2Op-->H + OH
  _kemliqemliq[_qp] =
      1e8 * _cw[_qp] * _cw[_qp] / 1000.; // 2e + 2H2O-->H2 + 2OH-. Now has units of m^3 / (mol * s)
  _kemem[_qp] = _kemliqemliq[_qp];
  _k4[_qp] = 2.5e10;        // e + H + H2O-->H2 + OH-
  _k5[_qp] = 3e10;          // e + OH-->OH-
  _k6[_qp] = 2.2e10;        // e + O- + H2O --> 2OH-
  _k7[_qp] = 2.3e10;        // e + H3O+ --> H2 + H2O
  _k8[_qp] = 1.1e10;        // e + H2O2 --> OH + OH-
  _k9[_qp] = 3.5e9;         // e + HO2- + H2O --> OH + 2OH-
  _k10[_qp] = 1.9e10;       // e + O2 --> O2-
  _k11[_qp] = 1.9e10;       // e + O --> O-
  _k12[_qp] = 1.0e1;        // H + H2O --> H2 + OH
  _k13[_qp] = 7.5e9;        // 2H --> H2
  _k14[_qp] = 7.0e9;        // H + OH --> H2O
  _k15[_qp] = 2.2e7;        // H + OH- --> H2O + e
  _k16[_qp] = 9.0e7;        // H + H2O2 --> OH + H2O
  _k17[_qp] = 6.0e6;        // H2 + H2O2 --> H + OH + H2O
  _k18[_qp] = 2.1e10;       // H + O2 --> HO2
  _k19[_qp] = 1.0e10;       // H + HO2 --> H2O2
  _k20[_qp] = 1.3e4;        // O + H2O --> 2OH
  _k21[_qp] = 3.0e9;        // O + O2 --> O3
  _k22[_qp] = 5.5e9;        // 2OH --> H2O2
  _k23[_qp] = 2.0e10;       // OH + O- --> HO2-
  _k24[_qp] = 4.2e7;        // OH + H2 --> H + H2O
  _k25[_qp] = 1.3e10;       // OH + OH- --> O- + H2O
  _k26[_qp] = 6.0e9;        // OH + HO2 --> H2O + O2
  _k27[_qp] = 8.0e9;        // OH + O2- --> OH- + O2
  _k28[_qp] = 1.8e6;        // ] O- + H2O --> OH- + OH
  _k29[_qp] = 8.0e7;        // O- + H2 --> OH- + H
  _k30[_qp] = 5.0e8;        // O- + H2O2 --> O2- + H2O
  _k31[_qp] = 4.0e8;        // O- + HO2- --> O2- + OH-
  _k32[_qp] = 3.6e9;        // O- + O2- --> O3-
  _k33[_qp] = 6.0e8;        // O- + O2- + H2O --> 2OH- + O2
  _k34[_qp] = 2.7e7;        // OH + H2O2 --> H2O + HO2
  _k35[_qp] = 7.5e9;        // OH + HO2- --> OH- + HO2
  _k36[_qp] = 6.0e3;        // H2O+ + H2O --> H3O+ + OH
  _k37[_qp] = 6.0e10;       // H3O+ + OH- --> H + OH + H2O
  _k38[_qp] = 2.0e3;        // HO2 + H2O --> H3O+ + O2-
  _k39[_qp] = 6.0e1;        // H3O+ O2- --> HO2 + H2O
  _diffemliq[_qp] = 4.5e-9; // diffusivity of hydrated electron. Anbar (1965) from Ranga paper
  _diffem[_qp] = _diffemliq[_qp];
  // _diffem[_qp] = 0.297951680159;
  _diffpotentialliq[_qp] = _eps[_qp];
  _diffpotential[_qp] = _diffpotentialliq[_qp];
  // _diffemliq[_qp] = 0.297951680159/4;
  _DH[_qp] = 5e-9;         // H radical
  _diffOHm[_qp] = 5.27e-9; // OH- ion
  // _diffOHm[_qp] = 2.98e-3; // Temporary high diffusivity taken from gas phase argon
  _diffClm[_qp] = _diffOHm[_qp];
  _DH2Op[_qp] = 5e-9;      // H2O+ ion
  _DOH[_qp] = 5e-9;        // OH radical
  _DH2[_qp] = 4.5e-9;      // H2 molecule
  _DOm[_qp] = 5e-9;        // O- ion
  _diffH3Op[_qp] = 9.3e-9; // H3O+ ion
  // _diffH3Op[_qp] = 2.98e-3;
  _diffNap[_qp] = _diffH3Op[_qp];
  _DH2O2[_qp] = 5e-9; // H2O2 molecule
  _DHO2m[_qp] = 5e-9; // HO2- ion
  _DO2[_qp] = 2e-9;   // O2 molecule
  _DO2m[_qp] = 5e-9;  // O2- ion
  _DO[_qp] = 5e-9;    // O radical
  _DHO2[_qp] = 5e-9;  // HO2 radical
  _DO3[_qp] = 5e-9;   // O3 molecule
  _DO3m[_qp] = 5e-9;  // O3- ion
  _zem[_qp] = -1;     // charge of hydrated electron
  _zH[_qp] = 0;       // H radical
  _zOHm[_qp] = -1;    // OH- ion
  _zH2Op[_qp] = 1;    // H2O+ ion
  _zOH[_qp] = 0;      // OH radical
  _zH2[_qp] = 0;      // H2 molecule
  _zOm[_qp] = -1;     // O- ion
  _zH3Op[_qp] = 1;    // H3O+ ion
  _zH2O2[_qp] = 0;    // H2O2 molecule
  _zHO2m[_qp] = -1;   // HO2- ion
  _zO2[_qp] = 0;      // O2 molecule
  _zO2m[_qp] = -1;    // O2- ion
  _zO[_qp] = 0;       // O radical
  _zHO2[_qp] = 0;     // HO2 radical
  _zO3[_qp] = 0;      // O3 molecule
  _zO3m[_qp] = -1;    // O3- ion
  _sgnemliq[_qp] = -1;
  _sgnem[_qp] = _sgnemliq[_qp];
  _sgnOHm[_qp] = -1;
  _sgnH3Op[_qp] = 1;
  _sgnClm[_qp] = -1;
  _sgnNap[_qp] = 1;
  _muemliq[_qp] =
      _e[_qp] * _diffemliq[_qp] / _k[_qp] / _T[_qp] * 1000.; // mobility of hydrated electron
  _muem[_qp] = _muemliq[_qp];
  // _muem[_qp] = 0.0352103411399 * 1000.; // units of m^2/(kV*s)
  // _muemliq[_qp] = 0.0352103411399/4;
  _muH[_qp] = _zH[_qp] * _e[_qp] * _DH[_qp] / _k[_qp] / _T[_qp];     // H radical
  _muOHm[_qp] = _e[_qp] * _diffOHm[_qp] / _k[_qp] / _T[_qp] * 1000.; // OH- ion
  _muClm[_qp] = _muOHm[_qp];
  // _muOHm[_qp] = 3.52e-4;
  _muH2Op[_qp] = _zH2Op[_qp] * _e[_qp] * _DH2Op[_qp] / _k[_qp] / _T[_qp]; // H2O+ ion
  _muOH[_qp] = _zOH[_qp] * _e[_qp] * _DOH[_qp] / _k[_qp] / _T[_qp];       // OH radical
  _muH2[_qp] = _zH2[_qp] * _e[_qp] * _DH2[_qp] / _k[_qp] / _T[_qp];       // H2 molecule
  _muOm[_qp] = _zOm[_qp] * _e[_qp] * _DOm[_qp] / _k[_qp] / _T[_qp];       // O- ion
  _muH3Op[_qp] = _e[_qp] * _diffH3Op[_qp] / _k[_qp] / _T[_qp] * 1000.;    // H3O+ ion
  _muNap[_qp] = _muH3Op[_qp];
  // _muH3Op[_qp] = 3.52e-4;
  _muH2O2[_qp] = _zH2O2[_qp] * _e[_qp] * _DH2O2[_qp] / _k[_qp] / _T[_qp]; // H2O2 molecule
  _muHO2m[_qp] = _zHO2m[_qp] * _e[_qp] * _DHO2m[_qp] / _k[_qp] / _T[_qp]; // HO2- ion
  _muO2[_qp] = _zO2[_qp] * _e[_qp] * _DO2[_qp] / _k[_qp] / _T[_qp];       // O2 molecule
  _muO2m[_qp] = _zO2m[_qp] * _e[_qp] * _DO2m[_qp] / _k[_qp] / _T[_qp];    // O2- ion
  _muO[_qp] = _zO[_qp] * _e[_qp] * _DO[_qp] / _k[_qp] / _T[_qp];          // O radical
  _muHO2[_qp] = _zHO2[_qp] * _e[_qp] * _DHO2[_qp] / _k[_qp] / _T[_qp];    // HO2 radical
  _muO3[_qp] = _zO3[_qp] * _e[_qp] * _DO3[_qp] / _k[_qp] / _T[_qp];       // O3 molecule
  _muO3m[_qp] = _zO3m[_qp] * _e[_qp] * _DO3m[_qp] / _k[_qp] / _T[_qp];    // O3- ion
  _Dunity[_qp] = 1.0;
  _muunity[_qp] = 1.0;
  _munegunity[_qp] = -1.0;

  // Material version of aux variables

  _EField[_qp] = _electric_field[_qp](0); // TODO: does this need to be 0 component now? consider
                                          // fixing this up....1D will request the 0 by default
  _OHm_lin[_qp] = std::exp(_OHm[_qp]);
  _H3Op_lin[_qp] = std::exp(_H3Op[_qp]);
}
