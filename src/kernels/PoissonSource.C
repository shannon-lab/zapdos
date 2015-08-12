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

#include "PoissonSource.h"

template<>
InputParameters validParams<PoissonSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("Arp", "Ion density in the simulation");
  params.addRequiredCoupledVar("em", "Electron density in the simulation");
  return params;
}

PoissonSource::PoissonSource(const InputParameters & parameters) :
    Kernel(parameters),
    
    // Material properties 
    
    _permittivity(getMaterialProperty<Real>("permittivity")),
    _e(getMaterialProperty<Real>("e")),
    
    // Coupled variables
    
    _Arp(coupledValue("Arp")),
    _em(coupledValue("em")),
    _Arp_id(coupled("Arp")),
    _em_id(coupled("em"))
    
{
}

/* Adding scaling terms for both the densities and the potential. The scaling term
for the densities is 1e19. The scaling term for the potential is 1e4 */

Real
PoissonSource::computeQpResidual()
{
  return -_test[_i][_qp]*_e[_qp]/_permittivity[_qp]*(_Arp[_qp]-_em[_qp]);
}

Real
PoissonSource::computeQpJacobian()
{
  return 0.0;
}

Real
PoissonSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _Arp_id)
    {
      return -_test[_i][_qp]*_e[_qp]/_permittivity[_qp]*_phi[_j][_qp];
    }
  
  else if (jvar == _em_id)
    {
      return _test[_i][_qp]*_e[_qp]/_permittivity[_qp]*_phi[_j][_qp];
    }
  else
    {
      return 0.0;
    }
}
