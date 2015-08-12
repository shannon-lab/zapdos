#include "AuxSource.h"

template<>
InputParameters validParams<AuxSource>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("em","The electron density");
  params.addRequiredCoupledVar("potential","The potential");
  
  return params;
}

AuxSource::AuxSource(const InputParameters & parameters) :
    AuxKernel(parameters),

    _muem(380.0/1e4),
    _diff(1800.0/1e4), // Morrow, Ebert
    _em(coupledValue("em")),
    _grad_potential(coupledGradient("potential")),
    _grad_em(coupledGradient("em"))
{
}

Real
AuxSource::computeValue()
{
  return 0.35*std::exp(-1.65e7/(_grad_potential[_qp].size()))*(-_muem*-_grad_potential[_qp]*_em[_qp]-_diff*_grad_em[_qp]).size();
  // return 1.0/(_grad_potential.size());
}

 
