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
#include "JacMat.h"

registerMooseObject("ZapdosApp", JacMat);

template <>
InputParameters
validParams<JacMat>()
{
  InputParameters params = validParams<Material>();
  params.addCoupledVar("v", "A variable for interpolation tests.");
  params.addCoupledVar("mean_en", "A variable for interpolation tests.");
  params.addCoupledVar("em", "A variable for interpolation tests.");
  params.addCoupledVar("emliq", "A variable for interpolation tests.");
  params.addRequiredParam<FileName>(
      "property_tables_file", "The file containing interpolation tables for material properties.");
  return params;
}

JacMat::JacMat(const InputParameters & parameters)
  : Material(parameters),
    _muu(declareProperty<Real>("muu")),
    _muv(declareProperty<Real>("muv")),
    _sgnu(declareProperty<Real>("sgnu")),
    _sgnem(declareProperty<Real>("sgnem")),
    _sgnmean_en(declareProperty<Real>("sgnmean_en")),
    _sgnv(declareProperty<Real>("sgnv")),
    _diffu(declareProperty<Real>("diffu")),
    _diffem(declareProperty<Real>("diffem")),
    _diffmean_en(declareProperty<Real>("diffmean_en")),
    _muem(declareProperty<Real>("muem")),
    _mumean_en(declareProperty<Real>("mumean_en")),
    _diffpotential(declareProperty<Real>("diffpotential")),
    _iz_coeff_efield_a(declareProperty<Real>("iz_coeff_efield_a")),
    _iz_coeff_efield_b(declareProperty<Real>("iz_coeff_efield_b")),
    _iz_coeff_efield_c(declareProperty<Real>("iz_coeff_efield_c")),
    _ku(declareProperty<Real>("ku")),
    _kuu(declareProperty<Real>("kuu")),
    _N_A(declareProperty<Real>("N_A")),
    _e(declareProperty<Real>("e")),
    _kv(declareProperty<Real>("kv")),
    _kvv(declareProperty<Real>("kvv")),
    _diffu1(declareProperty<Real>("diffu1")),
    _diffu2(declareProperty<Real>("diffu2")),
    _se_coeff(declareProperty<Real>("se_coeff")),
    _se_energy(declareProperty<Real>("se_energy")),
    _eps(declareProperty<Real>("eps")),
    _mem(declareProperty<Real>("mem")),
    _d_interp(declareProperty<Real>("d_interp")),
    _d_d_interp_d_v(declareProperty<Real>("d_d_interp_d_v")),
    _d_muem_d_actual_mean_en(declareProperty<Real>("d_muem_d_actual_mean_en")),
    _d_mumean_en_d_actual_mean_en(declareProperty<Real>("d_mumean_en_d_actual_mean_en")),
    _d_diffem_d_actual_mean_en(declareProperty<Real>("d_diffem_d_actual_mean_en")),
    _d_diffmean_en_d_actual_mean_en(declareProperty<Real>("d_diffmean_en_d_actual_mean_en")),
    _alpha_iz(declareProperty<Real>("alpha_iz")),
    _d_iz_d_actual_mean_en(declareProperty<Real>("d_iz_d_actual_mean_en")),
    _alpha_ex(declareProperty<Real>("alpha_ex")),
    _d_ex_d_actual_mean_en(declareProperty<Real>("d_ex_d_actual_mean_en")),
    _alpha_el(declareProperty<Real>("alpha_el")),
    _d_el_d_actual_mean_en(declareProperty<Real>("d_el_d_actual_mean_en")),
    _Eiz(declareProperty<Real>("Eiz")),
    _Eex(declareProperty<Real>("Eex")),
    _mGas(declareProperty<Real>("mGas")),
    _k_boltz(declareProperty<Real>("k_boltz")),
    _T_heavy(declareProperty<Real>("T_heavy")),
    _massu(declareProperty<Real>("massu")),
    _massArp(declareProperty<Real>("massArp")),
    _sgnp(declareProperty<Real>("sgnp")),
    _mup(declareProperty<Real>("mup")),
    _muw(declareProperty<Real>("muw")),
    _diffp(declareProperty<Real>("diffp")),
    _muArp(declareProperty<Real>("muArp")),
    _diffArp(declareProperty<Real>("diffArp")),
    _sgnArp(declareProperty<Real>("sgnArp")),
    _actual_mean_en(declareProperty<Real>("actual_mean_en")),
    _muOHm(declareProperty<Real>("muOHm")),
    _diffOHm(declareProperty<Real>("diffOHm")),
    _sgnOHm(declareProperty<Real>("sgnOHm")),
    _muemliq(declareProperty<Real>("muemliq")),
    _diffemliq(declareProperty<Real>("diffemliq")),
    _sgnemliq(declareProperty<Real>("sgnemliq")),
    _kemliqemliq(declareProperty<Real>("kemliqemliq")),
    _kemliq(declareProperty<Real>("kemliq")),

    _v(isCoupled("v") ? coupledValue("v") : _zero),
    _mean_en(isCoupled("mean_en") ? coupledValue("mean_en") : _zero),
    _em(isCoupled("em") ? coupledValue("em") : _zero),
    _emliq(isCoupled("emliq") ? coupledValue("emliq") : _zero)

