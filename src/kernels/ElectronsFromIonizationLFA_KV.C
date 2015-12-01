/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ElectronsFromIonizationLFA_KV.h"


template<>
InputParameters validParams<ElectronsFromIonizationLFA_KV>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential","The potential.");
  return params;
}


ElectronsFromIonizationLFA_KV::ElectronsFromIonizationLFA_KV(const InputParameters & parameters) :
    Kernel(parameters),
    
    _diffem(getMaterialProperty<Real>("diffem")),
    _muem(getMaterialProperty<Real>("muem")),
    _iz_coeff_efield_a(getMaterialProperty<Real>("iz_coeff_efield_a")),
    _iz_coeff_efield_b(getMaterialProperty<Real>("iz_coeff_efield_b")),
    _iz_coeff_efield_c(getMaterialProperty<Real>("iz_coeff_efield_c")),

    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential"))
{
}

ElectronsFromIonizationLFA_KV::~ElectronsFromIonizationLFA_KV()
{
}

Real
ElectronsFromIonizationLFA_KV::computeQpResidual()
{
    return -_test[_i][_qp]*_iz_coeff_efield_a[_qp]*std::pow(_grad_potential[_qp].size() * 1000. + std::numeric_limits<double>::epsilon(),_iz_coeff_efield_b[_qp])*std::exp(-_iz_coeff_efield_c[_qp]/(_grad_potential[_qp].size() * 1000. + std::numeric_limits<double>::epsilon()))*(-_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp]).size();
}

Real
ElectronsFromIonizationLFA_KV::computeQpJacobian()
{
  RealVectorValue _em_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp];
  RealVectorValue _d_em_flux_d_em = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_diffem[_qp]*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]);

  return -_test[_i][_qp]*_iz_coeff_efield_a[_qp]*std::pow(_grad_potential[_qp].size() * 1000. + std::numeric_limits<double>::epsilon(),_iz_coeff_efield_b[_qp])*std::exp(-_iz_coeff_efield_c[_qp]/(_grad_potential[_qp].size() * 1000. + std::numeric_limits<double>::epsilon()))*_em_flux*_d_em_flux_d_em/(_em_flux.size()+std::numeric_limits<double>::epsilon());
}

Real
ElectronsFromIonizationLFA_KV::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) { 
   RealVectorValue _em_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp];
   Real _em_flux_mag = _em_flux.size();
   RealVectorValue _d_em_flux_d_potential = -_muem[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp]);
   Real _d_em_flux_mag_d_potential = _em_flux*_d_em_flux_d_potential/(_em_flux_mag+std::numeric_limits<double>::epsilon());
   Real _iz = _iz_coeff_efield_a[_qp]*std::pow(_grad_potential[_qp].size() * 1000. + std::numeric_limits<double>::epsilon(),_iz_coeff_efield_b[_qp])*std::exp(-_iz_coeff_efield_c[_qp]/(_grad_potential[_qp].size() * 1000. + std::numeric_limits<double>::epsilon()));
   Real _d_iz_d_potential = std::pow(_grad_potential[_qp].size() * 1000. + std::numeric_limits<double>::epsilon(),_iz_coeff_efield_b[_qp]-2.0)*_iz_coeff_efield_a[_qp]*(_grad_potential[_qp].size() * 1000. * _iz_coeff_efield_b[_qp]+_iz_coeff_efield_c[_qp])*std::exp(-_iz_coeff_efield_c[_qp]/(_grad_potential[_qp].size() * 1000. + std::numeric_limits<double>::epsilon()))*_grad_potential[_qp]*_grad_phi[_j][_qp]/(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon());

    return -_test[_i][_qp]*(_iz*_d_em_flux_mag_d_potential + _d_iz_d_potential*_em_flux_mag);
  }

  else {
    return 0.0;
  }
}
