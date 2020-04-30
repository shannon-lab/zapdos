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

    _sign(1)
{
  _num_ions = coupledComponents("ion");

  // Resize the vectors to store _num_ions values:
  _ion.resize(_num_ions);
  _ion_var.resize(_num_ions);
  _ion_id.resize(_num_ions);
  _muion.resize(_num_ions);
  _sgnion.resize(_num_ions);

  // Retrieve the values for each ion and store in the relevant vectors.
  // Note that these need to be dereferenced to get the values inside the
  // main body of the code.
  // e.g. instead of "_ip[_qp]" it would be "(*_ip[i])[_qp]", where "i"
  // refers to a single ion species.
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion_var[i] = getVar("ion", i);
    _ion[i] = &coupledValue("ion", i);
    _ion_id[i] = _ion_var[i]->number();
    _muion[i] = &getMaterialProperty<Real>("mu" + (*getVar("ion", i)).name());
    _sgnion[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ion", i)).name());
  }
}

Real
LymberopoulosElectronBC::computeQpResidual()
{
  _ion_flux.zero();
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion_flux += (*_sgnion[i])[_qp] * (*_muion[i])[_qp] * -_grad_potential[_qp] * _r_units *
                 std::exp((*_ion[i])[_qp]);
  }

  return _test[_i][_qp] * _r_units *
         (_sign * _ks * std::exp(_u[_qp]) * _normals[_qp] * _normals[_qp] -
          _gamma * _ion_flux * _normals[_qp]);
}

Real
LymberopoulosElectronBC::computeQpJacobian()
{
  return _test[_i][_qp] * _r_units *
         (_sign * _ks * std::exp(_u[_qp]) * _phi[_j][_qp] * _normals[_qp] * _normals[_qp]);
}

Real
LymberopoulosElectronBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  _iter = std::find(_ion_id.begin(), _ion_id.end(), jvar);
  if (jvar == _potential_id)
  {
    _d_ion_flux_d_V.zero();
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      _d_ion_flux_d_V += (*_sgnion[i])[_qp] * (*_muion[i])[_qp] * -_grad_phi[_j][_qp] * _r_units *
                         std::exp((*_ion[i])[_qp]);
    }

    return _test[_i][_qp] * _r_units * ((-_gamma * _d_ion_flux_d_V * _normals[_qp]));
  }
  else if (_iter != _ion_id.end())
  {
    _ip_index = std::distance(_ion_id.begin(), _iter);

    _d_ion_flux_d_ion =
        ((*_sgnion[_ip_index])[_qp] * (*_muion[_ip_index])[_qp] * -_grad_potential[_qp] * _r_units *
         std::exp((*_ion[_ip_index])[_qp]) * _phi[_j][_qp]);

    return _test[_i][_qp] * _r_units * ((-_gamma * _d_ion_flux_d_ion * _normals[_qp]));
  }
  else
    return 0.0;
}
