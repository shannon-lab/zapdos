/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#pragma once

#include "AuxScalarKernel.h"
#include "FunctionParserUtils.h"
// #include "ValueProvider.h"

// Forward Declarations
class ParsedScalarRateCoefficient;

template <>
InputParameters validParams<ParsedScalarRateCoefficient>();

/**
 * Constant auxiliary value
 */
class ParsedScalarRateCoefficient : public AuxScalarKernel, public FunctionParserUtils
{
public:
  ParsedScalarRateCoefficient(const InputParameters & parameters);

  virtual ~ParsedScalarRateCoefficient() {}

protected:
  /**
   * AuxKernels MUST override computeValue.  computeValue() is called on
   * every quadrature point.  For Nodal Auxiliary variables those quadrature
   * points coincide with the nodes.
   */
  virtual Real computeValue() override;

  std::string _function;

  unsigned int _nargs;
  std::vector<const VariableValue *> _args;
  const VariableValue & _reduced_field;
  std::vector<std::string> _constant_names;
  std::vector<std::string> _constant_expressions;
  // const ValueProvider & _data;

  ADFunctionPtr _func_F;
};
