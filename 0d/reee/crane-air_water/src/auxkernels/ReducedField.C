#include "ReducedField.h"
#include "MooseUtils.h"

registerMooseObject("CraneApp", ReducedField);

template <>
InputParameters
validParams<ReducedField>()
{
 InputParameters params = validParams<AuxScalarKernel>();
 params.addCoupledVar("electron_mobility", "The electron mobility.");
 params.addCoupledVar("electron_density", "The electron density.");
 params.addCoupledVar("gas_density", "The gas density.");
 return params;
}

ReducedField::ReducedField(const InputParameters & parameters)
 : AuxScalarKernel(parameters),
  _mobility(coupledScalarValue("electron_mobility"))
{
}

ReducedField::~ReducedField() {}

Real
ReducedField::computeValue()
{
  return 1.0;
 // return _mobility.sample(_reduced_field[_i]);
}
