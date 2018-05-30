#include "GasBase.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", GasBase);

template <>
InputParameters
validParams<GasBase>()
{
  InputParameters params = validParams<Material>();

  params.addParam<Real>(
      "user_relative_permittivity", 1.0, "Multiplies the permittivity of free space.");
  // params.addRequiredParam<bool>("townsend","Whether to use the townsend formulation for the rate
  // terms.");
  params.addRequiredParam<bool>("interp_trans_coeffs",
                                "Whether to interpolate transport "
                                "coefficients as a function of the mean "
                                "energy. If false, coeffs are constant.");
  params.addRequiredParam<bool>("interp_elastic_coeff",
                                "Whether to interpolate the elastic collision townsend coefficient "
                                "as a function of the mean energy. If false, coeffs are constant.");
  params.addRequiredParam<bool>("ramp_trans_coeffs",
                                "Whether to ramp the non-linearity of coming "
                                "from the electron energy dependence of the "
                                "transport coefficients.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<bool>("use_moles",
                                "Whether to use units of moles as opposed to # of molecules.");
  params.addRequiredParam<FileName>(
      "property_tables_file", "The file containing interpolation tables for material properties.");
  params.addRequiredParam<Real>("position_units", "Units of position.");

  params.addParam<Real>("user_se_coeff", 0.15, "The secondary electron emission coefficient.");
  params.addParam<Real>("user_work_function", 5.00, "The work function.");
  params.addParam<Real>("user_field_enhancement", 1, "The field enhancement factor.");

  params.addParam<Real>("user_Richardson_coefficient", 1.20173E6, "The Richardson coefficient.");
  params.addParam<Real>("user_cathode_temperature", 300, "The cathode temperature in Kelvin.");

  params.addParam<Real>("user_T_gas", 300, "The gas temperature in Kelvin.");
  params.addParam<Real>("user_p_gas", 1.01e5, "The gas pressure in Pascals.");

  params.addCoupledVar("potential", "The potential for calculating the electron velocity");
  params.addCoupledVar("em", "Species concentration needed to calculate the poisson source");
  params.addCoupledVar("mean_en", "The electron mean energy in log form.");
  params.addCoupledVar("ip", "The ion density.");
  return params;
}

