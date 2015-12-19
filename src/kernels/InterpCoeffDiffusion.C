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

#include "InterpCoeffDiffusion.h"


template<>
InputParameters validParams<InterpCoeffDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addRequiredCoupledVar("v", "The variable that the diffusivity is a function of.");
  return params;
}

InterpCoeffDiffusion::InterpCoeffDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),
    _v(coupledValue("v")),
    _v_id(coupled("v")),
    _diffusivity(getMaterialProperty<Real>("d_interp")),
    _d_diffusivity_d_v(getMaterialProperty<Real>("d_d_interp_d_v"))
{
  // std::vector<Real> x;
  // std::vector<Real> y;
  // std::string path = "/home/lindsayad/zapdos/src/materials/test.txt";
  // const char *charPath = path.c_str();
  // std::ifstream myfile (charPath);
  // Real value;

  // if (myfile.is_open())
  // {
  //   while (myfile >> value)
  //   {
  //     x.push_back(value);
  //     myfile >> value;
  //     y.push_back(value);
  //   }
  //   myfile.close();
  // }

  // else std::cerr << "Unable to pen file" << std::endl;
  // _interpolation.setData(x, y);
}

InterpCoeffDiffusion::~InterpCoeffDiffusion()
{
}

Real
InterpCoeffDiffusion::computeQpResidual()
{
  // Real diffusivity = _interpolation.sample(_v[_qp]);
  return -_diffusivity[_qp] * _grad_u[_qp] * -_grad_test[_i][_qp];
  // return -diffusivity * _grad_u[_qp] * -_grad_test[_i][_qp];
}

Real
InterpCoeffDiffusion::computeQpJacobian()
{
  // Real diffusivity = _interpolation.sample(_v[_qp]);
  return -_diffusivity[_qp] * _grad_phi[_j][_qp] * -_grad_test[_i][_qp];
  // return -diffusivity * _grad_phi[_j][_qp] * -_grad_test[_i][_qp];
}

Real
InterpCoeffDiffusion::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_id)
    return -_d_diffusivity_d_v[_qp] * _phi[_j][_qp] * _grad_u[_qp] * -_grad_test[_i][_qp];
  else
    return 0.;
}
