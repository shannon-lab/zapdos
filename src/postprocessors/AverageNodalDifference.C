//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AverageNodalDifference.h"
#include "FEProblem.h"

registerMooseObject("ZapdosApp", AverageNodalDifference);

InputParameters
AverageNodalDifference::validParams()
{
  InputParameters params = NodalVariablePostprocessor::validParams();
  params.addRequiredCoupledVar("other_variable", "The variable to compare to.");
  params.addClassDescription("Returns the average nodal differences between two variables");
  params.set<bool>("unique_node_execute") = true;
  return params;
}

AverageNodalDifference::AverageNodalDifference(const InputParameters & parameters)
  : NodalVariablePostprocessor(parameters),
    _other_var(coupledValue("other_variable")),
    _sum_of_squared_diff(0.0),
    _n(0),
    _value(0)
{
}

void
AverageNodalDifference::initialize()
{
  _sum_of_squared_diff = 0.0;
  _n = 0;
}

void
AverageNodalDifference::execute()
{
  Real val = _u[_qp];
  Real other_val = _other_var[_qp];

  _sum_of_squared_diff += (val - other_val) * (val - other_val);
  _n++;
}

PostprocessorValue
AverageNodalDifference::getValue() const
{
  return _value;
}

void
AverageNodalDifference::finalize()
{
  gatherSum(_sum_of_squared_diff);
  gatherSum(_n);

  _value = std::sqrt(_sum_of_squared_diff / (_n * _n));
}

void
AverageNodalDifference::threadJoin(const UserObject & y)
{
  const AverageNodalDifference & pps = static_cast<const AverageNodalDifference &>(y);
  _sum_of_squared_diff += pps._sum_of_squared_diff;
  _n += pps._n;
}
