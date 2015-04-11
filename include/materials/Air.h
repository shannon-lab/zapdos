/* #ifndef AIR_H_
#define AIR_H_

#include "Material.h"

class Air;

template<>
InputParameters validParams<Air>();

class Air : public Material
{
public:
  Air(const std::string & name, InputParameters parameters);
  
protected:
  virtual void computeQpProperties();
  
  const */
