//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DGCoeffDiffusion.h"

registerMooseObject("ZapdosApp", DGCoeffDiffusion);

InputParameters
DGCoeffDiffusion::validParams()
{
  InputParameters params = ADDGKernel::validParams();
  // See header file for sigma and epsilon
  params.addRequiredParam<Real>("sigma", "sigma");
  params.addRequiredParam<Real>("epsilon", "epsilon");
  params.addClassDescription("The discontinuous Galerkin form of the generic diffusion term"
                             "(Densities must be in log form)");
  return params;
}

DGCoeffDiffusion::DGCoeffDiffusion(const InputParameters & parameters)
  : ADDGKernel(parameters),
    _epsilon(getParam<Real>("epsilon")),
    _sigma(getParam<Real>("sigma")),
    _diff(getADMaterialProperty<Real>("diff" + _var.name())),
    _diff_neighbor(getNeighborADMaterialProperty<Real>("diff" + _var.name()))
{
}

ADReal
DGCoeffDiffusion::computeQpResidual(Moose::DGResidualType type)
{
  ADReal r = 0;

  const unsigned int elem_b_order = static_cast<unsigned int>(_var.order());
  const double h_elem =
      _current_elem->volume() / _current_side_elem->volume() * 1. / std::pow(elem_b_order, 2.);

  switch (type)
  {
    using std::exp;
    case Moose::Element:
      r += 0.5 * (-_diff[_qp] * exp(_u[_qp]) * _grad_u[_qp] * _normals[_qp] * _test[_i][_qp] +
                  _epsilon * _grad_test[_i][_qp] * _normals[_qp] * exp(_u[_qp]));
      r += _sigma / h_elem * exp(_u[_qp]) * _test[_i][_qp];

      r += 0.5 * (-_diff_neighbor[_qp] * exp(_u_neighbor[_qp]) * _grad_u_neighbor[_qp] *
                      _normals[_qp] * _test[_i][_qp] -
                  _epsilon * _grad_test[_i][_qp] * _normals[_qp] * exp(_u_neighbor[_qp]));
      r += -_sigma / h_elem * exp(_u_neighbor[_qp]) * _test[_i][_qp];
      break;

    case Moose::Neighbor:
      r += 0.5 *
           (_diff[_qp] * exp(_u[_qp]) * _grad_u[_qp] * _normals[_qp] +
            _diff_neighbor[_qp] * exp(_u_neighbor[_qp]) * _grad_u_neighbor[_qp] * _normals[_qp]) *
           _test_neighbor[_i][_qp];
      r += _epsilon * 0.5 * _grad_test_neighbor[_i][_qp] * _normals[_qp] *
           (exp(_u[_qp]) - exp(_u_neighbor[_qp]));
      r -= _sigma / h_elem * (exp(_u[_qp]) - exp(_u_neighbor[_qp])) * _test_neighbor[_i][_qp];
      break;
  }

  return r;
}
