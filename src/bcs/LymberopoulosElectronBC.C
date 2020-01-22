//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "LymberopoulosElectronBC.h"

registerMooseObject("ZapdosApp", LymberopoulosElectronBC);

template <>
InputParameters
validParams<LymberopoulosElectronBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("ks", "The recombination coefficient");
  params.addRequiredParam<Real>("gamma", "The secondary electron coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("ion", "The ion density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Simpified kinetic electron boundary condition"
                             "(Based on DOI: https://doi.org/10.1063/1.352926)");
  return params;
}

LymberopoulosElectronBC::LymberopoulosElectronBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _ks(getParam<Real>("ks")),
    _gamma(getParam<Real>("gamma")),

    // Coupled Variables
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _Arp(coupledValue("ion")),
    _grad_Arp(coupledGradient("ion")),
    _Arp_id(coupled("ion")),

    _muion(getMaterialProperty<Real>("mu" + (*getVar("ion", 0)).name())),
    _diffion(getMaterialProperty<Real>("diff" + (*getVar("ion", 0)).name())),

    _sign(1)
{
}

Real
LymberopoulosElectronBC::computeQpResidual()
{

  RealVectorValue _ion_flux =
      (_muion[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_Arp[_qp]));

  // RealVectorValue _ion_flux = (_muion[_qp] * -_grad_potential[_qp] * _r_units *
  // std::exp(_Arp[_qp]) -
  //            _diffion[_qp] * std::exp(_Arp[_qp]) * _grad_Arp[_qp] * _r_units);

  return _test[_i][_qp] * _r_units *
         (_sign * _ks * std::exp(_u[_qp]) * _normals[_qp] * _normals[_qp] -
          _gamma * _ion_flux * _normals[_qp]);
}

Real
LymberopoulosElectronBC::computeQpJacobian()
{

  RealVectorValue _ion_flux =
      (_muion[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_Arp[_qp]));

  // RealVectorValue _ion_flux = (_muion[_qp] * -_grad_potential[_qp] * _r_units *
  // std::exp(_Arp[_qp]) -
  //            _diffion[_qp] * std::exp(_Arp[_qp]) * _grad_Arp[_qp] * _r_units);

  return _test[_i][_qp] * _r_units *
         (_sign * _ks * std::exp(_u[_qp]) * _phi[_j][_qp] * _normals[_qp] * _normals[_qp]);
}

// need to fix
Real
LymberopoulosElectronBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {

    RealVectorValue _d_ion_flux_d_V =
        (_muion[_qp] * -_grad_phi[_j][_qp] * _r_units * std::exp(_Arp[_qp]));

    // RealVectorValue _d_ion_flux_d_V = (_muion[_qp] * -_grad_phi[_j][_qp] * _r_units *
    // std::exp(_Arp[_qp]) -
    //            _diffion[_qp] * std::exp(_Arp[_qp]) * _grad_Arp[_qp] * _r_units);

    return _test[_i][_qp] * _r_units * ((-_gamma * _d_ion_flux_d_V * _normals[_qp]));
  }

  else if (jvar == _Arp_id)
  {

    RealVectorValue _d_ion_flux_d_ion =
        (_muion[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_Arp[_qp]) * _phi[_j][_qp]);

    // RealVectorValue _d_ion_flux_d_ion = (_muion[_qp] * -_grad_potential[_qp] * _r_units *
    // std::exp(_Arp[_qp]) * _phi[_j][_qp] -
    //                      _diffion[_qp] * (std::exp(_Arp[_qp]) * _grad_phi[_j][_qp] * _r_units +
    //                      std::exp(_Arp[_qp]) * _phi[_j][_qp] * _grad_Arp[_qp] * _r_units));

    return _test[_i][_qp] * _r_units * ((-_gamma * _d_ion_flux_d_ion * _normals[_qp]));
  }

  else
    return 0.0;
}
