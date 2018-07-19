/****************************************************************/
/*                      DO NOT MODIFY THIS HEADER               */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*              (c) 2010 Battelle Energy Alliance, LLC          */
/*                      ALL RIGHTS RESERVED                     */
/*                                                              */
/*              Prepared by Battelle Energy Alliance, LLC       */
/*              Under Contract No. DE-AC07-05ID14517            */
/*              With the U. S. Department of Energy             */
/*                                                              */
/*              See COPYRIGHT for full restrictions             */
/****************************************************************/
#ifndef GASBASE_H_
#define GASBASE_H_

#include "Material.h"
/* #include "LinearInterpolation.h" */
#include "SplineInterpolation.h"

class GasBase;

template <>
InputParameters validParams<GasBase>();

class GasBase : public Material
{
public:
  GasBase(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  SplineInterpolation _alpha_interpolation;
  SplineInterpolation _alphaEx_interpolation;
  SplineInterpolation _alphaEl_interpolation;
  SplineInterpolation _mu_interpolation;
  SplineInterpolation _diff_interpolation;

  Real _r_units;
  bool _interp_trans_coeffs;
  bool _interp_elastic_coeff;
  bool _ramp_trans_coeffs;
  std::string _potential_units;
  Real _voltage_scaling;
  Real _user_se_coeff;
  Real _user_work_function;
  Real _user_field_enhancement;
  Real _user_Richardson_coefficient;
  Real _user_cathode_temperature;
  Real _user_T_gas;
  Real _user_p_gas;
  bool _use_moles;

  MaterialProperty<Real> & _muem;
  MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  MaterialProperty<Real> & _diffem;
  MaterialProperty<Real> & _d_diffem_d_actual_mean_en;
  MaterialProperty<Real> & _rate_coeff_ion;
  MaterialProperty<Real> & _Eiz;
  MaterialProperty<Real> & _Eex;
  MaterialProperty<Real> & _mumean_en;
  MaterialProperty<Real> & _d_mumean_en_d_actual_mean_en;
  MaterialProperty<Real> & _diffmean_en;
  MaterialProperty<Real> & _d_diffmean_en_d_actual_mean_en;
  MaterialProperty<Real> & _rate_coeff_elastic;
  MaterialProperty<Real> & _massem;
  MaterialProperty<Real> & _massGas;
  MaterialProperty<Real> & _se_coeff;
  MaterialProperty<Real> & _work_function;
  MaterialProperty<Real> & _field_enhancement;
  MaterialProperty<Real> & _Richardson_coefficient;
  MaterialProperty<Real> & _cathode_temperature;
  MaterialProperty<Real> & _se_energy;
  MaterialProperty<Real> & _ElectronTotalFluxMag;
  MaterialProperty<Real> & _ElectronTotalFluxMagSizeForm;
  MaterialProperty<Real> & _ElectronTotalFlux;
  MaterialProperty<Real> & _ElectronAdvectiveFlux;
  MaterialProperty<Real> & _ElectronDiffusiveFlux;
  MaterialProperty<Real> & _IonTotalFlux;
  MaterialProperty<Real> & _IonAdvectiveFlux;
  MaterialProperty<Real> & _IonDiffusiveFlux;
  MaterialProperty<Real> & _EField;
  MaterialProperty<Real> & _Source_term;
  MaterialProperty<Real> & _Source_term_coeff;
  MaterialProperty<Real> & _e;
  MaterialProperty<Real> & _eps;
  MaterialProperty<Real> & _Tem_lfa;
  MaterialProperty<Real> & _Tip_lfa;
  MaterialProperty<Real> & _k_boltz;
  MaterialProperty<Real> & _Avogadro;
  MaterialProperty<Real> & _vthermal_em;
  MaterialProperty<Real> & _vthermal_ip;
  MaterialProperty<Real> & _iz_coeff_efield_a;
  MaterialProperty<Real> & _iz_coeff_efield_b;
  MaterialProperty<Real> & _iz_coeff_efield_c;
  MaterialProperty<Real> & _iz_coeff_energy_a;
  MaterialProperty<Real> & _iz_coeff_energy_b;
  MaterialProperty<Real> & _iz_coeff_energy_c;
  MaterialProperty<Real> & _N_A;
  MaterialProperty<Real> & _el_coeff_energy_a;
  MaterialProperty<Real> & _el_coeff_energy_b;
  MaterialProperty<Real> & _el_coeff_energy_c;
  MaterialProperty<Real> & _alpha_iz;
  // MaterialProperty<Real> & _kArIz;
  // MaterialProperty<Real> & _alpha_ArIz;
  MaterialProperty<Real> & _d_iz_d_actual_mean_en;
  MaterialProperty<Real> & _alpha_ex;
  MaterialProperty<Real> & _d_ex_d_actual_mean_en;
  MaterialProperty<Real> & _alpha_el;
  MaterialProperty<Real> & _d_el_d_actual_mean_en;
  // MaterialProperty<Real> & _kArEx;
  MaterialProperty<Real> & _sgnem;
  MaterialProperty<Real> & _sgnmean_en;
  MaterialProperty<Real> & _diffpotential;
  MaterialProperty<Real> & _actual_mean_energy;
  MaterialProperty<Real> & _Tem;
  MaterialProperty<Real> & _diffu;
  MaterialProperty<Real> & _sgnu;
  MaterialProperty<Real> & _T_gas;
  MaterialProperty<Real> & _p_gas;
  MaterialProperty<Real> & _n_gas;
  MaterialProperty<Real> & _kiz;
  MaterialProperty<Real> & _kex;
  MaterialProperty<Real> & _kArp;
  MaterialProperty<Real> & _kel;
  MaterialProperty<Real> & _d_kiz_d_actual_mean_en;
  MaterialProperty<Real> & _d_kex_d_actual_mean_en;
  MaterialProperty<Real> & _d_kel_d_actual_mean_en;
  MaterialProperty<Real> & _TemVolts;

  const VariableValue & _em;
  const VariableValue & _ip;
  const VariableGradient & _grad_em;
  const VariableGradient & _grad_ip;
  const VariableValue & _mean_en;
  const VariableGradient & _grad_potential;
};

#endif // GASBASE_H
