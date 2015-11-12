/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
#include "ArgonConstTD.h"

template<>
InputParameters validParams<ArgonConstTD>()
{
  InputParameters params = validParams<Material>();

  params.addParam<Real>("user_relative_permittivity", 1.0, "Multiplies the permittivity of free space.");
  // params.addRequiredParam<bool>("townsend","Whether to use the townsend formulation for the rate terms.");
  params.addRequiredParam<bool>("interp_trans_coeffs", "Whether to interpolate transport coefficients as a function of the mean energy. If false, coeffs are constant.");
  params.addRequiredParam<bool>("interp_elastic_coeff", "Whether to interpolate the elastic collision townsend coefficient as a function of the mean energy. If false, coeffs are constant.");
  params.addCoupledVar("potential", "The potential for calculating the electron velocity");
  params.addRequiredCoupledVar("em", "Species concentration needed to calculate the poisson source");
  params.addCoupledVar("mean_en", "The electron mean energy in log form.");
  params.addCoupledVar("ip", "The ion density.");
  return params;
}


ArgonConstTD::ArgonConstTD(const InputParameters & parameters) :
    Material(parameters),
    // _townsend(getParam<bool>("townsend")),
    _interp_trans_coeffs(getParam<bool>("interp_trans_coeffs")),
    _interp_elastic_coeff(getParam<bool>("interp_elastic_coeff")),

    _muem(declareProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(declareProperty<Real>("d_muem_d_actual_mean_en")),
    _diffem(declareProperty<Real>("diffem")),
    _d_diffem_d_actual_mean_en(declareProperty<Real>("d_diffem_d_actual_mean_en")),
    _muArp(declareProperty<Real>("muArp")),
    _diffArp(declareProperty<Real>("diffArp")),
    _rate_coeff_ion(declareProperty<Real>("rate_coeff_ion")),
    _Eiz(declareProperty<Real>("Eiz")),
    _Eex(declareProperty<Real>("Eex")),
    _Ar(declareProperty<Real>("Ar")),
  _mumean_en(declareProperty<Real>("mumean_en")),
  _d_mumean_en_d_actual_mean_en(declareProperty<Real>("d_mumean_en_d_actual_mean_en")),
  _diffmean_en(declareProperty<Real>("diffmean_en")),
  _d_diffmean_en_d_actual_mean_en(declareProperty<Real>("d_diffmean_en_d_actual_mean_en")),
  _rate_coeff_elastic(declareProperty<Real>("rate_coeff_elastic")),
  _mem(declareProperty<Real>("mem")),
  _mGas(declareProperty<Real>("mGas")),
  _se_coeff(declareProperty<Real>("se_coeff")),
  _ElectronTotalFluxMag(declareProperty<Real>("ElectronTotalFluxMag")),
  _ElectronTotalFluxMagSizeForm(declareProperty<Real>("ElectronTotalFluxMagSizeForm")),
  _ElectronTotalFlux(declareProperty<Real>("ElectronTotalFlux")),
  _ElectronAdvectiveFlux(declareProperty<Real>("ElectronAdvectiveFlux")),
  _ElectronDiffusiveFlux(declareProperty<Real>("ElectronDiffusiveFlux")),
  _IonTotalFlux(declareProperty<Real>("IonTotalFlux")),
  _IonAdvectiveFlux(declareProperty<Real>("IonAdvectiveFlux")),
  _IonDiffusiveFlux(declareProperty<Real>("IonDiffusiveFlux")),
  _EField(declareProperty<Real>("EField")),
  _Source_term(declareProperty<Real>("Source_term")),
  _Source_term_coeff(declareProperty<Real>("Source_term_coeff")),
  _e(declareProperty<Real>("e")),
  _eps(declareProperty<Real>("eps")),
  _Tem_lfa(declareProperty<Real>("Tem_lfa")),
  _Tip_lfa(declareProperty<Real>("Tip_lfa")),
  _k_boltz(declareProperty<Real>("k_boltz")),
  _vthermal_em(declareProperty<Real>("vthermal_em")),
  _vthermal_ip(declareProperty<Real>("vthermal_ip")),
  _iz_coeff_efield_a(declareProperty<Real>("iz_coeff_efield_a")),
  _iz_coeff_efield_b(declareProperty<Real>("iz_coeff_efield_b")),
  _iz_coeff_efield_c(declareProperty<Real>("iz_coeff_efield_c")),
  _iz_coeff_energy_a(declareProperty<Real>("iz_coeff_energy_a")),
  _iz_coeff_energy_b(declareProperty<Real>("iz_coeff_energy_b")),
  _iz_coeff_energy_c(declareProperty<Real>("iz_coeff_energy_c")),
  _N_A(declareProperty<Real>("N_A")),
  _el_coeff_energy_a(declareProperty<Real>("el_coeff_energy_a")),
  _el_coeff_energy_b(declareProperty<Real>("el_coeff_energy_b")),
  _el_coeff_energy_c(declareProperty<Real>("el_coeff_energy_c")),
  _alpha_iz(declareProperty<Real>("alpha_iz")),
  _d_iz_d_actual_mean_en(declareProperty<Real>("d_iz_d_actual_mean_en")),
  _alpha_ex(declareProperty<Real>("alpha_ex")),
  _d_ex_d_actual_mean_en(declareProperty<Real>("d_ex_d_actual_mean_en")),
  _alpha_el(declareProperty<Real>("alpha_el")),
  _d_el_d_actual_mean_en(declareProperty<Real>("d_el_d_actual_mean_en")),
  _sgnem(declareProperty<Real>("sgnem")),
  _sgnmean_en(declareProperty<Real>("sgnmean_en")),
  _sgnArp(declareProperty<Real>("sgnArp")),
  _diffpotential(declareProperty<Real>("diffpotential")),
  // _diffusivity(declareProperty<Real>("diffusivity")),
  // _d_diffusivity_d_u(declareProperty<Real>("d_diffusivity_d_u")),

  _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _grad_zero),
  _em(coupledValue("em")),
  _ip(isCoupled("ip") ? coupledValue("ip") : _zero),
  _grad_em(coupledGradient("em")),
  _grad_ip(isCoupled("ip") ? coupledGradient("ip") : _grad_zero),
  _mean_en(isCoupled("mean_en") ? coupledValue("mean_en") : _zero)
{
  std::vector<Real> actual_mean_energy;
  std::vector<Real> alpha;
  std::vector<Real> alphaEx;
  std::vector<Real> alphaEl;
  std::vector<Real> mu;
  std::vector<Real> diff;
  // std::vector<Real> d_alpha_d_actual_mean_energy;
  // std::cerr << "About to get the environment variable." << std::endl;
  char* zapDirPoint;
  zapDirPoint = getenv("ZAPDIR");
  std::string zapDir;

  if (zapDirPoint == NULL) {
    std::cerr << "Environment variable ZAPDIR not defined." << std::endl;
    std::exit(1);
  }
  else {
    zapDir = std::string(zapDirPoint);
  }

  std::string tdPath = "/src/materials/td_argon_mean_en.txt";
  std::string path = zapDir + tdPath;
  const char *charPath = path.c_str();
  std::ifstream myfile (charPath);
  Real value;

  if (myfile.is_open())
  {
    while ( myfile >> value )
    {
      actual_mean_energy.push_back(value);
      myfile >> value;
      alpha.push_back(value);
      // myfile >> value;
      // d_alpha_d_actual_mean_energy.push_back(value);
      myfile >> value;
      alphaEx.push_back(value);
      myfile >> value;
      alphaEl.push_back(value);
      myfile >> value;
      mu.push_back(value);
      myfile >> value;
      diff.push_back(value);
    }
    myfile.close();
  }

  else std::cerr << "Unable to open file" << std::endl; 

  _alpha_interpolation.setData(actual_mean_energy, alpha);
  // _d_alpha_d_actual_mean_energy_interpolation.setData(actual_mean_energy, d_alpha_d_actual_mean_energy);
  _alphaEx_interpolation.setData(actual_mean_energy, alphaEx);
  _alphaEl_interpolation.setData(actual_mean_energy, alphaEl);
  _mu_interpolation.setData(actual_mean_energy, mu);
  _diff_interpolation.setData(actual_mean_energy, diff);
}

