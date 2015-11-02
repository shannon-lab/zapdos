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

#include "ResidAndJacobTerms.h"

template<>
InputParameters validParams<ResidAndJacobTerms>()
{
  InputParameters params = validParams<ElementUserObject>();
  params.addRequiredCoupledVar("u","The dummy variable.");
  params.addRequiredParam<FEFamily>("fe_family", "The family of shape functions.");
  params.addRequiredParam<Order>("fe_order", "The order of the shape functions.");
  return params;
}

ResidAndJacobTerms::ResidAndJacobTerms(const InputParameters & parameters) :
  ElementUserObject(parameters),
  _u(coupledValue("u")),
  _grad_u(coupledGradient("u")),
  _diffusivity(getMaterialProperty<Real>("diffusivity")),
  _d_diffusivity_d_u(getMaterialProperty<Real>("d_diffusivity_d_u")),
  _DiffusionResid(0,0,0),
  _DiffusionJac(0,0,0),
  _fe_type(getParam<Order>("fe_order"), getParam<FEFamily>("fe_family")),
  _grad_phi(_assembly.feGradPhi(_fe_type)),
  _phi(_assembly.fePhi(_fe_type)),
  _qp(0)
{
}

RealVectorValue
ResidAndJacobTerms::getTerm(std::string term_name, const unsigned int j, const unsigned int qp)
{
  return _electrode_area;
}

void
ResidAndJacobTerms::initialize()
{
}

void
ResidAndJacobTerms::execute()
{
  for (_qp=0; _qp<_qrule->n_points(); _qp++) {
    _DiffusionResid = -_diffusivity[_qp]*_grad_u[_qp];
    // _DiffusionJac = -_d_diffusivity_d_u[_qp] * _grad_u[_qp] -_diffusivity[_qp]*_grad_phi[_qp];
  }
}

void
ResidAndJacobTerms::threadJoin(const UserObject & y)
{
}

void
ResidAndJacobTerms::finalize()
{
}
