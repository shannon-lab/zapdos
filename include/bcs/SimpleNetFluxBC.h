#ifndef SIMPLENETFLUXBC_H
#define SIMPLENETFLUXBC_H

#include "IntegratedBC.h"


class SimpleNetFluxBC;

template<>
InputParameters validParams<SimpleNetFluxBC>();

class SimpleNetFluxBC : public IntegratedBC
{
public:

  SimpleNetFluxBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  // Input Parameters

  const Real & _x_boundary_species_current;
  const Real & _y_boundary_species_current;
  const Real & _z_boundary_species_current;

  // Material Properties

  // Members unique to object

  RealVectorValue _species_current;
};


#endif //SIMPLENETFLUXBC_H
