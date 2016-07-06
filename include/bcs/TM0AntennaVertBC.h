#ifndef TM0ANTENNAVERTBC_H
#define TM0ANTENNAVERTBC_H

#include "IntegratedBC.h"

class TM0AntennaVertBC;

template<>
InputParameters validParams<TM0AntennaVertBC>();

class TM0AntennaVertBC : public IntegratedBC
{
public:

  TM0AntennaVertBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _omega;
  Real _eps_r;
  Real _eps0;
  bool _time_dependent;
};

#endif //TM0ANTENNAVERTBC_H
