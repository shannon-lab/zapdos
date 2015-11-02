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

#ifndef RESIDANDJACOBTERMS_H
#define RESIDANDJACOBTERMS_H

#include "ElementUserObject.h"

//Forward Declarations
class ResidAndJacobTerms;

template<>
InputParameters validParams<ResidAndJacobTerms>();

class ResidAndJacobTerms : public ElementUserObject
{
public:
  ResidAndJacobTerms(const InputParameters & parameters);

  /* Real electrode_area() const; */

  virtual void initialize();

  virtual void execute();

  virtual void threadJoin(const UserObject & y);

  virtual void finalize();

protected:

  const VariableValue & _u;
  const VariableGradient & _grad_u;
  const MaterialProperty<Real> & _diffusivity;
  const MaterialProperty<Real> & _d_diffusivity_d_u;
  RealVectorValue _DiffusionResid;
  RealVectorValue _DiffusionJac;
  FEType _fe_type;
  const VariablePhiGradient & _grad_phi;
  const VariablePhiValue & _phi;
  unsigned int _qp;
};

#endif
