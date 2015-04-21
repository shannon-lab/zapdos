#include "HSize.h"

template<>
InputParameters validParams<HSize>()
{
  InputParameters params = validParams<AuxKernel>();

  return params;
}

HSize::HSize(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters)

{
}

Real
HSize::computeValue()
{
  return _current_elem->hmax();
}
