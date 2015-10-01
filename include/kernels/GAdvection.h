#ifndef GADVECTION_H
#define GADVECTION_H

#include "Kernel.h"

// Forward Declaration
class GAdvection;


template<>
InputParameters validParams<GAdvection>();

class GAdvection : public Kernel
{
public:
	
	GAdvection(const InputParameters & parameters);
	
protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
	
	RealVectorValue _velocity;
	
	Real _vx;
	Real _vy;
	Real _vz;
	
private:

};

#endif // GADVECTION_H
