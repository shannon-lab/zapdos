#include "Water.h"

template<>
InputParameters validParams<Water>()
{
  InputParameters params = validParams<Material>();

  // params.addParam<std::string>("diffusivity_string","The string that determines which diffusivity to use");

  return params;
}

Water::Water(const std::string & name, InputParameters parameters) :
  Material(name,parameters),

  // Declare material properties

  _e(declareProperty<Real>("e")),
  _k(declareProperty<Real>("k")),           
  _T(declareProperty<Real>("T")),            
  _k1(declareProperty<Real>("k1")),
  _k2(declareProperty<Real>("k2")),
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
  _Dem(declareProperty<Real>("Dem")),
  _DH(declareProperty<Real>("DH")),
  _DOHm(declareProperty<Real>("DOHm")),
  _DH2Op(declareProperty<Real>("DH2Op")),
  _DOH(declareProperty<Real>("DOH")),
  _DH2(declareProperty<Real>("DH2")),
  _DOm(declareProperty<Real>("DOm")),
  _DH3Op(declareProperty<Real>("DH3Op")),
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
  _muem(declareProperty<Real>("muem")),
  _muH(declareProperty<Real>("muH")),
  _muOHm(declareProperty<Real>("muOHm")),
  _muH2Op(declareProperty<Real>("muH2Op")),
  _muOH(declareProperty<Real>("muOH")),
  _muH2(declareProperty<Real>("muH2")),
  _muOm(declareProperty<Real>("muOm")),
  _muH3Op(declareProperty<Real>("muH3Op")),
  _muH2O2(declareProperty<Real>("muH2O2")),
  _muHO2m(declareProperty<Real>("muHO2m")),
  _muO2(declareProperty<Real>("muO2")),
  _muO2m(declareProperty<Real>("muO2m")),
  _muO(declareProperty<Real>("muO")),
  _muHO2(declareProperty<Real>("muHO2")),
  _muO3(declareProperty<Real>("muO3")),
  _muO3m(declareProperty<Real>("muO3m"))
{}

