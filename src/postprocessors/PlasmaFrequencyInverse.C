//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PlasmaFrequencyInverse.h"

#include <algorithm>
#include <limits>

registerMooseObject("ZapdosApp", PlasmaFrequencyInverse);

template <>
InputParameters
validParams<PlasmaFrequencyInverse>()
{

  // Define the parameters
  InputParameters params = validParams<ElementVariablePostprocessor>();
  params.addRequiredParam<bool>("use_moles",
                                "Whether to use units of moles as opposed to # of molecules.");

  return params;
}

PlasmaFrequencyInverse::PlasmaFrequencyInverse(const InputParameters & parameters)
  : ElementVariablePostprocessor(parameters),
    _value(-std::numeric_limits<Real>::max()),
    _em_density(0),
    _use_moles(getParam<bool>("use_moles"))
{
}

void
PlasmaFrequencyInverse::initialize()
{

      _value = -std::numeric_limits<Real>::max(); // start w/ the min

}

void
PlasmaFrequencyInverse::computeQpValue()
{

      _value = std::max(_value, _u[_qp]);
}

Real
PlasmaFrequencyInverse::getValue()
{

      gatherMax(_value);

      if (_use_moles)
      {
        _em_density = std::exp(_value) * 6.022e23;
      }
      else
      {
        _em_density = std::exp(_value);
      }

      Real _plasma_freq = std::sqrt(std::pow(1.6022e-19,2) * _em_density / (8.8542e-12 * 9.1094e-31));

  return 1. / _plasma_freq;
}

void
PlasmaFrequencyInverse::threadJoin(const UserObject & y)
{
  const PlasmaFrequencyInverse & pps = static_cast<const PlasmaFrequencyInverse &>(y);

      _value = std::max(_value, pps._value);

}
