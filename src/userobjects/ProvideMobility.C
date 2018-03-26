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

#include "ProvideMobility.h"

registerMooseObject("ZapdosApp", ProvideMobility);

template <>
InputParameters
validParams<ProvideMobility>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params.addRequiredParam<Real>("electrode_area", "The area of the electrode or plasma.");
  params.addRequiredParam<Real>("ballast_resist", "The magnitude of the ballasting resistance.");
  params.addRequiredParam<Real>("e", "The Coulomb charge");
  return params;
}

ProvideMobility::ProvideMobility(const InputParameters & parameters)
  : GeneralUserObject(parameters),
    _electrode_area(getParam<Real>(
        "electrode_area")), // in square meters. Taken from Comsol's 1D corona discharge
    _ballast_resist(
        getParam<Real>("ballast_resist")), // Also taken from Comsol's 1D corona discharge
    // _electrode_area(1.26e-5), // in square meters. Taken from Comsol's 1D corona discharge. Used
    // in my golden simulation results
    // _ballast_resist(1e6), // Also taken from Comsol's 1D corona discharge. Used in my golden
    // simulation results
    _e(getParam<Real>("e"))
{
}

Real
ProvideMobility::electrode_area() const
{
  return _electrode_area;
}
Real
ProvideMobility::ballast_resist() const
{
  return _ballast_resist;
}
Real
ProvideMobility::coulomb_charge() const
{
  return _e;
}

void
ProvideMobility::initialize()
{
}

void
ProvideMobility::execute()
{
}

void
ProvideMobility::finalize()
{
}
