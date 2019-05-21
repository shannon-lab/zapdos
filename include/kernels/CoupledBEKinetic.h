//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Kernel.h"

#ifndef COUPLEDBEKINETIC_H
#define COUPLEDBEKINETIC_H

// Forward Declarations
class CoupledBEKinetic;

template <>
InputParameters validParams<CoupledBEKinetic>();

/**
 * Define the Kernel for a CoupledBEKinetic operator that looks like:
 *
 * delta (weight * v) / delta t.
 */
class CoupledBEKinetic : public Kernel
{
public:
  CoupledBEKinetic(const InputParameters & parameters);

protected:
  /**
   * Responsible for computing the residual at one quadrature point
   * This should always be defined in the .C
   * @return The residual of mass accumulation of the coupled kinetic mineral species concentration.
   */
  virtual Real computeQpResidual();
  /**
   * Responsible for computing the diagonal block of the preconditioning matrix.
   * This is essentially the partial derivative of the residual with respect to
   * the variable this kernel operates on ("u").
   *
   * Note that this can be an approximation or linearization.  In this case it's
   * not because the Jacobian of this operator is easy to calculate.
   *
   * This should always be defined in the .C
   * @return The diagonal jacobian of mass accumulation of the coupled kinetic mineral species
   * concentration.
   */
  virtual Real computeQpJacobian();
  //  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  /// Material property of porosity.
  const MaterialProperty<Real> & _porosity;

  /// Weight of the kinetic mineral concentration in the total primary species concentration.
  std::vector<Real> _weight;
  //  std::vector<unsigned int> _vars;
  /// Coupled kinetic mineral concentrations.
  std::vector<VariableValue *> _vals;
  /// Coupled old values of kinetic mineral concentrations.
  std::vector<VariableValue *> _vals_old;
};
#endif // COUPLEDBEKINETIC_H
