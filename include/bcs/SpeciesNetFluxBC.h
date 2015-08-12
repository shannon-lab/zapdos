#ifndef SPECIESNETFLUXBC_H
#define SPECIESNETFLUXBC_H

#include "IntegratedBC.h"


class SpeciesNetFluxBC;

template<>
InputParameters validParams<SpeciesNetFluxBC>();

class SpeciesNetFluxBC : public IntegratedBC
{
public:

  SpeciesNetFluxBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  // Input Parameters

  const Real & _x_boundary_species_current;
  const Real & _y_boundary_species_current;
  const Real & _z_boundary_species_current;

  // Material Properties

  const MaterialProperty<Real> & _species_charge;
  const MaterialProperty<Real> & _coulomb_charge;
  const MaterialProperty<Real> & _electron_mult;
  const MaterialProperty<Real> & _N_A;

  // Members unique to object

  RealVectorValue _species_current;
};


#endif //SPECIESNETFLUXBC_H
