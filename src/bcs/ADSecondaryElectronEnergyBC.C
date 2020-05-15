//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADSecondaryElectronEnergyBC.h"

// MOOSE includes
#include "MooseVariable.h"

registerADMooseObject("ZapdosApp", ADSecondaryElectronEnergyBC);

defineADLegacyParams(ADSecondaryElectronEnergyBC);

InputParameters
ADSecondaryElectronEnergyBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient of the electrons.");
  params.addParam<Real>("r_ion", 0, "The reflection coefficient of the ions.");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

ADSecondaryElectronEnergyBC::ADSecondaryElectronEnergyBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),
    _r_ion(getParam<Real>("r_ion")),
    _kb(getMaterialProperty<Real>("k_boltz")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),
    _em(adCoupledValue("em")),

    _muem(getADMaterialProperty<Real>("muem")),
    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _se_coeff(getMaterialProperty<Real>("se_coeff")),
    _se_energy(getMaterialProperty<Real>("se_energy")),
    _mumean_en(getADMaterialProperty<Real>("mumean_en"))
{
  _ion_flux = 0;
  _a = 0.5;
  _b = 0.5;
  _v_thermal = 0.0;
  _n_gamma = 0.0;

  _num_ions = coupledComponents("ip");

  // Resize the vectors to store _num_ions values:
  _ip.resize(_num_ions);
  _grad_ip.resize(_num_ions);
  _muip.resize(_num_ions);
  _Tip.resize(_num_ions);
  _massip.resize(_num_ions);
  _sgnip.resize(_num_ions);

  // Retrieve the values for each ion and store in the relevant vectors.
  // Note that these need to be dereferenced to get the values inside the
  // main body of the code.
  // e.g. instead of "_ip[_qp]" it would be "(*_ip[i])[_qp]", where "i"
  // refers to a single ion species.
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip[i] = &adCoupledValue("ip", i);
    _grad_ip[i] = &adCoupledGradient("ip", i);
    _muip[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ip", i)).name());
    _Tip[i] = &getADMaterialProperty<Real>("T" + (*getVar("ip", i)).name());
    _massip[i] = &getMaterialProperty<Real>("mass" + (*getVar("ip", i)).name());
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ip", i)).name());
  }
}

ADReal
ADSecondaryElectronEnergyBC::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  _ion_flux = 0;
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgnip[i])[_qp] * -_grad_potential[_qp] > 0.0)
      _b = 1.0;
    else
      _b = 0.0;
    _ion_flux += std::exp((*_ip[i])[_qp]) *
                 (0.5 * std::sqrt(8 * _kb[_qp] * (*_Tip[i])[_qp] / (M_PI * (*_massip[i])[_qp])) +
                  (2 * _b - 1) * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] *
                      _r_units * _normals[_qp]);
  }

  _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux /
             (_muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
              std::numeric_limits<double>::epsilon());

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units *
         ((1 - _r) / (1 + _r) * (-5. / 6. * _v_thermal * _n_gamma * _se_energy[_qp]) -
          5. / 3. * (2. / (1 + _r)) * _se_energy[_qp] * (1 - _a) * _se_coeff[_qp] * _ion_flux);
}
