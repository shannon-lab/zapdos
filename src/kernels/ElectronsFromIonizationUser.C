#include "ElectronsFromIonizationUser.h"

registerMooseObject("ZapdosApp", ElectronsFromIonizationUser);

template <>
InputParameters
validParams<ElectronsFromIonizationUser>()
{
  InputParameters params = validParams<ElectronsFromIonization>();
  params.addRequiredParam<Real>("muem", "The mobility.");
  params.addRequiredParam<Real>("diffem", "The diffusivity.");
  params.addRequiredParam<Real>("alpha_iz", "The Townsend ionization coefficient.");
  return params;
}

ElectronsFromIonizationUser::ElectronsFromIonizationUser(const InputParameters & parameters)
  : ElectronsFromIonization(parameters)
{
  _diffem.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("diffem")));
  _muem.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("muem")));
  _alpha_iz.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("alpha_iz")));
  _d_diffem_d_actual_mean_en.resize(_fe_problem.getMaxQps(), Real(0));
  _d_muem_d_actual_mean_en.resize(_fe_problem.getMaxQps(), Real(0));
  _d_iz_d_actual_mean_en.resize(_fe_problem.getMaxQps(), Real(0));
}
