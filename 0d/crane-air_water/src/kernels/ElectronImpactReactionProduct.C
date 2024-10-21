#include "ElectronImpactReactionProduct.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ElectronImpactReactionProduct);

template <>
InputParameters
validParams<ElectronImpactReactionProduct>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("mean_en", "The electron mean energy.");
  params.addRequiredCoupledVar("potential", "The potential.");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addCoupledVar("target", "The coupled target. If none, assumed to be background gas from BOLSIG+.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<std::string>("reaction", "Stores the full reaction equation.");
  params.addRequiredParam<std::string>("reaction_coefficient_name",
                                       "Stores the name of the reaction rate/townsend coefficient, "
                                       "unique to each individual reaction.");
  return params;
}

ElectronImpactReactionProduct::ElectronImpactReactionProduct(const InputParameters & parameters)
  : Kernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _reaction_coeff_name(getParam<std::string>("reaction_coefficient_name")),
    _reaction_name(getParam<std::string>("reaction")),
    _diffem(getMaterialProperty<Real>("diffem")),
    _muem(getMaterialProperty<Real>("muem")),
    // _alpha(getMaterialProperty<Real>("alpha_iz")),
    _alpha(getMaterialProperty<Real>(_reaction_coeff_name)),
    // _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_iz_d_actual_mean_en")),
    _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_alpha_d_en_" + _reaction_name)),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en")),
    _mean_en(coupledValue("mean_en")),
    _grad_potential(coupledGradient("potential")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em")),
    _mean_en_id(coupled("mean_en")),
    _potential_id(coupled("potential")),
    _em_id(coupled("em")),
    _target(isCoupled("target") ? coupledValue("target") : _zero),
    _target_id(isCoupled("target") ? coupled("target") : 12345678) 
{
}

ElectronImpactReactionProduct::~ElectronImpactReactionProduct() {}

Real
ElectronImpactReactionProduct::computeQpResidual()
{
  Real electron_flux_mag = (-_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
                            _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units)
                               .norm();

  // std::cout << _alpha_sink[_qp] << std::endl;
  // std::cout << _alpha_source[_qp] << "\n" << std::endl;

  // if (_reactant)
  //   Real alpha = _alpha_sink[_qp];
  // else
  //   Real alpha = _alpha_source[_qp];

  // Real iz_term = _alpha_iz[_qp] * electron_flux_mag;
  // Real iz_term = alpha * electron_flux_mag;

  // return -_test[_i][_qp] * iz_term;
 
  return -_test[_i][_qp] * _alpha[_qp] * electron_flux_mag;
}

Real
ElectronImpactReactionProduct::computeQpJacobian()
{
  if (_var.number() == _em_id)
  {
    Real actual_mean_en = std::exp(_mean_en[_qp] - _em[_qp]);

    Real d_iz_d_em = _d_iz_d_actual_mean_en[_qp] * actual_mean_en * -_phi[_j][_qp];
    Real d_muem_d_em = _d_muem_d_actual_mean_en[_qp] * actual_mean_en * -_phi[_j][_qp];
    Real d_diffem_d_em = _d_diffem_d_actual_mean_en[_qp] * actual_mean_en * -_phi[_j][_qp];

    RealVectorValue electron_flux =
        -_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
        _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units;
    RealVectorValue d_electron_flux_d_em =
        -d_muem_d_em * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
        _muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) * _phi[_j][_qp] -
        d_diffem_d_em * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units -
        _diffem[_qp] * std::exp(_em[_qp]) * _phi[_j][_qp] * _grad_em[_qp] * _r_units -
        _diffem[_qp] * std::exp(_em[_qp]) * _grad_phi[_j][_qp] * _r_units;
    Real electron_flux_mag = electron_flux.norm();
    Real d_electron_flux_mag_d_em = electron_flux * d_electron_flux_d_em /
                                    (electron_flux_mag + std::numeric_limits<double>::epsilon());

    Real d_iz_term_d_em = (electron_flux_mag * d_iz_d_em + _alpha[_qp] * d_electron_flux_mag_d_em);

    return -_test[_i][_qp] * d_iz_term_d_em;
  }
  else
    return 0;
}