GasBase::GasBase(const InputParameters & parameters)
  : Material(parameters),
    // _townsend(getParam<bool>("townsend")),
    _r_units(1. / getParam<Real>("position_units")),
    _interp_trans_coeffs(getParam<bool>("interp_trans_coeffs")),
    _interp_elastic_coeff(getParam<bool>("interp_elastic_coeff")),
    _ramp_trans_coeffs(getParam<bool>("ramp_trans_coeffs")),
    _potential_units(getParam<std::string>("potential_units")),
    _user_se_coeff(getParam<Real>("user_se_coeff")),
    _user_work_function(getParam<Real>("user_work_function")),
    _user_field_enhancement(getParam<Real>("user_field_enhancement")),

    _user_Richardson_coefficient(getParam<Real>("user_Richardson_coefficient")),
    _user_cathode_temperature(getParam<Real>("user_cathode_temperature")),

    _user_T_gas(getParam<Real>("user_T_gas")),
    _user_p_gas(getParam<Real>("user_p_gas")),
    _use_moles(getParam<bool>("use_moles")),

    _muem(declareProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(declareProperty<Real>("d_muem_d_actual_mean_en")),
    _diffem(declareProperty<Real>("diffem")),
    _d_diffem_d_actual_mean_en(declareProperty<Real>("d_diffem_d_actual_mean_en")),
    // _muArp(declareProperty<Real>("muArp")),
    // _diffArp(declareProperty<Real>("diffArp")),
    _rate_coeff_ion(declareProperty<Real>("rate_coeff_ion")),
    _Eiz(declareProperty<Real>("Eiz")),
    _Eex(declareProperty<Real>("Eex")),
    // _Ar(declareProperty<Real>("Ar")),
    _mumean_en(declareProperty<Real>("mumean_en")),
    _d_mumean_en_d_actual_mean_en(declareProperty<Real>("d_mumean_en_d_actual_mean_en")),
    _diffmean_en(declareProperty<Real>("diffmean_en")),
    _d_diffmean_en_d_actual_mean_en(declareProperty<Real>("d_diffmean_en_d_actual_mean_en")),
    _rate_coeff_elastic(declareProperty<Real>("rate_coeff_elastic")),
    _massem(declareProperty<Real>("massem")),
    _massGas(declareProperty<Real>("massGas")),
    // _massArp(declareProperty<Real>("massArp")),
    _se_coeff(declareProperty<Real>("se_coeff")),
    _work_function(declareProperty<Real>("work_function")),
    _field_enhancement(declareProperty<Real>("field_enhancement")),

    _Richardson_coefficient(declareProperty<Real>("Richardson_coefficient")),
    _cathode_temperature(declareProperty<Real>("cathode_temperature")),

    _se_energy(declareProperty<Real>("se_energy")),

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
    _Avogadro(declareProperty<Real>("Avogadro")),
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
    // _kArIz(declareProperty<Real>("kArIz")),
    // _alpha_ArIz(declareProperty<Real>("alpha_ArIz")),
    _d_iz_d_actual_mean_en(declareProperty<Real>("d_iz_d_actual_mean_en")),
    _alpha_ex(declareProperty<Real>("alpha_ex")),
    _d_ex_d_actual_mean_en(declareProperty<Real>("d_ex_d_actual_mean_en")),
    _alpha_el(declareProperty<Real>("alpha_el")),
    _d_el_d_actual_mean_en(declareProperty<Real>("d_el_d_actual_mean_en")),
    // _kArEx(declareProperty<Real>("kArEx")),
    _sgnem(declareProperty<Real>("sgnem")),
    _sgnmean_en(declareProperty<Real>("sgnmean_en")),
    // _sgnArp(declareProperty<Real>("sgnArp")),
    _diffpotential(declareProperty<Real>("diffpotential")),
    _actual_mean_energy(declareProperty<Real>("actual_mean_energy")),
    // _TArp(declareProperty<Real>("TArp")),
    _Tem(declareProperty<Real>("Tem")),
    // _muu(declareProperty<Real>("muu")),
    _diffu(declareProperty<Real>("diffu")),
    _sgnu(declareProperty<Real>("sgnu")),
    _T_gas(declareProperty<Real>("T_gas")),
    _p_gas(declareProperty<Real>("p_gas")),
    _n_gas(declareProperty<Real>("n_gas")),
    _kiz(declareProperty<Real>("kiz")),
    _kex(declareProperty<Real>("kex")),
    _kArp(declareProperty<Real>("kArp")),
    _kel(declareProperty<Real>("kel")),
    _d_kiz_d_actual_mean_en(declareProperty<Real>("d_kiz_d_actual_mean_en")),
    _d_kex_d_actual_mean_en(declareProperty<Real>("d_kex_d_actual_mean_en")),
    _d_kel_d_actual_mean_en(declareProperty<Real>("d_kel_d_actual_mean_en")),
    _TemVolts(declareProperty<Real>("TemVolts")),

    // _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _grad_zero),
    _em(isCoupled("em") ? coupledValue("em") : _zero),
    _ip(isCoupled("ip") ? coupledValue("ip") : _zero),
    _grad_em(isCoupled("em") ? coupledGradient("em") : _grad_zero),
    _grad_ip(isCoupled("ip") ? coupledGradient("ip") : _grad_zero),
    _mean_en(isCoupled("mean_en") ? coupledValue("mean_en") : _zero),
    _grad_potential(coupledGradient("potential"))
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  std::vector<Real> actual_mean_energy;
  std::vector<Real> alpha;
  // std::vector<Real> kArIz;
  std::vector<Real> alphaEx;
  std::vector<Real> alphaEl;
  // std::vector<Real> kArExIz;
  std::vector<Real> mu;
  std::vector<Real> diff;
  // std::vector<Real> d_alpha_d_actual_mean_energy;

  std::string file_name = getParam<FileName>("property_tables_file");
  MooseUtils::checkFileReadable(file_name);
  const char * charPath = file_name.c_str();
  std::ifstream myfile(charPath);
  Real value;

  if (myfile.is_open())
  {
    while (myfile >> value)
    {
      actual_mean_energy.push_back(value);
      myfile >> value;
      alpha.push_back(value);
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

  else
    mooseError("Unable to open file");

  _alpha_interpolation.setData(actual_mean_energy, alpha);
  _alphaEx_interpolation.setData(actual_mean_energy, alphaEx);
  _alphaEl_interpolation.setData(actual_mean_energy, alphaEl);
  _mu_interpolation.setData(actual_mean_energy, mu);
  _diff_interpolation.setData(actual_mean_energy, diff);
}

void
GasBase::computeQpProperties()
{
  _massem[_qp] = 9.11e-31;
  _massGas[_qp] = 40.0 * 1.66e-27;
  _T_gas[_qp] = _user_T_gas;
  _p_gas[_qp] = _user_p_gas;
  _k_boltz[_qp] = 1.38e-23;
  _Avogadro[_qp] = 6.0221409E23;
  if (_use_moles)
    _n_gas[_qp] = _p_gas[_qp] / (8.3145 * _T_gas[_qp]);
  else
    _n_gas[_qp] = _p_gas[_qp] / (_k_boltz[_qp] * _T_gas[_qp]);
  _se_coeff[_qp] = _user_se_coeff;
  _work_function[_qp] = _user_work_function;
  _field_enhancement[_qp] = _user_field_enhancement;

  _Richardson_coefficient[_qp] = _user_Richardson_coefficient;
  _cathode_temperature[_qp] = _user_cathode_temperature;

  _se_energy[_qp] = 2. * 3. / 2.; // Emi uses 2 Volts coming off the wall (presumably for Te).
                                  // Multiply by 3/2 to get mean_en
  _e[_qp] = 1.6e-19;
  _eps[_qp] = 8.85e-12;
  _sgnem[_qp] = -1.;
  _sgnmean_en[_qp] = -1.;
  _diffpotential[_qp] = _eps[_qp];


  // With the exception of temperature/energy (generally in eV), all properties are in standard SI
  // units unless otherwise indicated

  if (_interp_trans_coeffs)
  {
    if (_ramp_trans_coeffs)
    {
      _muem[_qp] =
          (std::tanh(_t / 1e-6) * _mu_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp])) +
           (1. - std::tanh(_t / 1e-6)) * .0352) *
          _voltage_scaling;
      _d_muem_d_actual_mean_en[_qp] =
          std::tanh(_t / 1e-6) *
          _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp])) * _voltage_scaling;
      _diffem[_qp] =
          std::tanh(_t / 1e-6) * _diff_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp])) +
          (1. - std::tanh(_t / 1e-6)) * .30;
      _d_diffem_d_actual_mean_en[_qp] =
          std::tanh(_t / 1e-6) *
          _diff_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp]));
    }
    else
    {
      _muem[_qp] = _mu_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp])) * _voltage_scaling;
      _d_muem_d_actual_mean_en[_qp] =
          _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp])) * _voltage_scaling;
      _diffem[_qp] = _diff_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp]));
      _d_diffem_d_actual_mean_en[_qp] =
          _diff_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp]));
    }
  }
  else
  {
    // From bolos at atmospheric pressure and an EField of 2e5 V/m
    _muem[_qp] =
        0.0352103411399 * _voltage_scaling; // units of m^2/(kV*s) if _voltage_scaling = 1000
    _d_muem_d_actual_mean_en[_qp] = 0.0;
    _diffem[_qp] = 0.297951680159;
    _d_diffem_d_actual_mean_en[_qp] = 0.0;
  }

  // From curve fitting with bolos
  _iz_coeff_efield_a[_qp] = 1.43171672e-1;
  _iz_coeff_efield_b[_qp] = 9.05925536e-1;
  _iz_coeff_efield_c[_qp] = 3.04958892e+6;

  _iz_coeff_energy_a[_qp] = 1.52165930e+8;
  _iz_coeff_energy_b[_qp] = -2.87277596e-1;
  _iz_coeff_energy_c[_qp] = 5.51972192e+1;


  _actual_mean_energy[_qp] = std::exp(_mean_en[_qp] - _em[_qp]);
  _alpha_iz[_qp] = _alpha_interpolation.sample(_actual_mean_energy[_qp]);
  // _kArIz[_qp] = _kArIz_interpolation.sample(_actual_mean_energy[_qp]);
  _d_iz_d_actual_mean_en[_qp] =
      _alpha_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp]));
  // _kArEx[_qp] = _kArExIz_interpolation.sample(_actual_mean_energy[_qp]);
  _alpha_ex[_qp] = _alphaEx_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp]));
  _d_ex_d_actual_mean_en[_qp] =
      _alphaEx_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp]));
  if (_interp_elastic_coeff)
  {
    _alpha_el[_qp] = _alphaEl_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp]));
    _d_el_d_actual_mean_en[_qp] =
        _alphaEl_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp]));
  }
  else
  {
    _alpha_el[_qp] = 5e8;
    _d_el_d_actual_mean_en[_qp] = 0.0;
  }

  _el_coeff_energy_a[_qp] = 1.60638169e-13;
  _el_coeff_energy_b[_qp] = 3.17917979e-1;
  _el_coeff_energy_c[_qp] = 4.66301096;

  _N_A[_qp] = 6.02e23;
  _Eiz[_qp] = 15.76;
  _Eex[_qp] = 11.5;

  // From Hagelaar: The below approximations can be derived assumption Maxwell EEDF, const
  // momentum-transfer frequency, and constant kinetic pressure.
  _mumean_en[_qp] = 5.0 / 3.0 * _muem[_qp];
  _diffmean_en[_qp] = 5.0 / 3.0 * _diffem[_qp];
  if (_interp_trans_coeffs)
  {
    _d_mumean_en_d_actual_mean_en[_qp] = 5.0 / 3.0 * _d_muem_d_actual_mean_en[_qp];
    _d_diffmean_en_d_actual_mean_en[_qp] = 5.0 / 3.0 * _d_diffem_d_actual_mean_en[_qp];
  }
  else
  {
    _d_mumean_en_d_actual_mean_en[_qp] = 0.0;
    _d_diffmean_en_d_actual_mean_en[_qp] = 0.0;
  }

  _rate_coeff_elastic[_qp] = 1e-13;

  _TemVolts[_qp] = 2. / 3. * std::exp(_mean_en[_qp] - _em[_qp]);
  _Tem[_qp] = _e[_qp] * _TemVolts[_qp] / _k_boltz[_qp];

  _kiz[_qp] = 2.34e-14 * std::pow(_TemVolts[_qp], .59) * std::exp(-17.44 / _TemVolts[_qp]);
  _d_kiz_d_actual_mean_en[_qp] =
      2.34e-14 * (.59 * std::pow(_TemVolts[_qp], .59 - 1.) * std::exp(-17.44 / _TemVolts[_qp]) +
                  std::pow(_TemVolts[_qp], .59) * std::exp(-17.44 / _TemVolts[_qp]) * 17.44 /
                      std::pow(_TemVolts[_qp], 2.)) *
      2. / 3.;
  _kex[_qp] = 2.48e-14 * std::pow(_TemVolts[_qp], .33) * std::exp(-12.78 / _TemVolts[_qp]);
  _kArp[_qp] = 2.48e-14 * std::pow(_TemVolts[_qp], .33) * std::exp(-12.78 / _TemVolts[_qp]);
  _d_kex_d_actual_mean_en[_qp] =
      2.48e-14 * (.33 * std::pow(_TemVolts[_qp], .33 - 1.) * std::exp(-12.78 / _TemVolts[_qp]) +
                  std::pow(_TemVolts[_qp], .33) * std::exp(-12.78 / _TemVolts[_qp]) * 12.78 /
                      std::pow(_TemVolts[_qp], 2.)) *
      2. / 3.;

  // EField calculation test
  _EField[_qp] = _grad_potential[_qp](0)*_r_units;

  // Townsend calculation test
  // _alpha_ArIz[_qp] = _n_gas[_qp]*_kArIz[_qp]/(_muem[_qp]*_EField[_qp]);

  _kel[_qp] = 1e-13; // Approximate elastic rate coefficient
  _d_kel_d_actual_mean_en[_qp] = 0.;
  if (_use_moles)
  {
    _kiz[_qp] = _kiz[_qp] * _N_A[_qp];
    _d_kiz_d_actual_mean_en[_qp] = _d_kiz_d_actual_mean_en[_qp] * _N_A[_qp];
    _kex[_qp] = _kex[_qp] * _N_A[_qp];
    _kArp[_qp] = _kArp[_qp] * _N_A[_qp];
    _d_kex_d_actual_mean_en[_qp] = _d_kex_d_actual_mean_en[_qp] * _N_A[_qp];
    _kel[_qp] = _kel[_qp] * _N_A[_qp];
    _d_kel_d_actual_mean_en[_qp] = _d_kel_d_actual_mean_en[_qp] * _N_A[_qp];
  }
}
