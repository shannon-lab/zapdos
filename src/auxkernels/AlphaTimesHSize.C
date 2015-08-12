#include "AlphaTimesHSize.h"

template<>
InputParameters validParams<AlphaTimesHSize>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("potential", "The potential");

  return params;
}

AlphaTimesHSize::AlphaTimesHSize(const InputParameters & parameters) :
    AuxKernel(parameters),
    
    // Material Properties
    
    _potential_mult(getMaterialProperty<Real>("potential_mult")),

    // Coupled Variables
    
    _grad_potential(coupledGradient("potential"))
{
}

Real
AlphaTimesHSize::computeValue()
{
  return fmax(1.0e5 * std::exp(1.0 - 1.0e7/(_potential_mult[_qp]*_grad_potential[_qp].size()+1.0)) - 9697.2,0.0)*_current_elem->hmax();
}