void
ArgonConstTD::computeQpProperties()
{
  // This is just a dummy material property for some simple functionality testing
  // _diffusivity[_qp] = _mean_en[_qp] + 1.;
  // _d_diffusivity_d_u[_qp] = 1.;

  // With the exception of perhaps temperature/energy (perhaps in eV), all properties are in standard SI units

  if (_interp_trans_coeffs) {  
    _muem[_qp] = _mu_interpolation.sample(std::exp(_mean_en[_qp]-_em[_qp]));
    _d_muem_d_actual_mean_en[_qp] = _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp]-_em[_qp]));
    _diffem[_qp] = _diff_interpolation.sample(std::exp(_mean_en[_qp]-_em[_qp]));
    _d_diffem_d_actual_mean_en[_qp] = _diff_interpolation.sampleDerivative(std::exp(_mean_en[_qp]-_em[_qp]));
  }
  else {
    // From bolos at atmospheric pressure and an EField of 2e5 V/m
    _muem[_qp] = 0.0352103411399;
    _d_muem_d_actual_mean_en[_qp] = 0.0;
    _diffem[_qp] = 0.297951680159;
    _d_diffem_d_actual_mean_en[_qp] = 0.0;
  }

  // From Richards and Sawin, muArp*pressure = 1444 cm^2*Torr/(V*s) and diffArp*pressure = 40 cm^2*Torr/s. Use pressure = 760 torr.
  _muArp[_qp] = 1.9e-4;
  _diffArp[_qp] = 5.26e-6;

  // 100 times less than electrons
  // _muArp[_qp] = 3.52e-4;
  // _diffArp[_qp] = 2.98e-3;

  // From curve fitting with bolos
  _iz_coeff_efield_a[_qp] = 1.43171672e-1;
  _iz_coeff_efield_b[_qp] = 9.05925536e-1;
  _iz_coeff_efield_c[_qp] = 3.04958892e+6;

  // if (_townsend) {
  _iz_coeff_energy_a[_qp] = 1.52165930e+8;
  _iz_coeff_energy_b[_qp] = -2.87277596e-1;
  _iz_coeff_energy_c[_qp] = 5.51972192e+1;
  // }
  // else {
  //   _iz_coeff_energy_a[_qp] = 1.43878529e-11;
  //   _iz_coeff_energy_b[_qp] = -2.70610234e-1;
  //   _iz_coeff_energy_c[_qp] = 7.64727794e+1;
  // }

  _alpha_iz[_qp] = _alpha_interpolation.sample(std::exp(_mean_en[_qp]-_em[_qp]));
  _d_iz_d_actual_mean_en[_qp] = _alpha_interpolation.sampleDerivative(std::exp(_mean_en[_qp]-_em[_qp]));
  // _d_iz_d_actual_mean_en[_qp] = _d_alpha_d_actual_mean_energy_interpolation.sample(std::exp(_mean_en[_qp]-_em[_qp]));
  _alpha_ex[_qp] = _alphaEx_interpolation.sample(std::exp(_mean_en[_qp]-_em[_qp]));
  _d_ex_d_actual_mean_en[_qp] = _alphaEx_interpolation.sampleDerivative(std::exp(_mean_en[_qp]-_em[_qp]));
  if (_interp_elastic_coeff) {
    _alpha_el[_qp] = _alphaEl_interpolation.sample(std::exp(_mean_en[_qp]-_em[_qp]));
    _d_el_d_actual_mean_en[_qp] = _alphaEl_interpolation.sampleDerivative(std::exp(_mean_en[_qp]-_em[_qp]));
  }
  else {
    _alpha_el[_qp] = 5e8;
    _d_el_d_actual_mean_en[_qp] = 0.0;
  }

  _el_coeff_energy_a[_qp] = 1.60638169e-13;
  _el_coeff_energy_b[_qp] = 3.17917979e-1;
  _el_coeff_energy_c[_qp] = 4.66301096;

  _N_A[_qp] = 6.02e23;
  _Ar[_qp] = 1.01e5/(300*1.38e-23);
  _Eiz[_qp] = 15.76;
  _Eex[_qp] = 11.5;

  // From Hagelaar: The below approximations can be derived assumption Maxwell EEDF, const momentum-transfer frequency, and constant kinetic pressure.
  _mumean_en[_qp] = 5.0/3.0*_muem[_qp];
  _diffmean_en[_qp] = 5.0/3.0*_diffem[_qp];
  if (_interp_trans_coeffs) {
    _d_mumean_en_d_actual_mean_en[_qp] = 5.0/3.0*_d_muem_d_actual_mean_en[_qp];
    _d_diffmean_en_d_actual_mean_en[_qp] = 5.0/3.0*_d_diffem_d_actual_mean_en[_qp];
  }
  else {
    _d_mumean_en_d_actual_mean_en[_qp] = 0.0;
    _d_diffmean_en_d_actual_mean_en[_qp] = 0.0;
  } 

  _rate_coeff_elastic[_qp] = 1e-13;
  _mem[_qp] = 9.11e-31;
  _mGas[_qp] = 40.0*1.66e-27;
  _se_coeff[_qp] = 0.1;
  _e[_qp] = 1.6e-19;
  _eps[_qp] = 8.85e-12;
  // _Tem_lfa[_qp] = 1.0; // Volts
  // _Tip_lfa[_qp] = 300; // Kelvin
  _k_boltz[_qp] = 1.38e-23;
  // _vthermal_em[_qp] = 1.6*sqrt(_e[_qp]*_Tem_lfa[_qp]/_mem[_qp]);
  // _vthermal_ip[_qp] = 1.6*sqrt(_k_boltz[_qp]*_Tip_lfa[_qp]/_mGas[_qp]);
  _sgnem[_qp] = -1.;
  _sgnmean_en[_qp] = -1.;
  _sgnArp[_qp] = 1.;
  _diffpotential[_qp] = _eps[_qp];

  // _ElectronTotalFluxMag[_qp] = std::sqrt((-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp])*(-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]));
  // _ElectronTotalFluxMagSizeForm[_qp] = (-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]).size();
  // _ElectronTotalFlux[_qp] = -_muem[_qp]*-_grad_potential[_qp](0)*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp](0);
  // _ElectronAdvectiveFlux[_qp] = -_muem[_qp]*-_grad_potential[_qp](0)*std::exp(_em[_qp]);
  // _ElectronDiffusiveFlux[_qp] = -_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp](0);
  // _IonTotalFlux[_qp] = -_muArp[_qp]*-_grad_potential[_qp](0)*std::exp(_ip[_qp])-_diffArp[_qp]*std::exp(_ip[_qp])*_grad_ip[_qp](0);
  // _IonAdvectiveFlux[_qp] = -_muArp[_qp]*-_grad_potential[_qp](0)*std::exp(_ip[_qp]);
  // _IonDiffusiveFlux[_qp] = -_diffArp[_qp]*std::exp(_ip[_qp])*_grad_ip[_qp](0);
  _EField[_qp] = -_grad_potential[_qp](0);
  // _Source_term[_qp] = _rate_coeff_ion[_qp]*std::exp(-_Eiz[_qp]/_grad_potential[_qp].size())*(-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]).size();
  // _Source_term_coeff[_qp] = _rate_coeff_ion[_qp]*std::exp(-_Eiz[_qp]/_grad_potential[_qp].size());
}
