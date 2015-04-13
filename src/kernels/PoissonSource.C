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
  params.addRequiredParam<Real>("permittivity", "The permittivity of the medium");
  params.addParam<Real>("coulomb_charge", 1.6e-19, "The charge of a single electron");
  params.addRequiredCoupledVar("ion_density", "Ion density in the simulation");
  params.addRequiredCoupledVar("electron_density", "Electron density in the simulation");
  return params;
}

PoissonSource::PoissonSource(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    
    _permittivity(getParam<Real>("permittivity")),
    _coulomb_charge(getParam<Real>("coulomb_charge")),
    _ion_density(coupledValue("ion_density")),
    _electron_density(coupledValue("electron_density")),
    _ion_density_id(coupled("ion_density")),
    _electron_density_id(coupled("electron_density"))
    
{
}

Real
PoissonSource::computeQpResidual()
{
  return _test[_i][_qp]*_coulomb_charge/_permittivity*(_electron_density[_qp]-_ion_density[_qp]);
}

Real
PoissonSource::computeQpJacobian()
{
  return 0.0;
}

Real
PoissonSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _ion_density_id)
  {
    return -_test[_i][_qp]*_coulomb_charge/_permittivity*_phi[_j][_qp];
  }
  
  if (jvar == _electron_density_id)
  {
    return _test[_i][_qp]*_coulomb_charge/_permittivity*_phi[_j][_qp];
  }
  
  return 0.0;
}
  
