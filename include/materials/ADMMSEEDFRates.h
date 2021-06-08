/****************************************************************/
/*                      DO NOT MODIFY THIS HEADER               */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*              (c) 2010 Battelle Energy Alliance, LLC          */
/*                      ALL RIGHTS RESERVED                     */
/*                                                              */
/*              Prepared by Battelle Energy Alliance, LLC       */
/*              Under Contract No. DE-AC07-05ID14517            */
/*              With the U. S. Department of Energy             */
/*                                                              */
/*              See COPYRIGHT for full restrictions             */
/****************************************************************/
#pragma once

#include "ADMaterial.h"

class ADMMSEEDFRates : public ADMaterial
{
public:
  static InputParameters validParams();
  ADMMSEEDFRates(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

  const ADVariableValue & _em;
  const ADVariableValue & _mean_en;

  std::vector<std::string> _prop_names;
  std::vector<FunctionName> _prop_values;
  std::vector<FunctionName> _d_prop_values_actual_mean_en;

  unsigned int _num_props;

  std::vector<ADMaterialProperty<Real> *> _properties;
  std::vector<const Function *> _functions;
  std::vector<const Function *> _deriv_functions;

  using ADMaterial::_communicator;

private:
  /**
   * A helper method for evaluating the functions
   */
  void computeQpFunctions();
};
