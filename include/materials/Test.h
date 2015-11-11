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
#ifndef TEST_H_
#define TEST_H_

#include "Material.h"
class Test;

template<>
InputParameters validParams<Test>();

class Test : public Material
{
public:
  Test(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  // Material properties
  MaterialProperty<Real> & _diff;
};

#endif //TEST_H
