//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADComsolSecondaryElectronBC.h"

// MOOSE includes
#include "MooseVariable.h"

registerADMooseObject("ZapdosApp", ADComsolSecondaryElectronBC);

defineADLegacyParams(ADComsolSecondaryElectronBC);

InputParameters
ADComsolSecondaryElectronBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient of the electrons.");
  params.addParam<Real>("r_ion", 0, "The reflection coefficient of the ions.");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("mean_en", "The electron density.");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

ADComsolSecondaryElectronBC::ADComsolSecondaryElectronBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),
    _r_ion(getParam<Real>("r_ion")),
    _kb(getMaterialProperty<Real>("k_boltz")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),
    _mean_en(adCoupledValue("mean_en")),

    _muem(getADMaterialProperty<Real>("muem")),
    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _se_coeff(getMaterialProperty<Real>("se_coeff"))
{
  _ion_flux = 0;
  _b = 0.5;

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
ADComsolSecondaryElectronBC::computeQpResidual()
{
  // Ion flux is a vector, but this value is multiplied by _normals[_qp] so
  // it is a scalar quantity.
  _ion_flux = 0.0;
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgnip[i])[_qp] * -_grad_potential[_qp] > 0.0)
      _b = 1.0;
    else
      _b = 0.0;

    _ion_flux += std::exp((*_ip[i])[_qp]) *
                 (0.5 * std::sqrt(8 * _kb[_qp] * (*_Tip[i])[_qp] / (M_PI * (*_massip[i])[_qp])) +
                  _b * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] * _r_units *
                      _normals[_qp]);
  }

  return -_test[_i][_qp] * _r_units * _se_coeff[_qp] * _ion_flux;
}