{
  std::vector<Real> actual_mean_energy;
  std::vector<Real> alpha;
  std::vector<Real> alphaEx;
  std::vector<Real> alphaEl;
  std::vector<Real> mu;
  std::vector<Real> diff;

  std::string file_name = getParam<FileName>("property_tables_file");
  MooseUtils::checkFileReadable(file_name);
  const char * charPath = file_name.c_str();
  std::ifstream newfile(charPath);
  Real value_new;

  if (newfile.is_open())
  {
    while (newfile >> value_new)
    {
      actual_mean_energy.push_back(value_new);
      newfile >> value_new;
      alpha.push_back(value_new);
      newfile >> value_new;
      alphaEx.push_back(value_new);
      newfile >> value_new;
      alphaEl.push_back(value_new);
      newfile >> value_new;
      mu.push_back(value_new);
      newfile >> value_new;
      diff.push_back(value_new);
    }
    newfile.close();
  }

  else
    mooseError("Unable to open file");

  _alpha_interpolation.setData(actual_mean_energy, alpha);
  // _d_alpha_d_actual_mean_energy_interpolation.setData(actual_mean_energy,
  // d_alpha_d_actual_mean_energy);
  _alphaEx_interpolation.setData(actual_mean_energy, alphaEx);
  _alphaEl_interpolation.setData(actual_mean_energy, alphaEl);
  _mu_interpolation.setData(actual_mean_energy, mu);
  _diff_interpolation.setData(actual_mean_energy, diff);
}

void
JacMat::computeQpProperties()
{
  _muu[_qp] = 1.1;
  _muv[_qp] = 1.1;
  _sgnu[_qp] = -1.;
  _sgnem[_qp] = -1.;
  _sgnmean_en[_qp] = -1;
  _sgnv[_qp] = -1.;
  _diffu[_qp] = 1.1;
  _actual_mean_en[_qp] = std::exp(_mean_en[_qp] - _em[_qp]);
  _muem[_qp] = _mu_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp]));
  // _muem[_qp] = 1.1;
  _mumean_en[_qp] = 5. / 3. * _muem[_qp];
  _diffem[_qp] = _diff_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp]));
  // _diffem[_qp] = 1.1;
  _diffmean_en[_qp] = 5. / 3. * _diffem[_qp];
  _d_muem_d_actual_mean_en[_qp] =
      _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp]));
  // _d_muem_d_actual_mean_en[_qp] = 0.;
  _d_mumean_en_d_actual_mean_en[_qp] = 5. / 3. * _d_muem_d_actual_mean_en[_qp];
  _d_diffem_d_actual_mean_en[_qp] =
      _diff_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp]));
  // _d_diffem_d_actual_mean_en[_qp] = 0;
  _d_diffmean_en_d_actual_mean_en[_qp] = 5. / 3. * _d_diffem_d_actual_mean_en[_qp];
  _diffpotential[_qp] = 1.1;
  _muOHm[_qp] = 1.1;
  _diffOHm[_qp] = 1.1;
  _sgnOHm[_qp] = 1.;
  _muemliq[_qp] = 1.1;
  _diffemliq[_qp] = 1.1;
  _sgnemliq[_qp] = -1.;

  _kemliqemliq[_qp] = 1.1;
  _kemliq[_qp] = 1.1;
  _iz_coeff_efield_a[_qp] = 1.1;
  _iz_coeff_efield_b[_qp] = 1.1;
  _iz_coeff_efield_c[_qp] = 1.1;
  _ku[_qp] = 1.1;
  _kuu[_qp] = 1.1;
  _N_A[_qp] = 1.1;
  _e[_qp] = 1.1;
  _kv[_qp] = 1.1;
  _kvv[_qp] = 1.1;
  _diffu1[_qp] = 1.1;
  _diffu2[_qp] = 1.1;
  _se_coeff[_qp] = 0.1;
  _se_energy[_qp] = 1.1;
  _eps[_qp] = 1.1;
  _mem[_qp] = 1.1;
  _alpha_iz[_qp] = _alpha_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp]));
  _d_iz_d_actual_mean_en[_qp] =
      _alpha_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp]));
  _alpha_ex[_qp] = _alphaEx_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp]));
  _d_ex_d_actual_mean_en[_qp] =
      _alphaEx_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp]));
  _alpha_el[_qp] = _alphaEl_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp]));
  _d_el_d_actual_mean_en[_qp] =
      _alphaEl_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp]));
  _Eiz[_qp] = 1.1;
  _Eex[_qp] = 1.1;
  _mem[_qp] = 1.1;
  _mGas[_qp] = 1.1;
  _k_boltz[_qp] = 1.1;
  _T_heavy[_qp] = 1.1;
  _massu[_qp] = 1.1;
  _massArp[_qp] = 1.1;
  _sgnp[_qp] = -1.;
  _mup[_qp] = 1.1;
  _muw[_qp] = 1.1;
  _diffp[_qp] = 1.1;
  _muArp[_qp] = 1.1;
  _diffArp[_qp] = 1.1;
  _sgnArp[_qp] = -1.;
}
