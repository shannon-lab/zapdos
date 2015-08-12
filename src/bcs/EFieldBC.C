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

#include "EFieldBC.h"

template<>
InputParameters validParams<EFieldBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("x_boundary_e_field","The value of the electric field at the boundary in the x direction.");
  params.addParam<Real>("y_boundary_e_field",0.0,"The value of the electric field at the boundary in the y direction.");
  params.addParam<Real>("z_boundary_e_field",0.0,"The value of the electric field at the boundary in the z direction.");
  return params;
}

EFieldBC::EFieldBC(const InputParameters & parameters) :
  IntegratedBC(parameters),
  _x_boundary_e_field(getParam<Real>("x_boundary_e_field")),
  _y_boundary_e_field(getParam<Real>("y_boundary_e_field")),
  _z_boundary_e_field(getParam<Real>("z_boundary_e_field")),

  // MaterialProperties

  _eps_r(getMaterialProperty<Real>("eps_r")),
  _potential_mult(getMaterialProperty<Real>("potential_mult"))
{

  _e_field(0) = _x_boundary_e_field;
  _e_field(1) = _y_boundary_e_field;
  _e_field(2) = _z_boundary_e_field;

}

Real
EFieldBC::computeQpResidual()
{
  return _test[_i][_qp]*_normals[_qp]*_e_field/(_eps_r[_qp]*_potential_mult[_qp]);
}

