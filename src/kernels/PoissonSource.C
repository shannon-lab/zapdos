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
  params.addRequiredCoupledVar("ion_density", "Ion density in the simulation");
  params.addRequiredCoupledVar("electron_density", "Electron density in the simulation");
  return params;
}

PoissonSource::PoissonSource(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    
    // Material properties 
    
    _permittivity(getMaterialProperty<Real>("permittivity")),
    _coulomb_charge(getMaterialProperty<Real>("coulomb_charge")),
    _density_mult(getMaterialProperty<Real>("density_mult")),
    _potential_mult(getMaterialProperty<Real>("potential_mult")),
    
    // Coupled variables
    
    _ion_density(coupledValue("ion_density")),
    _electron_density(coupledValue("electron_density")),
    _ion_density_id(coupled("ion_density")),
    _electron_density_id(coupled("electron_density"))
    
{
}

/* Adding scaling terms for both the densities and the potential. The scaling term
for the densities is 1e19. The scaling term for the potential is 1e4 */

Real
PoissonSource::computeQpResidual()
{
  return _test[_i][_qp]*_coulomb_charge[_qp]/_permittivity[_qp]*_density_mult[_qp]/_potential_mult[_qp]*(_electron_density[_qp]-_ion_density[_qp]);
}

Real
PoissonSource::computeQpJacobian()
{
  return 0.0;
}

/*Real
PoissonSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _ion_density_id)
  {
    return -_test[_i][_qp]*_coulomb_charge[_qp]/_permittivity[_qp]*_density_mult[_qp]/_potential_mult[_qp]*_phi[_j][_qp];
  }
  
  if (jvar == _electron_density_id)
  {
    return _test[_i][_qp]*_coulomb_charge[_qp]/_permittivity[_qp]*_density_mult[_qp]/_potential_mult[_qp]*_phi[_j][_qp];
  }
  
  return 0.0;
} */
  
