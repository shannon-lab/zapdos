#include "SpeciesNetFluxBC.h"

// To clarify language: species current refers to the electrical current produced by motion of that species

template<>
InputParameters validParams<SpeciesNetFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("x_boundary_species_current","The value of the species current at the boundary in the x direction.");
  params.addParam<Real>("y_boundary_species_current",0.0,"The value of the species current at the boundary in the y direction.");
  params.addParam<Real>("z_boundary_species_current",0.0,"The value of the species current at the boundary in the z direction.");
  params.addRequiredParam<std::string>("species_charge","Specifies the charge of the species in question. Can be positive or negative.");
  return params;
}

SpeciesNetFluxBC::SpeciesNetFluxBC(const InputParameters & parameters) :
  IntegratedBC(parameters),
  _x_boundary_species_current(getParam<Real>("x_boundary_species_current")),
  _y_boundary_species_current(getParam<Real>("y_boundary_species_current")),
  _z_boundary_species_current(getParam<Real>("z_boundary_species_current")),

  // MaterialProperties
  _species_charge(getMaterialProperty<Real>(getParam<std::string>("species_charge"))),
  _coulomb_charge(getMaterialProperty<Real>("e")),
  _electron_mult(getMaterialProperty<Real>("electron_mult")),
  _N_A(getMaterialProperty<Real>("N_A"))
{

  _species_current(0) = _x_boundary_species_current;
  _species_current(1) = _y_boundary_species_current;
  _species_current(2) = _z_boundary_species_current;

}

Real
SpeciesNetFluxBC::computeQpResidual()
{
  return _test[_i][_qp]*_species_current*_normals[_qp]/(_species_charge[_qp]*_coulomb_charge[_qp]*_N_A[_qp]);
}