void
Water::computeQpProperties()
{
  _e[_qp]	= 1.6e-19;  // coulombic charge
  _k[_qp]	= 1.38e-23; // Boltzmanns constant
  _T[_qp]	= 300;      // Simulation temperature
  _k1[_qp]	= 1.9e1;   // e + H2O-->H + OH-
  _k2[_qp]	= 6e11;     // e + H2O-->H + OH
  _k3[_qp]	= 1e8;      // 2e + 2H2O-->H2 + 2OH-
  _k4[_qp]	= 2.5e10;   // e + H + H2O-->H2 + OH-
  _k5[_qp]	= 3e10;     // e + OH-->OH-
  _k6[_qp]	= 2.2e10;   // e + O- + H2O --> 2OH-
  _k7[_qp]	= 2.3e10;   // e + H3O+ --> H2 + H2O
  _k8[_qp]	= 1.1e10;   // e + H2O2 --> OH + OH-
  _k9[_qp]	= 3.5e9;    // e + HO2- + H2O --> OH + 2OH-
  _k10[_qp]	= 1.9e10; // e + O2 --> O2-
  _k11[_qp]	= 1.9e10; // e + O --> O-
  _k12[_qp]	= 1.0e1;  // H + H2O --> H2 + OH
  _k13[_qp]	= 7.5e9;  // 2H --> H2
  _k14[_qp]	= 7.0e9;  // H + OH --> H2O
  _k15[_qp]	= 2.2e7;  // H + OH- --> H2O + e
  _k16[_qp]	= 9.0e7;  // H + H2O2 --> OH + H2O
  _k17[_qp]	= 6.0e6;  // H2 + H2O2 --> H + OH + H2O
  _k18[_qp]	= 2.1e10; // H + O2 --> HO2
  _k19[_qp]	= 1.0e10; // H + HO2 --> H2O2
  _k20[_qp]	= 1.3e4;  // O + H2O --> 2OH
  _k21[_qp]	= 3.0e9;  // O + O2 --> O3
  _k22[_qp]	= 5.5e9;  // 2OH --> H2O2
  _k23[_qp]	= 2.0e10; // OH + O- --> HO2-
  _k24[_qp]	= 4.2e7;  // OH + H2 --> H + H2O
  _k25[_qp]	= 1.3e10; // OH + OH- --> O- + H2O
  _k26[_qp]	= 6.0e9;  // OH + HO2 --> H2O + O2
  _k27[_qp]	= 8.0e9;  // OH + O2- --> OH- + O2
  _k28[_qp]	= 1.8e6;  // ] O- + H2O --> OH- + OH
  _k29[_qp]	= 8.0e7;  // O- + H2 --> OH- + H
  _k30[_qp]	= 5.0e8;  // O- + H2O2 --> O2- + H2O
  _k31[_qp]	= 4.0e8;  // O- + HO2- --> O2- + OH-
  _k32[_qp]	= 3.6e9;  // O- + O2- --> O3-
  _k33[_qp]	= 6.0e8;  // O- + O2- + H2O --> 2OH- + O2
  _k34[_qp]	= 2.7e7;  // OH + H2O2 --> H2O + HO2
  _k35[_qp]	= 7.5e9;  // OH + HO2- --> OH- + HO2
  _k36[_qp]	= 6.0e3;  // H2O+ + H2O --> H3O+ + OH
  _k37[_qp]	= 6.0e10; // H3O+ + OH- --> H + OH + H2O
  _k38[_qp]	= 2.0e3;  // HO2 + H2O --> H3O+ + O2-
  _k39[_qp]	= 6.0e1;  // H3O+ O2- --> HO2 + H2O
  _Dem[_qp]	= 4.5e-9;	// diffusivity of hydrated electron
  _DH[_qp]	= 5e-9;		// H radical
  _DOHm[_qp]	= 5.27e-9;	// OH- ion
  _DH2Op[_qp]	= 5e-9;		// H2O+ ion
  _DOH[_qp]	= 5e-9;		// OH radical
  _DH2[_qp]	= 4.5e-9;	// H2 molecule
  _DOm[_qp]	= 5e-9;		// O- ion
  _DH3Op[_qp]	= 9.3e-9;	// H3O+ ion
  _DH2O2[_qp]	= 5e-9;		// H2O2 molecule
  _DHO2m[_qp]	= 5e-9;		// HO2- ion
  _DO2[_qp]	= 2e-9;		// O2 molecule
  _DO2m[_qp]	= 5e-9;		// O2- ion
  _DO[_qp]	= 5e-9;		// O radical
  _DHO2[_qp]	= 5e-9;		// HO2 radical
  _DO3[_qp]	= 5e-9;		// O3 molecule
  _DO3m[_qp]	= 5e-9;		// O3- ion
  _zem[_qp]	= -1;		// charge of hydrated electron
  _zH[_qp]	= 0;		// H radical
  _zOHm[_qp]	= -1;		// OH- ion
  _zH2Op[_qp]	= 1;		// H2O+ ion
  _zOH[_qp]	= 0;		// OH radical
  _zH2[_qp]	= 0;		// H2 molecule
  _zOm[_qp]	= -1;		// O- ion
  _zH3Op[_qp]	= 1;		// H3O+ ion
  _zH2O2[_qp]	= 0;		// H2O2 molecule
  _zHO2m[_qp]	= -1;		// HO2- ion
  _zO2[_qp]	= 0;		// O2 molecule
  _zO2m[_qp]	= -1;		// O2- ion
  _zO[_qp]	= 0;		// O radical
  _zHO2[_qp]	= 0;		// HO2 radical
  _zO3[_qp]	= 0;		// O3 molecule
  _zO3m[_qp]	= -1;		// O3- ion
  _muem[_qp]	= abs(_zem[_qp])*_e[_qp]*_Dem[_qp]/_k[_qp]/_T[_qp];	// mobility of hydrated electron
  _muH[_qp]	= abs(_zH[_qp])*_e[_qp]*_DH[_qp]/_k[_qp]/_T[_qp];	// H radical
  _muOHm[_qp]	= abs(_zOHm[_qp])*_e[_qp]*_DOHm[_qp]/_k[_qp]/_T[_qp];	// OH- ion
  _muH2Op[_qp]	= abs(_zH2Op[_qp])*_e[_qp]*_DH2Op[_qp]/_k[_qp]/_T[_qp];	// H2O+ ion
  _muOH[_qp]	= abs(_zOH[_qp])*_e[_qp]*_DOH[_qp]/_k[_qp]/_T[_qp];	// OH radical
  _muH2[_qp]	= abs(_zH2[_qp])*_e[_qp]*_DH2[_qp]/_k[_qp]/_T[_qp];	// H2 molecule
  _muOm[_qp]	= abs(_zOm[_qp])*_e[_qp]*_DOm[_qp]/_k[_qp]/_T[_qp];	// O- ion
  _muH3Op[_qp]	= abs(_zH3Op[_qp])*_e[_qp]*_DH3Op[_qp]/_k[_qp]/_T[_qp];	// H3O+ ion
  _muH2O2[_qp]	= abs(_zH2O2[_qp])*_e[_qp]*_DH2O2[_qp]/_k[_qp]/_T[_qp];	// H2O2 molecule
  _muHO2m[_qp]	= abs(_zHO2m[_qp])*_e[_qp]*_DHO2m[_qp]/_k[_qp]/_T[_qp];	// HO2- ion
  _muO2[_qp]	= abs(_zO2[_qp])*_e[_qp]*_DO2[_qp]/_k[_qp]/_T[_qp];	// O2 molecule
  _muO2m[_qp]	= abs(_zO2m[_qp])*_e[_qp]*_DO2m[_qp]/_k[_qp]/_T[_qp];	// O2- ion
  _muO[_qp]	= abs(_zO[_qp])*_e[_qp]*_DO[_qp]/_k[_qp]/_T[_qp];	// O radical
  _muHO2[_qp]	= abs(_zHO2[_qp])*_e[_qp]*_DHO2[_qp]/_k[_qp]/_T[_qp];	// HO2 radical
  _muO3[_qp]	= abs(_zO3[_qp])*_e[_qp]*_DO3[_qp]/_k[_qp]/_T[_qp];	// O3 molecule
  _muO3m[_qp]	= abs(_zO3m[_qp])*_e[_qp]*_DO3m[_qp]/_k[_qp]/_T[_qp];	// O3- ion
}