Real
ElectronImpactReactionProduct::computeQpOffDiagJacobian(unsigned int jvar)
{
  // Define multiplication factor (determining if product or reactant)

  Real actual_mean_en = std::exp(_mean_en[_qp] - _em[_qp]);

  Real d_iz_d_mean_en = _d_iz_d_actual_mean_en[_qp] * actual_mean_en * _phi[_j][_qp];
  Real d_iz_d_em = _d_iz_d_actual_mean_en[_qp] * actual_mean_en * -_phi[_j][_qp];
  Real d_muem_d_mean_en = _d_muem_d_actual_mean_en[_qp] * actual_mean_en * _phi[_j][_qp];
  Real d_muem_d_em = _d_muem_d_actual_mean_en[_qp] * actual_mean_en * -_phi[_j][_qp];
  Real d_diffem_d_mean_en = _d_diffem_d_actual_mean_en[_qp] * actual_mean_en * _phi[_j][_qp];
  Real d_diffem_d_em = _d_diffem_d_actual_mean_en[_qp] * actual_mean_en * -_phi[_j][_qp];

  RealVectorValue electron_flux =
      -_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
      _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units;
  RealVectorValue d_electron_flux_d_potential =
      -_muem[_qp] * -_grad_phi[_j][_qp] * _r_units * std::exp(_em[_qp]);
  RealVectorValue d_electron_flux_d_mean_en =
      -d_muem_d_mean_en * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
      d_diffem_d_mean_en * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units;
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
  Real d_electron_flux_mag_d_mean_en = electron_flux * d_electron_flux_d_mean_en /
                                       (electron_flux_mag + std::numeric_limits<double>::epsilon());
  Real d_electron_flux_mag_d_em = electron_flux * d_electron_flux_d_em /
                                  (electron_flux_mag + std::numeric_limits<double>::epsilon());

  // Real d_iz_term_d_potential = (_alpha_iz[_qp] * d_electron_flux_mag_d_potential);
  // Real d_iz_term_d_mean_en =
  //     (electron_flux_mag * d_iz_d_mean_en + _alpha_iz[_qp] * d_electron_flux_mag_d_mean_en);
  // Real d_iz_term_d_em = (electron_flux_mag * d_iz_d_em + _alpha_iz[_qp] *
  // d_electron_flux_mag_d_em);

  Real d_iz_term_d_potential = (_alpha[_qp] * d_electron_flux_mag_d_potential);
  Real d_iz_term_d_mean_en =
      (electron_flux_mag * d_iz_d_mean_en + _alpha[_qp] * d_electron_flux_mag_d_mean_en);
  Real d_iz_term_d_em = (electron_flux_mag * d_iz_d_em + _alpha[_qp] * d_electron_flux_mag_d_em);

  if (jvar == _potential_id)
    return -_test[_i][_qp] * d_iz_term_d_potential;

  else if (jvar == _mean_en_id)
    return -_test[_i][_qp] * d_iz_term_d_mean_en;

  else if (jvar == _em_id)
    return -_test[_i][_qp] * d_iz_term_d_em;
  else if (jvar == _target_id)
    return -_test[_i][_qp] * _alpha[_qp] * electron_flux_mag * _phi[_j][_qp]; 

  else
    return 0.0;

  // if (jvar == _potential_id)
  //   return -_test[_i][_qp] * d_iz_term_d_potential;
  //
  // else if (jvar == _mean_en_id)
  //   return -_test[_i][_qp] * d_iz_term_d_mean_en;
  //
  // else if (jvar == _em_id)
  //   return -_test[_i][_qp] * d_iz_term_d_em;
  //
  // else
  //   return 0.0;
}
