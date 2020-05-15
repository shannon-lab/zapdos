//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "InterfacePotential.h"

registerMooseObject("ZapdosApp", InterfacePotential);

InputParameters
InterfacePotential::validParams()
{
  InputParameters params = InterfaceKernel::validParams();
  params.addParam<MaterialPropertyName>("diff", "D", "The diffusion coefficient.");
  params.addParam<MaterialPropertyName>(
      "D_neighbor", "D_neighbor", "The neighboring diffusion coefficient.");
  // params.addRequiredCoupledVar("sigma", "The surface charge on this boundary.");
  params.addRequiredCoupledVar("em", "The electron density. (Used for Jacobian calculation.)");
  params.addRequiredCoupledVar("mean_en",
                               "The mean electron energy. (Used for Jacobian calculation.)");
  params.addRequiredCoupledVar("ions",
                               "All of the ions in the system. (Used for Jacobian calculation.)");
  params.addRequiredParam<Real>("position_units", "The units of position.");
  return params;
}

InterfacePotential::InterfacePotential(const InputParameters & parameters)
  : InterfaceKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _D(getMaterialProperty<Real>("diff" + _var.name())),
    _D_neighbor(getNeighborMaterialProperty<Real>("diff" + _neighbor_var.name())),
    //_sigma(coupledValue("sigma"))
    _sigma(getMaterialProperty<Real>("surface_charge")),
    _d_sigma_d_potential(getMaterialProperty<Real>("d_surface_charge_d_potential")),
    _d_sigma_d_em(getMaterialProperty<Real>("d_surface_charge_d_em")),
    _d_sigma_d_mean_en(getMaterialProperty<Real>("d_surface_charge_d_mean_en")),
    _d_sigma_d_ion(getMaterialProperty<std::vector<Real>>("d_surface_charge_d_ion")),

    // Coupled Variable IDs
    _em_id(coupled("em")),
    _mean_en_id(coupled("mean_en"))
{
  _num_ions = coupledComponents("ions");

  // Resize the vectors to store _num_ions values:
  _ion_id.resize(_num_ions);

  // Retrieve the values for each ion and store in the relevant vectors.
  // Note that these need to be dereferenced to get the values inside the
  // main body of the code.
  // e.g. instead of "_ip[_qp]" it would be "(*_ip[i])[_qp]", where "i"
  // refers to a single ion species.
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion_id[i] = getVar("ions", i)->number();
  }
}

Real
InterfacePotential::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  switch (type)
  {
    case Moose::Element:
      r = -_test[_i][_qp] *
          (_D_neighbor[_qp] * _grad_neighbor_value[_qp] * _r_units * _normals[_qp] + _sigma[_qp]);
      break;

    case Moose::Neighbor:
      // r = _test_neighbor[_i][_qp] * (_D[_qp] * _grad_u[_qp] * _r_units * _normals[_qp]);
      // r = 0.0;
      r = _test_neighbor[_i][_qp] *
          (_D[_qp] * _grad_u[_qp] * _r_units * _normals[_qp] - _sigma[_qp]);
      /*
      r = _test_neighbor[_i][_qp] *
          (_D[_qp] * _grad_u[_qp] * _r_units * _normals[_qp] + _sigma[_qp]);
          */
      break;
  }

  return r;
}

Real
InterfacePotential::computeQpJacobian(Moose::DGJacobianType type)
{
  // The surface charge is a function of the gas-side plasma (_grad_u, not _grad_neighbor_value)
  // So we need ElementElement derivatives here as well!
  Real jac = 0;

  switch (type)
  {
    case Moose::ElementElement:
      jac = -_test[_i][_qp] * _d_sigma_d_potential[_qp] * -_grad_phi[_j][_qp] * _normals[_qp] *
            _r_units;
      break;

    case Moose::NeighborNeighbor:
      break;

    case Moose::NeighborElement:
      jac = _test_neighbor[_i][_qp] * _grad_phi[_j][_qp] * _normals[_qp] * _r_units *
            (_D[_qp] - _d_sigma_d_potential[_qp]);
      // jac = _test_neighbor[_i][_qp] * _D[_qp] * _grad_phi[_j][_qp] * _normals[_qp] * _r_units;
      // jac = 0.0;
      break;

    case Moose::ElementNeighbor:
      jac = -_test[_i][_qp] * _D_neighbor[_qp] * _grad_phi_neighbor[_j][_qp] * _r_units *
            _normals[_qp];
      break;
  }

  return jac;
}

Real
InterfacePotential::computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar)
{
  Real off_jac = 0;

  // There are three core dependencies of the off diagonal jacobian!
  //    1. Electron density _em
  //    2. Mean electron energy, _mean_en
  //    3. Ion density, _ip
  //
  // Note that the ion density corresponds to ALL POSSIBLE ions, so a search is performed to
  // check whether jvar == any _ip_id
  //
  // Also note that all off-diagonal jacobians are on the Element side, not the Neighbor side.
  // Therefore, all derivatives w.r.t. neighbor variables (ElementNeighbor and NeighborNeighbor)
  // are zero. Convenient!
  //
  // The signs should be included in the derivative terms.

  // Iterator for finding the correct ion derivative
  _iter = std::find(_ion_id.begin(), _ion_id.end(), jvar);
  if (jvar == _em_id)
  {
    switch (type)
    {
      case Moose::ElementElement:
        off_jac = -_test[_i][_qp] * _d_sigma_d_em[_qp] * _phi[_j][_qp] * _r_units;
        break;

      case Moose::NeighborNeighbor:
        break;

      case Moose::NeighborElement:
        off_jac = _test_neighbor[_i][_qp] * _phi[_j][_qp] * _r_units * _d_sigma_d_em[_qp];
        break;

      case Moose::ElementNeighbor:
        break;
    }
  }
  else if (jvar == _mean_en_id)
  // if (jvar == _mean_en_id)
  {
    switch (type)
    {
      case Moose::ElementElement:
        off_jac = -_test[_i][_qp] * _d_sigma_d_mean_en[_qp] * _phi[_j][_qp] * _r_units;
        break;

      case Moose::NeighborNeighbor:
        break;

      case Moose::NeighborElement:
        off_jac = _test_neighbor[_i][_qp] * _phi[_j][_qp] * _r_units * _d_sigma_d_mean_en[_qp];
        break;

      case Moose::ElementNeighbor:
        break;
    }
  }
  else if (_iter != _ion_id.end())
  // if (_iter != _ion_id.end())
  {
    _ip_index = std::distance(_ion_id.begin(), _iter);
    switch (type)
    {
      case Moose::ElementElement:
        off_jac = -_test[_i][_qp] * _d_sigma_d_ion[_qp][_ip_index] * _phi[_j][_qp] * _r_units;
        break;

      case Moose::NeighborNeighbor:
        break;

      case Moose::NeighborElement:
        off_jac =
            _test_neighbor[_i][_qp] * _phi[_j][_qp] * _r_units * _d_sigma_d_ion[_qp][_ip_index];
        break;

      case Moose::ElementNeighbor:
        break;
    }
  }

  return off_jac;
}
