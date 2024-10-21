#pragma once

#include "AuxScalarKernel.h"
#include "FunctionParserUtils.h"

// Forward Declarations
class ParsedAuxScalar;

template <>
InputParameters validParams<ParsedAuxScalar>();

/**
 * AuxKernel that evaluates a parsed function expression
 */
class ParsedAuxScalar : public AuxScalarKernel, public FunctionParserUtils
{
public:
  ParsedAuxScalar(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  /// function expression
  std::string _function;

  /// coupled variables
  unsigned int _nargs;
  std::vector<const VariableValue *> _args;

  /// function parser object for the resudual and on-diagonal Jacobian
  ADFunctionPtr _func_F;
};
