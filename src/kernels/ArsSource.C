#include "ArsSource.h"

template<>
InputParameters validParams<ArsSource>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");

  return params;
}

ArsSource::ArsSource(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  // Input Parameters

  // Material Properties
  _k6(getMaterialProperty<Real>("k6")),
  _k7(getMaterialProperty<Real>("k7")),
  _Ar(getMaterialProperty<Real>("Ar")),

  // Coupled Variables
  _em(coupledValue("em")),
  _em_id(coupled("em")),

  // Unique to kernel

  _k2(0.0),
  _k3(0.0),
  _k5(0.0)
  
{
}

ArsSource::~ArsSource()
{}

Real
ArsSource::computeQpResidual()
{
  // Clean expression for reading:
  //   return -_test[_i][_qp]*(_k2*_Ar[_qp]*_em[_qp]-_k3*_em[_qp]*_u[_qp]-_k5*_em[_qp]*_u[_qp]-_k6[_qp]*_Ar[_qp]*_u[_qp]-_k7[_qp]*std::pow(_u[_qp],2));

  return -_test[_i][_qp]*(_k2*std::max(_Ar[_qp],0.0)*std::max(_em[_qp],0.0)-_k3*std::max(_em[_qp],0.0)*std::max(_u[_qp],0.0)-_k5*std::max(_em[_qp],0.0)*std::max(_u[_qp],0.0)-_k6[_qp]*std::max(_Ar[_qp],0.0)*std::max(_u[_qp],0.0)-_k7[_qp]*std::pow(_u[_qp],2));
}

Real
ArsSource::computeQpJacobian()
{
  return -_test[_i][_qp]*(-_k3*_em[_qp]*_phi[_j][_qp]-_k5*_em[_qp]*_phi[_j][_qp]-_k6[_qp]*_Ar[_qp]*_phi[_j][_qp]-_k7[_qp]*2.0*_u[_qp]*_phi[_j][_qp]);
}

Real
ArsSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
    {
      return -_test[_i][_qp]*(_k2*_Ar[_qp]*_phi[_j][_qp]-_k3*_phi[_j][_qp]*_u[_qp]-_k5*_phi[_j][_qp]*_u[_qp]);
    }
  else
    {
      return 0.0;
    }
}
