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

template<>
InputParameters validParams<ProvideMobility>()
{
  InputParameters params = validParams<GeneralUserObject>();
  return params;
}

ProvideMobility::ProvideMobility(const std::string & name, InputParameters parameters) :
  GeneralUserObject(name, parameters),
  _muem(8.86e-2), // Values for air
  _diffem(7.62e-2),
  _muip(8.86e-4),
  _diffip(7.62e-4),
  _electrode_area(1.26e-5), // in square meters. Taken from Comsol's 1D corona discharge
  _ballast_resist(1e6), // Also taken from Comsol's 1D corona discharge
  _e(1.6e-19)
{
}

Real
ProvideMobility::mu_em() const
{
  return _muem;
}
Real
ProvideMobility::diff_em() const
{
  return _diffem;
}
Real
ProvideMobility::mu_ip() const
{
  return _muip;
}
Real
ProvideMobility::diff_ip() const
{
  return _diffip;
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
