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

#include "ElectronEnergyDiffusion.h"


template<>
InputParameters validParams<ElectronEnergyDiffusion>()
{
  InputParameters params = validParams<Diffusion>();

  params.addRequiredCoupledVar("em","The electron density used to calculate the diffusivity using the Einstein relation");

  return params;
}


ElectronEnergyDiffusion::ElectronEnergyDiffusion(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),
    
    // Input Parameters

    // Material Properties

    _mu_mean_electron_energy(getMaterialProperty<Real>("mu_mean_electron_energy")),

    // Coupled Variables

    _em(coupledValue("em")),
    _em_id(coupled("em")),

    // Unique variables

    _T_em(0.0),
    _D_mean_electron_energy(0.0)
{
}

ElectronEnergyDiffusion::~ElectronEnergyDiffusion()
{
}

Real
ElectronEnergyDiffusion::computeQpResidual()
{
  _T_em = _u[_qp]*2.0/(3.0*_em[_qp]);
  _D_mean_electron_energy = _mu_mean_electron_energy[_qp]*_T_em;
  return _D_mean_electron_energy*_grad_u[_qp] * _grad_test[_i][_qp];
}

Real
ElectronEnergyDiffusion::computeQpJacobian()
{
  return _grad_test[_i][_qp]*(_grad_u[_qp]*_mu_mean_electron_energy[_qp]*_phi[_j][_qp]*2.0/(3.0*_em[_qp])+_D_mean_electron_energy*_grad_phi[_j][_qp]);
}

Real ElectronEnergyDiffusion::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
    {
      return _grad_test[_i][_qp]*_grad_u[_qp]*_mu_mean_electron_energy[_qp]*_u[_qp]*2.0/(3.0*-std::pow(_em[_qp],2))*_phi[_j][_qp];
    }
  else
    {
      return 0.0;
    }
}
