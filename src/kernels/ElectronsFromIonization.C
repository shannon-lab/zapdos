#include "ElectronsFromIonization.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", ElectronsFromIonization);

template <>
InputParameters
validParams<ElectronsFromIonization>()
{
  InputParameters params = validParams<Kernel>();
  params.addCoupledVar("mean_en", 3, "The electron mean energy.");
  params.addCoupledVar("potential", "The potential.");
  params.addRequiredCoupledVar("em", "The electron density in logarithmic form.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<Real>("EField",
                        "Optionally can use a specified electric field for 1D "
                        "simulations in place of a potential variable");
  params.addParam<bool>("use_material_props", true, "Whether to use a material for properties.");
  params.addParam<Real>("muem", "The mobility.");
  params.addParam<Real>("diffem", "The diffusivity.");
  params.addParam<Real>("alpha_iz", "The Townsend ionization coefficient.");
  return params;
}

ElectronsFromIonization::ElectronsFromIonization(const InputParameters & parameters)
  : Kernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffem(getParam<bool>("use_material_props") ? getMaterialProperty<Real>("diffem")
                                                 : _user_diffem),
    _d_diffem_d_actual_mean_en(getParam<bool>("use_material_props")
                                   ? getMaterialProperty<Real>("d_diffem_d_actual_mean_en")
                                   : _user_d_diffem_d_actual_mean_en),
    _muem(getParam<bool>("use_material_props") ? getMaterialProperty<Real>("muem") : _user_muem),
    _d_muem_d_actual_mean_en(getParam<bool>("use_material_props")
                                 ? getMaterialProperty<Real>("d_muem_d_actual_mean_en")
                                 : _user_d_muem_d_actual_mean_en),
    _alpha_iz(getParam<bool>("use_material_props") ? getMaterialProperty<Real>("alpha_iz")
                                                   : _user_alpha_iz),
    _d_iz_d_actual_mean_en(getParam<bool>("use_material_props")
                               ? getMaterialProperty<Real>("d_iz_d_actual_mean_en")
                               : _user_d_iz_d_actual_mean_en),

    _mean_en(coupledValue("mean_en")),
    _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _minus_e_field),
    _mean_en_id(coupled("mean_en")),
    _potential_id(coupled("potential")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em")),
    _em_id(coupled("em"))
{
  if (!(isCoupled("potential") || parameters.isParamSetByUser("EField")))
    mooseError("You must either couple in a potential variable or set an EField.");

  if (!(isCoupled("potential")))
    _minus_e_field.resize(_fe_problem.getMaxQps(), RealGradient(-getParam<Real>("EField")));
  if (!(getParam<bool>("use_material_props")))
  {
    auto max_qps = _fe_problem.getMaxQps();
    _user_diffem.resize(max_qps);
    _user_d_diffem_d_actual_mean_en.resize(max_qps);
    _user_muem.resize(max_qps);
    _user_d_muem_d_actual_mean_en.resize(max_qps);
    _user_alpha_iz.resize(max_qps);
    _user_d_iz_d_actual_mean_en.resize(max_qps);
    for (decltype(max_qps) qp = 0; qp < max_qps; ++qp)
    {
      _user_diffem[qp] = getParam<Real>("diffem");
      _user_d_diffem_d_actual_mean_en[qp] = 0;
      _user_muem[qp] = getParam<Real>("muem");
      _user_d_muem_d_actual_mean_en[qp] = 0;
      _user_alpha_iz[qp] = getParam<Real>("alpha_iz");
      _user_d_iz_d_actual_mean_en[qp] = 0;
    }
  }
}

ElectronsFromIonization::~ElectronsFromIonization() {}

// When modifying electron or potential units, nothing should be needed to be done here provided
// that material properties are properly done.
Real
ElectronsFromIonization::computeQpResidual()
{
  Real electron_flux_mag = (-_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
                            _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units)
                               .norm();
  Real iz_term = _alpha_iz[_qp] * electron_flux_mag;

  return -_test[_i][_qp] * iz_term;
}

Real
ElectronsFromIonization::computeQpJacobian()
{
  if (_var.number() == _em_id)
  {
    Real actual_mean_en = std::exp(_mean_en[_qp] - _em[_qp]);
    Real d_actual_mean_en_d_em = -std::exp(_mean_en[_qp] - _em[_qp]) * _phi[_j][_qp];

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

    Real d_iz_term_d_em =
        (electron_flux_mag * d_iz_d_em + _alpha_iz[_qp] * d_electron_flux_mag_d_em);

    return -_test[_i][_qp] * d_iz_term_d_em;
  }
  else
    return 0;
}

Real
ElectronsFromIonization::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real actual_mean_en = std::exp(_mean_en[_qp] - _em[_qp]);
  Real d_actual_mean_en_d_mean_en = std::exp(_mean_en[_qp] - _em[_qp]) * _phi[_j][_qp];
  Real d_actual_mean_en_d_em = -std::exp(_mean_en[_qp] - _em[_qp]) * _phi[_j][_qp];

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

  Real d_iz_term_d_potential = (_alpha_iz[_qp] * d_electron_flux_mag_d_potential);
  Real d_iz_term_d_mean_en =
      (electron_flux_mag * d_iz_d_mean_en + _alpha_iz[_qp] * d_electron_flux_mag_d_mean_en);
  Real d_iz_term_d_em = (electron_flux_mag * d_iz_d_em + _alpha_iz[_qp] * d_electron_flux_mag_d_em);

  if (jvar == _potential_id)
    return -_test[_i][_qp] * d_iz_term_d_potential;

  else if (jvar == _mean_en_id)
    return -_test[_i][_qp] * d_iz_term_d_mean_en;

  else if (jvar == _em_id)
    return -_test[_i][_qp] * d_iz_term_d_em;

  else
    return 0.0;
}
