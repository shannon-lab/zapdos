#include "IsotropicDiff.h"

template<>
InputParameters validParams<IsotropicDiff>()
{
  InputParameters params = validParams<Diffusion>;

  params.addRequiredParam<std::string>("var_name_string","The name of the kernel variable. Required to import the correct mobility from the material properties file.");
  params.addRequiredCoupledVar("potential","The potential for calculating the advection velocity.");
  return params;
}

IsotropicDiff::IsotropicDiff(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),

    // Coupled variables

    _grad_potential(coupledGradient("potential")),

    // Material properties

    _mobility(getMaterialProperty<Real>("mu"+
{
}

IsotropicDiff::~IsotropicDiff()
{
}

Real
IsotropicDiff::computeQpResidual()
{
  return _tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp]*_velocity[_qp]*_grad_u[_qp];    
