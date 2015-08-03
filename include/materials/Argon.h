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
#ifndef ARGON_H_
#define ARGON_H_

#include "Material.h"

class Argon;

template<>
InputParameters validParams<Argon>();

class Argon : public Material
{
public:
  Argon(const std::string & name, InputParameters parameters);

protected:
  virtual void computeQpProperties();

  MaterialProperty<Real>  & _muem;
  MaterialProperty<Real>  & _diffem;
  MaterialProperty<Real>  & _muip;
  MaterialProperty<Real>  & _diffip;
  MaterialProperty<Real>  & _rate_coeff_ion;
  MaterialProperty<Real>  & _Eiz;
  MaterialProperty<Real>  & _Ar;
  MaterialProperty<Real> &  _muel;
  MaterialProperty<Real> &  _diffel;
  MaterialProperty<Real> &  _rate_coeff_elastic;
  MaterialProperty<Real> &  _mem;
  MaterialProperty<Real> &  _mip;
  MaterialProperty<Real> &  _se_coeff;
};

#endif //ARGON_H
