#include "SpeciesSum.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", SpeciesSum);

template <>
InputParameters
validParams<SpeciesSum>()
{
  InputParameters params = validParams<Material>();
  params.addCoupledVar("coupled_vars", "The coupled variables to sum.");
  return params;
}

SpeciesSum::SpeciesSum(const InputParameters & parameters)
  : Material(parameters),
  _total_sum(declareProperty<Real>("species_sum"))
{
  int n = coupledComponents("coupled_vars");

  _vals.resize(n);

  for (unsigned int i=0; i<_vals.size(); ++i)
  {
    _vals[i] = &coupledValue("coupled_vars", i);
  }
}

void
SpeciesSum::computeQpProperties()
{
  _total_sum[_qp] = 0.0;
  for (unsigned int i=0; i<_vals.size(); ++i)
  {
    _total_sum[_qp] += (*_vals[i])[_qp];
  }
}
