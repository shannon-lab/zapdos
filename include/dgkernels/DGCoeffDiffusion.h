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

#include "ADDGKernel.h"

/**
 * DG kernel for diffusion
 *
 * General DG kernel that this class can handle is:
 * \f$ { \nabla u * n_e} [v] + epsilon { \nabla v * n_e } [u] + (sigma / |e| * [u][v]) \f$
 *
 * \f$ [a] = [ a_1 - a_2 ] \f$
 * \f$ {a} = 0.5 * (a_1 + a_2) \f$
 *
 */
class DGCoeffDiffusion : public ADDGKernel
{
public:
  static InputParameters validParams();

  DGCoeffDiffusion(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual(Moose::DGResidualType type) override;

  /*
   *   _epsilon and _sigma (as described above) are used to penalize the jumps
   *   in discontinuity between cells. More information can be found in "Discontinuous
   *   Galerkin Methods for Solving Elliptic and Parabolic Equations: Theory
   *   and Implementation" by B. Rivière
   */
  const Real _epsilon;
  const Real _sigma;
  /// Diffusion coefficient of current cell
  const ADMaterialProperty<Real> & _diff;
  /// Diffusion coefficient of neighboring cell
  const ADMaterialProperty<Real> & _diff_neighbor;
};
