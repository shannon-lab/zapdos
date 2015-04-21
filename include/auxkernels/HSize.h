#ifndef HSIZE_H
#define HSIZE_H

#include "AuxKernel.h"

//Forward Declarations
class HSize;

template<>
InputParameters validParams<HSize>();

/**
 * Constant auxiliary value
 */
class HSize : public AuxKernel
{
public:
  HSize(const std::string & name, InputParameters parameters);

  virtual ~HSize() {}

protected:

  virtual Real computeValue();

};

#endif //HSIZE_H
