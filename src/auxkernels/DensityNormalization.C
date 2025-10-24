//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DensityNormalization.h"

registerMooseObject("ZapdosApp", DensityNormalization);

InputParameters
DensityNormalization::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("density", "The variable to be normalized in log form");
  params.addRequiredParam<PostprocessorName>("normalization",
                                             "The postprocessor to be the denominator");
  params.addParam<PostprocessorName>("shift", "The postprocessor to shift the source");
  params.addParam<Real>("normal_factor", 1.0, "The normalization factor");
  params.addClassDescription("Similar to NormalizationAux except meant to "
                             "normalize variables expressed in log form");
  return params;
}

DensityNormalization::DensityNormalization(const InputParameters & parameters)
  : AuxKernel(parameters),
    _density(coupledValue("density")),
    _pp_on_source(&getPostprocessorValue("normalization")),
    _shift(isParamValid("shift") ? &getPostprocessorValue("shift") : NULL),
    _normal_factor(getParam<Real>("normal_factor"))
{
}

Real
DensityNormalization::computeValue()
{
  Real denominator = *_pp_on_source;
  Real shift = _shift ? *_shift : 0.0;
  return std::exp(_density[_qp]) * _normal_factor / denominator - shift;
}
