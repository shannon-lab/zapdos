/****************************************************************/
/*							 DO NOT MODIFY THIS HEADER											*/
/* MOOSE - Multiphysics Object Oriented Simulation Environment	*/
/*																															*/
/*					 (c) 2010 Battelle Energy Alliance, LLC						 */
/*									 ALL RIGHTS RESERVED												*/
/*																															*/
/*					Prepared by Battelle Energy Alliance, LLC					 */
/*						Under Contract No. DE-AC07-05ID14517							*/
/*						With the U. S. Department of Energy							 */
/*																															*/
/*						See COPYRIGHT for full restrictions							 */
/****************************************************************/

#ifndef NEUMANNCIRCUITVOLTAGENEW_H
#define NEUMANNCIRCUITVOLTAGENEW_H

#include "NonlocalIntegratedBC.h"
#include "CurrentDensityShapeSideUserObject.h"
#include "ProvideMobility.h"

//Forward Declarations
class NeumannCircuitVoltageNew;
class Function;

template<>
InputParameters validParams<NeumannCircuitVoltageNew>();

/**
 * Boundary condition of a Neumann style whose value is computed by a user-defined function
 */
class NeumannCircuitVoltageNew : public NonlocalIntegratedBC
{
public:
	NeumannCircuitVoltageNew(const InputParameters & parameters);

protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	virtual Real computeQpOffDiagJacobian(unsigned int jvar);
	virtual Real computeQpNonlocalJacobian(dof_id_type dof_index);
	virtual Real computeQpNonlocalOffDiagJacobian(unsigned int jvar, dof_id_type dof_index);


	// Current and current density
	const CurrentDensityShapeSideUserObject & _current_uo;
	const Real & _current;
	const std::vector<Real> & _current_jac;
	std::string _surface;
	Real _current_sign;

	// Data
	const ProvideMobility & _data;

	// Coupled variables
	const std::vector<dof_id_type> & _var_dofs;

	unsigned int _em_id;
	const std::vector<dof_id_type> & _em_dofs;

	unsigned int _ip_id;
	const std::vector<dof_id_type> & _ip_dofs;

	unsigned int _mean_en_id;
	const std::vector<dof_id_type> & _mean_en_dofs;

	// System properties
	Function & _V_source;
	Real _resistance;
	Real _area;
  bool _use_area;

	// Units
	std::string _potential_units;
	Real _r_units;
	Real _voltage_scaling;

};

#endif // NEUMANNCIRCUITVOLTAGENEW_H
