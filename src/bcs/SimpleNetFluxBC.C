#include "SimpleNetFluxBC.h"

// To clarify language: species current refers to the electrical current produced by motion of that species

template<>
InputParameters validParams<SimpleNetFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("x_boundary_species_current","The value of the species current at the boundary in the x direction.");
  params.addParam<Real>("y_boundary_species_current",0.0,"The value of the species current at the boundary in the y direction.");
  params.addParam<Real>("z_boundary_species_current",0.0,"The value of the species current at the boundary in the z direction.");
  return params;
}

SimpleNetFluxBC::SimpleNetFluxBC(const InputParameters & parameters) :
  IntegratedBC(parameters),
  _x_boundary_species_current(getParam<Real>("x_boundary_species_current")),
  _y_boundary_species_current(getParam<Real>("y_boundary_species_current")),
  _z_boundary_species_current(getParam<Real>("z_boundary_species_current"))

  // MaterialProperties
{

  _species_current(0) = _x_boundary_species_current;
  _species_current(1) = _y_boundary_species_current;
  _species_current(2) = _z_boundary_species_current;

}

Real
SimpleNetFluxBC::computeQpResidual()
{
  return _test[_i][_qp]*_species_current*_normals[_qp];
}

