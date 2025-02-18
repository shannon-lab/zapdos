//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADMaterial.h"

/**
 *  Add material properties used for MMS verifications involving
    properties as a function of electron mean energy.
 */
class ADMMSEEDFRates : public ADMaterial
{
public:
  static InputParameters validParams();
  ADMMSEEDFRates(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

  /// Electron density
  const ADVariableValue & _em;
  /// Electron mean energy density
  const ADVariableValue & _mean_en;

  /// Name of material properties
  const std::vector<std::string> _prop_names;
  /// Name of functions representing property values
  const std::vector<FunctionName> _prop_values;
  /// Name of functions representing derivative of the property values wrt the electron mean energy
  const std::vector<FunctionName> _d_prop_values_actual_mean_en;

  /// Number of named material properties
  unsigned int _num_props;

  /// Material properties
  std::vector<ADMaterialProperty<Real> *> _properties;
  /// Functions of material properties
  std::vector<const Function *> _functions;
  /// Functions of derivatives of material properties
  std::vector<const Function *> _deriv_functions;

  using ADMaterial::_communicator;

private:
  /**
   * A helper method for evaluating the functions
   */
  void computeQpFunctions();
};
