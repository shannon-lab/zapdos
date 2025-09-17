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

/**
 *  ZAPDOS_CONSTANTS contains various constants useful in plasma modeling
 */
namespace ZAPDOS_CONSTANTS
{
/// Elementary charge
static const Real e = 1.6e-19;

/// Boltzmann constant
static const Real k_boltz = 1.38e-23;

/// Avogadro's number
static const Real N_A = 6.02e23;

/// Permittivity of free space
static const Real eps_0 = 8.85e-12;
} // namespace ZAPDOS_CONSTANTS
