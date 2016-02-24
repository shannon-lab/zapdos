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
#ifndef JACMAT_H_
#define JACMAT_H_

#include "Material.h"
#include "SplineInterpolation.h"

class JacMat;

template<>
InputParameters validParams<JacMat>();

class JacMat : public Material
{
public:
  JacMat(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  MaterialProperty<Real> & _muu;
  MaterialProperty<Real> & _muv;
  MaterialProperty<Real> & _sgnu;
  MaterialProperty<Real> & _sgnem;
  MaterialProperty<Real> & _sgnmean_en;
  MaterialProperty<Real> & _sgnv;
  MaterialProperty<Real> & _diffu;
  MaterialProperty<Real> & _diffem;
  MaterialProperty<Real> & _diffmean_en;
  MaterialProperty<Real> & _muem;
  MaterialProperty<Real> & _mumean_en;
  MaterialProperty<Real> & _diffpotential;
  MaterialProperty<Real> & _iz_coeff_efield_a;
  MaterialProperty<Real> & _iz_coeff_efield_b;
  MaterialProperty<Real> & _iz_coeff_efield_c;
  MaterialProperty<Real> & _ku;
  MaterialProperty<Real> & _kuu;
  MaterialProperty<Real> & _N_A;
  MaterialProperty<Real> & _e;
  MaterialProperty<Real> & _kv;
  MaterialProperty<Real> & _kvv;
  MaterialProperty<Real> & _diffu1;
  MaterialProperty<Real> & _diffu2;
  MaterialProperty<Real> & _se_coeff;
  MaterialProperty<Real> & _se_energy;
  MaterialProperty<Real> & _eps;
  MaterialProperty<Real> & _mem;
  MaterialProperty<Real> & _d_interp;
  MaterialProperty<Real> & _d_d_interp_d_v;
  MaterialProperty<Real> &  _d_muem_d_actual_mean_en;
  MaterialProperty<Real> &  _d_mumean_en_d_actual_mean_en;
  MaterialProperty<Real> &  _d_diffem_d_actual_mean_en;
  MaterialProperty<Real> &  _d_diffmean_en_d_actual_mean_en;
  MaterialProperty<Real> &  _alpha_iz;
  MaterialProperty<Real> &  _d_iz_d_actual_mean_en;
  MaterialProperty<Real> &  _alpha_ex;
  MaterialProperty<Real> &  _d_ex_d_actual_mean_en;
  MaterialProperty<Real> &  _alpha_el;
  MaterialProperty<Real> &  _d_el_d_actual_mean_en;
  MaterialProperty<Real> &  _Eiz;
  MaterialProperty<Real> &  _Eex;
  MaterialProperty<Real> &  _mGas;
  MaterialProperty<Real> &  _k_boltz;
  MaterialProperty<Real> &  _T_heavy;
  MaterialProperty<Real> &  _massu;
  MaterialProperty<Real> &  _massArp;
  MaterialProperty<Real> &  _sgnp;
  MaterialProperty<Real> &  _mup;
  MaterialProperty<Real> &  _muw;
  MaterialProperty<Real> &  _diffp;
  MaterialProperty<Real> &  _muArp;
  MaterialProperty<Real> &  _diffArp;
  MaterialProperty<Real> &  _sgnArp;
  MaterialProperty<Real> &  _actual_mean_en;
  MaterialProperty<Real> &  _muOHm;
  MaterialProperty<Real> &  _diffOHm;
  MaterialProperty<Real> &  _sgnOHm;
  MaterialProperty<Real> &  _muemliq;
  MaterialProperty<Real> &  _diffemliq;
  MaterialProperty<Real> &  _sgnemliq;
  MaterialProperty<Real> &  _kemliqemliq;
  MaterialProperty<Real> &  _kemliq;

  const VariableValue & _v;
  const VariableValue & _mean_en;
  const VariableValue & _em;
  const VariableValue & _emliq;

  SplineInterpolation _interpolation;
  SplineInterpolation  _alpha_interpolation;
  SplineInterpolation  _alphaEx_interpolation;
  SplineInterpolation  _alphaEl_interpolation;
  SplineInterpolation  _mu_interpolation;
  SplineInterpolation  _diff_interpolation;

};

#endif //JACMAT_H
