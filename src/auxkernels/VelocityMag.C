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

#include "VelocityMag.h"

template<>
InputParameters validParams<VelocityMag>()
{
  InputParameters params = validParams<AuxKernel>();
  
  //MooseEnum component("x y z");
  
  //params.addRequiredParam<MooseEnum>("component",component, "The desired component of potential gradient.");

  // Add a "coupling paramater" to get a variable from the input file.
  /*  params.addRequiredCoupledVar("potential", "The potential"); */

      return params;
}

VelocityMag::VelocityMag(const InputParameters & parameters) :
    AuxKernel(parameters),
    
    //_component(getParam<MooseEnum>("component")),

    // Get the gradient of the variable
    //    _grad_potential(coupledGradient("potential")),
    
    // Get material properties
    //    _velocity_coeff(getMaterialProperty<Real>("velocity_coeff"))
    _velocity(getMaterialProperty<RealVectorValue>("velocity"))

{
}

Real
VelocityMag::computeValue()
{
  // Access the gradient of the pressure at this quadrature point
  // Then pull out the "component" of it we are looking for (x, y or z)
  // Note that getting a particular component of a gradient is done using the
  // parenthesis operator
  return _velocity[_qp].size();
  // return _grad_potential[_qp](_component);
}
