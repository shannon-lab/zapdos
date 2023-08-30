//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AverageNodalDensity.h"
#include "MooseMesh.h"
#include "SubProblem.h"

registerMooseObject("ZapdosApp", AverageNodalDensity);

InputParameters
AverageNodalDensity::validParams()
{
  InputParameters params = NodalVariablePostprocessor::validParams();

  params.addClassDescription("Similar to AverageNodalVariableValue except meant to "
                             "average variables expressed in log form");
  return params;
}

AverageNodalDensity::AverageNodalDensity(const InputParameters & parameters)
  : NodalVariablePostprocessor(parameters), _sum(0), _n(0)
{
}

void
AverageNodalDensity::initialize()
{
  _sum = 0;
  _n = 0;
}

void
AverageNodalDensity::execute()
{
  _sum += std::exp(_u[_qp]);
  _n++;
}

PostprocessorValue
AverageNodalDensity::getValue() const
{
  return _sum / _n;
}

void
AverageNodalDensity::finalize()
{
  gatherSum(_sum);
  gatherSum(_n);
}

void
AverageNodalDensity::threadJoin(const UserObject & y)
{
  const AverageNodalDensity & pps = static_cast<const AverageNodalDensity &>(y);
  _sum += pps._sum;
  _n += pps._n;
}
