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

#include "ElectronDiffusion.h"


template<>
InputParameters validParams<ElectronDiffusion>()
{
  InputParameters params = validParams<Diffusion>();

  params.addRequiredCoupledVar("mean_electron_energy","The electron energy used to calculate the diffusivity using the Einstein relation");

  return params;
}


ElectronDiffusion::ElectronDiffusion(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),
    
    // Input Parameters

    // Material Properties

    _muem(getMaterialProperty<Real>("muem")),

    // Coupled Variables

    _mean_electron_energy(coupledValue("mean_electron_energy")),
    _mean_electron_energy_id(coupled("mean_electron_energy")),

    // Unique variables

    _T_em(0.0),
    _D_em(0.0)
{
}

ElectronDiffusion::~ElectronDiffusion()
{
}

Real
ElectronDiffusion::computeQpResidual()
{
  _T_em = _mean_electron_energy[_qp]*2.0/(3.0*_u[_qp]);
  _D_em = _muem[_qp]*_T_em;
  return _D_em*_grad_u[_qp] * _grad_test[_i][_qp];
}

Real
ElectronDiffusion::computeQpJacobian()
{
  return _grad_test[_i][_qp]*(_grad_u[_qp]*_muem[_qp]*_mean_electron_energy[_qp]*2.0/(3.0*-std::pow(_u[_qp],2))*_phi[_j][_qp]+_D_em*_grad_phi[_j][_qp]);
}

Real ElectronDiffusion::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _mean_electron_energy_id)
    {
      return _grad_test[_i][_qp]*_grad_u[_qp]*_muem[_qp]*_phi[_j][_qp]*2.0/(3.0*_u[_qp]);
    }
  else
    {
      return 0.0;
    }
}
