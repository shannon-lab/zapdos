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


ElectronEnergyDiffusion::ElectronEnergyDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),
    
    // Input Parameters

    // Material Properties

    _muem(getMaterialProperty<Real>("muem")),

    // Coupled Variables

    _em(coupledValue("em")),
    _em_id(coupled("em")),

    // Unique variables

    _T_e(0.0),
    _D_Te(0.0),
    _mu_Te(0.0),
    _d_D_Te_d_Te(0.0)
{
}

ElectronEnergyDiffusion::~ElectronEnergyDiffusion()
{
}

Real
ElectronEnergyDiffusion::computeQpResidual()
{
  _mu_Te = 5.0/3.0*_muem[_qp];
  _T_e = _std::max(_u[_qp],0.0);
  _D_Te = _mu_Te*_T_e;
  return 1.5*_D_Te*_em[_qp]*_grad_u[_qp] * _grad_test[_i][_qp];
}

Real
ElectronEnergyDiffusion::computeQpJacobian()
{
  _mu_Te = 5.0/3.0*_muem[_qp];
  _T_e = _std::max(_u[_qp],0.0);
  _D_Te = _mu_Te*_T_e;
  _d_D_Te_d_Te = _mu_Te;
  return 1.5*_em[_qp]*_grad_test[_i][_qp]*(_grad_u[_qp]*_d_D_Te_d_Te*_phi[_j][_qp]+_D_Te*_grad_phi[_j][_qp]);
}

Real ElectronEnergyDiffusion::computeQpOffDiagJacobian(unsigned int jvar)
{
  _mu_Te = 5.0/3.0*_muem[_qp];
  _T_e = _std::max(_u[_qp],0.0);
  _D_Te = _mu_Te*_T_e;

  if (jvar == _em_id)
    {
      return 1.5*_D_Te*_phi[_j][_qp]*_grad_u[_qp] * _grad_test[_i][_qp];
    }
  else
    {
      return 0.0;
    }
}
