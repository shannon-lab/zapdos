#include "HSize.h"

template<>
InputParameters validParams<HSize>()
{
  InputParameters params = validParams<AuxKernel>();

  return params;
}

HSize::HSize(const InputParameters & parameters) :
    AuxKernel(parameters)

{
}

Real
HSize::computeValue()
{
  return _current_elem->hmax();
}
