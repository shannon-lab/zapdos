//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PeriodicComparisonCounter.h"
#include "FEProblem.h"

registerMooseObject("ZapdosApp", PeriodicComparisonCounter);

InputParameters
PeriodicComparisonCounter::validParams()
{
  InputParameters params = GeneralPostprocessor::validParams();

  params.addRequiredParam<PostprocessorName>("value1", "First post-processor or value");
  params.addRequiredParam<PostprocessorName>("value2", "Second post-processor or value");

  MooseEnum comparison_type("equals greater_than_equals less_than_equals greater_than less_than");
  params.addRequiredParam<MooseEnum>("comparison_type",
                                     comparison_type,
                                     "The type of comparison to perform. Options are: " +
                                         comparison_type.getRawNames());

  params.addRequiredParam<Real>("frequency", "The frequency of the periodic cycle in Hz");

  params.addClassDescription("Compares two Postprocessors or values and keeps count"
                             "of how many cycles in a row that comparision is true.");

  return params;
}

PeriodicComparisonCounter::PeriodicComparisonCounter(const InputParameters & parameters)
  : GeneralPostprocessor(parameters),
    _value1(getPostprocessorValue("value1")),
    _value2(getPostprocessorValue("value2")),
    _comparison_type(getParam<MooseEnum>("comparison_type").getEnum<ComparisonType>()),
    _period(1. / getParam<Real>("frequency")),
    _feproblem(dynamic_cast<FEProblemBase &>(_subproblem)),
    _counter(0),
    _period_counter(1.0)
{
}

void
PeriodicComparisonCounter::initialize()
{
}

void
PeriodicComparisonCounter::execute()
{
}

PostprocessorValue
PeriodicComparisonCounter::getValue() const
{
  return _counter;
}

void
PeriodicComparisonCounter::finalize()
{
  Real remainder = std::remainder(_feproblem.time(), _period);
  Real max = std::numeric_limits<double>::epsilon();
  Real min = -std::numeric_limits<double>::epsilon();

  if ((remainder >= min) && (remainder <= max))
  {
    _period_counter++;

    switch (_comparison_type)
    {
      case ComparisonType::EQUALS:
        if (_value1 == _value2)
          _counter++;
        else
          _counter = 0.0;
        break;
      case ComparisonType::GREATER_THAN_EQUALS:
        if (_value1 >= _value2)
          _counter++;
        else
          _counter = 0.0;
        break;
      case ComparisonType::LESS_THAN_EQUALS:
        if (_value1 <= _value2)
          _counter++;
        else
          _counter = 0.0;
        break;
      case ComparisonType::GREATER_THAN:
        if (_value1 > _value2)
          _counter++;
        else
          _counter = 0.0;
        break;
      case ComparisonType::LESS_THAN:
        if (_value1 < _value2)
          _counter++;
        else
          _counter = 0.0;
        break;
      default:
        mooseError("Invalid comparison type.");
    }
  }
}
