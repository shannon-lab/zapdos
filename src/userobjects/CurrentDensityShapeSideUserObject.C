#include "CurrentDensityShapeSideUserObject.h"
#include "libmesh/quadrature.h"

registerMooseObject("ZapdosApp", CurrentDensityShapeSideUserObject);

template <>
InputParameters
validParams<CurrentDensityShapeSideUserObject>()
{
  InputParameters params = validParams<ShapeSideUserObject>();
  params.addRequiredCoupledVar("em", "The electron  density.");
  params.addRequiredCoupledVar("ip", "The ion density density.");
  params.addRequiredCoupledVar("potential", "The electrical potential.");
  params.addRequiredCoupledVar("mean_en", "The mean energy variable.");
  params.addRequiredParam<bool>("use_moles", "Whether the densities are in molar units.");
  return params;
}

CurrentDensityShapeSideUserObject::CurrentDensityShapeSideUserObject(
    const InputParameters & parameters)
  : ShapeSideUserObject(parameters),
    _em(coupledValue("em")),
    _em_id(coupled("em")),
    _grad_em(coupledGradient("em")),
    _ip_var(*getVar("ip", 0)),
    _ip(coupledValue("ip")),
    _ip_id(coupled("ip")),
    _grad_ip(coupledGradient("ip")),
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),
    _muip(getMaterialProperty<Real>("mu" + _ip_var.name())),
    _diffip(getMaterialProperty<Real>("diff" + _ip_var.name())),
    _muem(getMaterialProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _diffem(getMaterialProperty<Real>("diffem")),
    _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en")),
    _e(1.6e-19),
    _use_moles(getParam<bool>("use_moles")),
    _avogadro(6.02e23)
{
}

void
CurrentDensityShapeSideUserObject::initialize()
{
  _integral = 0.0;

  // Jacobian term storage is up to the user. One option is using an std::vector
  // We resize it to the total number of DOFs in the system and zero it out.
  // WARNING: this can be large number (smart sparse storage could be a future improvement)
  if (_fe_problem.currentlyComputingJacobian())
    _jacobian_storage.assign(_subproblem.es().n_dofs(), 0.0);
}

void
CurrentDensityShapeSideUserObject::execute()
{
  for (unsigned int qp = 0; qp < _qrule->n_points(); ++qp)
  {
    RealVectorValue ion_current = _e * (_muip[qp] * -_grad_potential[qp] * std::exp(_ip[qp]) -
                                        _diffip[qp] * std::exp(_ip[qp]) * _grad_ip[qp]);
    RealVectorValue electron_current =
        -_e * (-_muem[qp] * -_grad_potential[qp] * std::exp(_em[qp]) -
               _diffem[qp] * std::exp(_em[qp]) * _grad_em[qp]);
    Real outgoing_current = _normals[qp] * (ion_current + electron_current);
    if (_use_moles)
      outgoing_current *= _avogadro;

    _integral += _JxW[qp] * _coord[qp] * outgoing_current;
  }
}

void
CurrentDensityShapeSideUserObject::executeJacobian(unsigned int jvar)
{
  // derivative of _integral w.r.t. ip_j
  if (jvar == _ip_id)
  {
    Real sum = 0.0;
    for (unsigned int qp = 0; qp < _qrule->n_points(); ++qp)
    {
      RealVectorValue d_ion_current_d_ip =
          _e * (_muip[qp] * -_grad_potential[qp] * std::exp(_ip[qp]) * _phi[_j][qp] -
                _diffip[qp] * (std::exp(_ip[qp]) * _phi[_j][qp] * _grad_ip[qp] +
                               std::exp(_ip[qp]) * _grad_phi[_j][qp]));
      if (_use_moles)
        d_ion_current_d_ip *= _avogadro;
      sum += _JxW[qp] * _coord[qp] * _normals[qp] * d_ion_current_d_ip;
    }

    _jacobian_storage[_j_global] += sum;
  }

  // derivative of _integral w.r.t. em_j
  else if (jvar == _em_id)
  {
    Real sum = 0.0;
    for (unsigned int qp = 0; qp < _qrule->n_points(); ++qp)
    {
      Real d_actual_mean_en_d_em = std::exp(_mean_en[qp] - _em[qp]) * -_phi[_j][qp];
      Real d_muem_d_em = _d_muem_d_actual_mean_en[qp] * d_actual_mean_en_d_em;
      Real d_diffem_d_em = _d_diffem_d_actual_mean_en[qp] * d_actual_mean_en_d_em;

      RealVectorValue d_electron_current_d_em =
          -_e * (-_muem[qp] * -_grad_potential[qp] * std::exp(_em[qp]) * _phi[_j][qp] -
                 d_muem_d_em * -_grad_potential[qp] * std::exp(_em[qp]) -
                 _diffem[qp] * (std::exp(_em[qp]) * _phi[_j][qp] * _grad_em[qp] +
                                std::exp(_em[qp]) * _grad_phi[_j][qp]) -
                 d_diffem_d_em * std::exp(_em[qp]) * _grad_em[qp]);
      if (_use_moles)
        d_electron_current_d_em *= _avogadro;
      sum += _JxW[qp] * _coord[qp] * _normals[qp] * d_electron_current_d_em;
    }

    _jacobian_storage[_j_global] += sum;
  }

  // derivative of _integral w.r.t. potential_j
  else if (jvar == _potential_id)
  {
    Real sum = 0.0;
    for (unsigned int qp = 0; qp < _qrule->n_points(); ++qp)
    {
      RealVectorValue d_ion_current_d_potential =
          _e * (_muip[qp] * -_grad_phi[_j][qp] * std::exp(_ip[qp]));
      RealVectorValue d_electron_current_d_potential =
          -_e * (-_muem[qp] * -_grad_phi[_j][qp] * std::exp(_em[qp]));
      Real d_outgoing_current_d_potential =
          _normals[qp] * (d_ion_current_d_potential + d_electron_current_d_potential);
      if (_use_moles)
        d_outgoing_current_d_potential *= _avogadro;
      sum += _JxW[qp] * _coord[qp] * d_outgoing_current_d_potential;
    }

    _jacobian_storage[_j_global] += sum;
  }

  // derivative of _integral w.r.t. mean_en_j
  else if (jvar == _mean_en_id)
  {
    Real sum = 0.0;
    for (unsigned int qp = 0; qp < _qrule->n_points(); ++qp)
    {
      Real d_actual_mean_en_d_mean_en = std::exp(_mean_en[qp] - _em[qp]) * _phi[_j][qp];
      Real d_muem_d_mean_en = _d_muem_d_actual_mean_en[qp] * d_actual_mean_en_d_mean_en;
      Real d_diffem_d_mean_en = _d_diffem_d_actual_mean_en[qp] * d_actual_mean_en_d_mean_en;

      RealVectorValue d_electron_current_d_mean_en =
          -_e * (-d_muem_d_mean_en * -_grad_potential[qp] * std::exp(_em[qp]) -
                 d_diffem_d_mean_en * std::exp(_em[qp]) * _grad_em[qp]);
      if (_use_moles)
        d_electron_current_d_mean_en *= _avogadro;
      sum += _JxW[qp] * _coord[qp] * _normals[qp] * d_electron_current_d_mean_en;
    }

    _jacobian_storage[_j_global] += sum;
  }
}

void
CurrentDensityShapeSideUserObject::finalize()
{
  gatherSum(_integral);

  if (_fe_problem.currentlyComputingJacobian())
    gatherSum(_jacobian_storage);
}

void
CurrentDensityShapeSideUserObject::threadJoin(const UserObject & y)
{
  const CurrentDensityShapeSideUserObject & shp_uo =
      dynamic_cast<const CurrentDensityShapeSideUserObject &>(y);
  _integral += shp_uo._integral;

  if (_fe_problem.currentlyComputingJacobian())
  {
    mooseAssert(_jacobian_storage.size() == shp_uo._jacobian_storage.size(),
                "Jacobian storage size is inconsistent across threads");
    for (unsigned int i = 0; i < _jacobian_storage.size(); ++i)
      _jacobian_storage[i] += shp_uo._jacobian_storage[i];
  }
}
