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
#ifndef TEST2_H_
#define TEST2_H_

#include "Material.h"
class Test2;

template<>
InputParameters validParams<Test2>();

class Test2 : public Material
{
public:
  Test2(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  // Material properties
  MaterialProperty<Real> & _diff;
};

#endif //TEST2_H
