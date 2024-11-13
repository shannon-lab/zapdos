//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ShapeSideUserObject.h"

/*
 *  Calculates the total current at a boundary
 */
class CurrentDensityShapeSideUserObject : public ShapeSideUserObject
{
public:
  CurrentDensityShapeSideUserObject(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~CurrentDensityShapeSideUserObject() {}

  /**
   * This is called before execute so you can reset any internal data.
   */
  virtual void initialize();
  /**
   * Called on every "object" (like every element or node).
   * In this case, it is called at every quadrature point on every element.
   */
  virtual void execute();

  /**
   * Implement this function to compute Jacobian terms for this UserObject. The
   * shape function index _j and its corrsponding global DOF index _j_global
   * will be provided.
   */
  virtual void executeJacobian(unsigned int jvar);
  /**
   * Called _once_ after execute has been called all all "objects".
   */
  virtual void finalize();
  /**
   * Called when using threading.  You need to combine the data from "y"
   * into _this_ object.
   */
  virtual void threadJoin(const UserObject & y);

  ///@{ custom UserObject interface functions
  const Real & getIntegral() const { return _integral; }
  const std::vector<Real> & getJacobian() const { return _jacobian_storage; }
  ///@}

protected:

  /// Term that represents the value of the side integral
  Real _integral;
  /// Term that represents the Jacobian
  std::vector<Real> _jacobian_storage;

  /// Value of the electron density variable
  const VariableValue & _em;
  /// ID of the electron density variable
  unsigned int _em_id;
  /// Gradient of the electron density
  const VariableGradient & _grad_em;

  /// Ion density variable
  const MooseVariable & _ip_var;
  /// Value of the ion density variable
  const VariableValue & _ip;
  /// ID of the ion density variable
  unsigned int _ip_id;
  /// Gradient of the ion density
  const VariableGradient & _grad_ip;
  /// Gradient of the potential
  const VariableGradient & _grad_potential;
  /// ID of the potential variable
  unsigned int _potential_id;
  /// Value of the electron energy density variable
  const VariableValue & _mean_en;
  /// ID of the electron energy density variable
  unsigned int _mean_en_id;
  /// Mobility coefficient of the ions
  const ADMaterialProperty<Real> & _muip;
  /// Diffusion coefficient of the ions
  const ADMaterialProperty<Real> & _diffip;
  /// Mobility coefficient of the electrons
  const ADMaterialProperty<Real> & _muem;
  /// Diffusion coefficient of the electrons
  const ADMaterialProperty<Real> & _diffem;
  /// Elementary charge
  Real _e;
  /// True if molar density is used
  bool _use_moles;
  /// Avogadro's number
  Real _avogadro;
};
