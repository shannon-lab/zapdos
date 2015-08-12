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

#ifndef PROVIDEMOBILITY_H
#define PROVIDEMOBILITY_H

#include "GeneralUserObject.h"

//Forward Declarations
class ProvideMobility;

template<>
InputParameters validParams<ProvideMobility>();

class ProvideMobility : public GeneralUserObject
{
public:
  ProvideMobility(const InputParameters & parameters);

  Real mu_em() const;
  Real diff_em() const;
  Real mu_ip() const;
  Real diff_ip() const;
  Real electrode_area() const;
  Real ballast_resist() const;
  Real coulomb_charge() const;

  virtual void initialize();

  virtual void execute();

  virtual void finalize();

protected:

  Real _muem;
  Real _diffem;
  Real _muip;
  Real _diffip;
  Real _electrode_area;
  Real _ballast_resist;
  Real _e;

};

#endif
