//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CurrentDensityShapeSideUserObject.h"
#include "Zapdos.h"
#include "libmesh/quadrature.h"

registerMooseObject("ZapdosApp", CurrentDensityShapeSideUserObject);

InputParameters
CurrentDensityShapeSideUserObject::validParams()
{
  InputParameters params = ShapeSideUserObject::validParams();
  params.addRequiredCoupledVar("em", "The electron  density.");
  params.deprecateParam("em", "electrons", "04/01/2026");
  params.addRequiredCoupledVar("electrons", "The electron density in log form");
  params.addRequiredCoupledVar("ip", "The ion density density.");
  params.deprecateParam("ip", "ions", "04/01/2026");
  params.addRequiredCoupledVar("ions", "The ion density in log form.");
  params.addRequiredCoupledVar("potential", "The electrical potential.");
  params.addRequiredCoupledVar("mean_en", "The mean energy variable.");
  params.deprecateParam("mean_en", "electron_energy", "04/01/2026");
  params.addRequiredCoupledVar("electron_energy", "The mean electron energy density in log form");
  params.addRequiredParam<bool>("use_moles", "Whether the densities are in molar units.");
  params.addClassDescription("Calculates the total current at a boundary");
  return params;
}

CurrentDensityShapeSideUserObject::CurrentDensityShapeSideUserObject(
    const InputParameters & parameters)
  : ShapeSideUserObject(parameters),
    _em(coupledValue("electrons")),
    _em_id(coupled("electrons")),
    _grad_em(coupledGradient("electrons")),
    _ip_var(*getVar("ions", 0)),
    _ip(coupledValue("ions")),
    _ip_id(coupled("ions")),
    _grad_ip(coupledGradient("ions")),
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _mean_en(coupledValue("electron_energy")),
    _mean_en_id(coupled("electron_energy")),
    _muip(getADMaterialProperty<Real>("mu" + _ip_var.name())),
    _diffip(getADMaterialProperty<Real>("diff" + _ip_var.name())),
    _muem(getADMaterialProperty<Real>("muem")),
    _diffem(getADMaterialProperty<Real>("diffem")),
    _use_moles(getParam<bool>("use_moles"))
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
    RealVectorValue ion_current =
        ZAPDOS_CONSTANTS::e * (_muip[qp].value() * -_grad_potential[qp] * std::exp(_ip[qp]) -
                               _diffip[qp].value() * std::exp(_ip[qp]) * _grad_ip[qp]);
    RealVectorValue electron_current =
        -ZAPDOS_CONSTANTS::e * (-_muem[qp].value() * -_grad_potential[qp] * std::exp(_em[qp]) -
                                _diffem[qp].value() * std::exp(_em[qp]) * _grad_em[qp]);
    Real outgoing_current = _normals[qp] * (ion_current + electron_current);
    if (_use_moles)
      outgoing_current *= ZAPDOS_CONSTANTS::N_A;

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
          ZAPDOS_CONSTANTS::e *
          (_muip[qp].value() * -_grad_potential[qp] * std::exp(_ip[qp]) * _phi[_j][qp] -
           _diffip[qp].value() * (std::exp(_ip[qp]) * _phi[_j][qp] * _grad_ip[qp] +
                                  std::exp(_ip[qp]) * _grad_phi[_j][qp]));
      if (_use_moles)
        d_ion_current_d_ip *= ZAPDOS_CONSTANTS::N_A;
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
      Real d_muem_d_em = _muem[qp].derivatives()[jvar] * d_actual_mean_en_d_em;
      Real d_diffem_d_em = _diffem[qp].derivatives()[jvar] * d_actual_mean_en_d_em;

      RealVectorValue d_electron_current_d_em =
          -ZAPDOS_CONSTANTS::e *
          (-_muem[qp].value() * -_grad_potential[qp] * std::exp(_em[qp]) * _phi[_j][qp] -
           d_muem_d_em * -_grad_potential[qp] * std::exp(_em[qp]) -
           _diffem[qp].value() * (std::exp(_em[qp]) * _phi[_j][qp] * _grad_em[qp] +
                                  std::exp(_em[qp]) * _grad_phi[_j][qp]) -
           d_diffem_d_em * std::exp(_em[qp]) * _grad_em[qp]);
      if (_use_moles)
        d_electron_current_d_em *= ZAPDOS_CONSTANTS::N_A;
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
          ZAPDOS_CONSTANTS::e * (_muip[qp].value() * -_grad_phi[_j][qp] * std::exp(_ip[qp]));
      RealVectorValue d_electron_current_d_potential =
          -ZAPDOS_CONSTANTS::e * (-_muem[qp].value() * -_grad_phi[_j][qp] * std::exp(_em[qp]));
      Real d_outgoing_current_d_potential =
          _normals[qp] * (d_ion_current_d_potential + d_electron_current_d_potential);
      if (_use_moles)
        d_outgoing_current_d_potential *= ZAPDOS_CONSTANTS::N_A;
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
      Real d_muem_d_mean_en = _muem[qp].derivatives()[jvar] * d_actual_mean_en_d_mean_en;
      Real d_diffem_d_mean_en = _diffem[qp].derivatives()[jvar] * d_actual_mean_en_d_mean_en;

      RealVectorValue d_electron_current_d_mean_en =
          -ZAPDOS_CONSTANTS::e * (-d_muem_d_mean_en * -_grad_potential[qp] * std::exp(_em[qp]) -
                                  d_diffem_d_mean_en * std::exp(_em[qp]) * _grad_em[qp]);
      if (_use_moles)
        d_electron_current_d_mean_en *= ZAPDOS_CONSTANTS::N_A;
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
