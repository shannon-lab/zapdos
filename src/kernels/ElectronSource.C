#include "ElectronSource.h"

template<>
InputParameters validParams<ElectronSource>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("Ars", "The excited state argon density in moles");

  return params;
}

ElectronSource::ElectronSource(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  // Input Parameters

  // Material Properties
  _Ar(getMaterialProperty<Real>("Ar")),

  // Coupled Variables
  _Ars(coupledValue("Ars")),
  _Ars_id(coupled("Ars")),

  // Unique to kernel

  _k4(0.0),
  _k5(0.0)
  
{
}

ElectronSource::~ElectronSource()
{}

Real
ElectronSource::computeQpResidual()
{
  // Clean expression for reading:
  //   return -_test[_i][_qp]*(_k4*_u[_qp]*_Ar[_qp]+_k5*_u[_qp]*_Ars[_qp]);n

  return -_test[_i][_qp]*(_k4*std::max(_u[_qp],0.0)*std::max(_Ar[_qp],0.0)+_k5*std::max(_u[_qp],0.0)*std::max(_Ars[_qp],0.0));
}

Real
ElectronSource::computeQpJacobian()
{
  return -_test[_i][_qp]*(_k4*_phi[_j][_qp]*_Ar[_qp]+_k5*_phi[_j][_qp]*_Ars[_qp]);
}

Real
ElectronSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _Ars_id)
    {
      return -_test[_i][_qp]*(_k5*_u[_qp]*_phi[_j][_qp]);
    }
  else
    {
      return 0.0;
    }
}
