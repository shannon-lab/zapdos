#include "ElectronEnergyTermTownsend.h"

registerMooseObject("CraneApp", ElectronEnergyTermTownsend);

template <>
InputParameters
validParams<ElectronEnergyTermTownsend>()
{
  InputParameters params = validParams<Kernel>();
  params.addCoupledVar("potential", "The potential.");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addParam<bool>("elastic_collision", false, "If the collision is elastic.");
  params.addRequiredParam<std::string>("reaction", "The reaction that is adding/removing energy.");
  params.addParam<Real>("threshold_energy", 0.0, "Energy required for reaction to take place.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addCoupledVar("target",
                       "The coupled target. If none, assumed to be background gas from BOLSIG+.");
  return params;
}

ElectronEnergyTermTownsend::ElectronEnergyTermTownsend(const InputParameters & parameters)
  : Kernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _elastic(getParam<bool>("elastic_collision")),
    _threshold_energy(getParam<Real>("threshold_energy")),
    _elastic_energy(
        getMaterialProperty<Real>("energy_elastic_" + getParam<std::string>("reaction"))),
    _diffem(getMaterialProperty<Real>("diffem")),
    _muem(getMaterialProperty<Real>("muem")),
    _alpha(getMaterialProperty<Real>("alpha_" + getParam<std::string>("reaction"))),
    // _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_alpha_d_en_em + Ar = em + em + Arp")),
    _d_iz_d_actual_mean_en(
        getMaterialProperty<Real>("d_alpha_d_en_" + getParam<std::string>("reaction"))),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en")),
    _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _grad_zero),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em")),
    _potential_id(coupled("potential")),
    _em_id(coupled("em")),
    _target(isCoupled("target") ? coupledValue("target") : _zero),
    _target_id(isCoupled("target") ? coupled("target") : 12345678)
{
  if (!_elastic && !isParamValid("threshold_energy"))
    mooseError("ElectronEnergyTermTownsend: Elastic collision set to false, but no threshold "
               "energy for this reaction is provided!");
  // else if (_elastic)
  // _energy_change = _elastic_energy[_qp];
  // else
  _energy_change = _threshold_energy;
}

ElectronEnergyTermTownsend::~ElectronEnergyTermTownsend() {}

Real
ElectronEnergyTermTownsend::computeQpResidual()
{
  Real electron_flux_mag = (-_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
                            _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units)
                               .norm();
  Real iz_term = _alpha[_qp] * electron_flux_mag;

  return -_test[_i][_qp] * iz_term * _threshold_energy;
}

Real
ElectronEnergyTermTownsend::computeQpJacobian()
{
  Real d_actual_mean_en_d_mean_en = std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];
  Real d_iz_d_mean_en = _d_iz_d_actual_mean_en[_qp] * d_actual_mean_en_d_mean_en;
  Real d_muem_d_mean_en = _d_muem_d_actual_mean_en[_qp] * d_actual_mean_en_d_mean_en;
  Real d_diffem_d_mean_en = _d_diffem_d_actual_mean_en[_qp] * d_actual_mean_en_d_mean_en;

  RealVectorValue electron_flux =
      -_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
      _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units;
  RealVectorValue d_electron_flux_d_mean_en =
      -d_muem_d_mean_en * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
      d_diffem_d_mean_en * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units;
  Real electron_flux_mag = electron_flux.norm();
  Real d_electron_flux_mag_d_mean_en = electron_flux * d_electron_flux_d_mean_en /
                                       (electron_flux_mag + std::numeric_limits<double>::epsilon());
  Real d_iz_term_d_mean_en =
      (electron_flux_mag * d_iz_d_mean_en + _alpha[_qp] * d_electron_flux_mag_d_mean_en);

  return -_test[_i][_qp] * d_iz_term_d_mean_en * _threshold_energy;
}

Real
ElectronEnergyTermTownsend::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real d_actual_mean_en_d_em = -std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];
  Real d_iz_d_em = _d_iz_d_actual_mean_en[_qp] * d_actual_mean_en_d_em;
  Real d_muem_d_em = _d_muem_d_actual_mean_en[_qp] * d_actual_mean_en_d_em;
  Real d_diffem_d_em = _d_diffem_d_actual_mean_en[_qp] * d_actual_mean_en_d_em;

  RealVectorValue electron_flux =
      -_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
      _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units;
  RealVectorValue d_electron_flux_d_potential =
      -_muem[_qp] * -_grad_phi[_j][_qp] * _r_units * std::exp(_em[_qp]);
  RealVectorValue d_electron_flux_d_em =
      -d_muem_d_em * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
      _muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) * _phi[_j][_qp] -
      d_diffem_d_em * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units -
      _diffem[_qp] * std::exp(_em[_qp]) * _phi[_j][_qp] * _grad_em[_qp] * _r_units -
      _diffem[_qp] * std::exp(_em[_qp]) * _grad_phi[_j][_qp] * _r_units;
  Real electron_flux_mag = electron_flux.norm();
  Real d_electron_flux_mag_d_potential =
      electron_flux * d_electron_flux_d_potential /
      (electron_flux_mag + std::numeric_limits<double>::epsilon());
  Real d_electron_flux_mag_d_em = electron_flux * d_electron_flux_d_em /
                                  (electron_flux_mag + std::numeric_limits<double>::epsilon());

  Real d_iz_term_d_potential = (_alpha[_qp] * d_electron_flux_mag_d_potential);
  Real d_iz_term_d_em = (electron_flux_mag * d_iz_d_em + _alpha[_qp] * d_electron_flux_mag_d_em);

  if (jvar == _potential_id)
    return -_test[_i][_qp] * d_iz_term_d_potential * _threshold_energy;

  else if (jvar == _em_id)
  {
    return -_test[_i][_qp] * d_iz_term_d_em * _threshold_energy;
  }
  else if (jvar == _target_id)
  {
    return -_test[_i][_qp] * _alpha[_qp] * electron_flux.norm() * _phi[_j][_qp] * _threshold_energy;
  }

  else
    return 0.0;
}
