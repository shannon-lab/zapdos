//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaSecondaryElectronWithEffEfieldBC.h"

registerMooseObject("ZapdosApp", SakiyamaSecondaryElectronWithEffEfieldBC);

InputParameters
SakiyamaSecondaryElectronWithEffEfieldBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addRequiredCoupledVar("Ex", "The EField in the x-direction");
  params.addCoupledVar("Ey", 0, "The EField in the y-direction"); // only required in 2D and 3D
  params.addCoupledVar("Ez", 0, "The EField in the z-direction"); // only required in 3D
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<Real>("users_gamma",
                        "A secondary electron emission coeff. only used for this BC.");
  params.addClassDescription("Kinetic secondary electron boundary condition"
                             "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

SakiyamaSecondaryElectronWithEffEfieldBC::SakiyamaSecondaryElectronWithEffEfieldBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _Ex(adCoupledValue("Ex")),
    _Ey(adCoupledValue("Ey")),
    _Ez(adCoupledValue("Ez")),

    _a(0.5),
    _ion_flux(0, 0, 0),
    _user_se_coeff(getParam<Real>("users_gamma"))
{
  _num_ions = coupledComponents("ip");

  _ip.resize(_num_ions);
  _muip.resize(_num_ions);
  _sgnip.resize(_num_ions);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip[i] = &adCoupledValue("ip", i);
    _muip[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ip", i)).name());
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ip", i)).name());
  }
}

ADReal
SakiyamaSecondaryElectronWithEffEfieldBC::computeQpResidual()
{
  ADRealVectorValue EField(_Ex[_qp], _Ey[_qp], _Ez[_qp]);

  _ion_flux.zero();
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgnip[i])[_qp] * EField >= 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }
    //_ion_flux += _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] * _r_units *
    //             std::exp((*_ip[i])[_qp]);

    _ion_flux += _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * EField * _r_units  *
                 std::exp((*_ip[i])[_qp]);
  }

  return -_test[_i][_qp] * _r_units * _a * _user_se_coeff * _ion_flux * _normals[_qp];
}
