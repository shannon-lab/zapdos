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
#ifndef JACMAT_H_
#define JACMAT_H_

#include "Material.h"

class JacMat;

template<>
InputParameters validParams<JacMat>();

class JacMat : public Material
{
public:
  JacMat(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  MaterialProperty<Real> & _muu;
  MaterialProperty<Real> & _muv;
  MaterialProperty<Real> & _sgnu;
  MaterialProperty<Real> & _sgnv;
  MaterialProperty<Real> & _diffu;
  MaterialProperty<Real> & _diffem;
  MaterialProperty<Real> & _muem;
  MaterialProperty<Real> & _iz_coeff_efield_a;
  MaterialProperty<Real> & _iz_coeff_efield_b;
  MaterialProperty<Real> & _iz_coeff_efield_c;

};

#endif //JACMAT_H
