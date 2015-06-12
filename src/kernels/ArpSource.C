#include "ArpSource.h"

template<>
InputParameters validParams<ArpSource>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("Ars", "The excited state argon density in moles");

  return params;
}

ArpSource::ArpSource(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  // Input Parameters

  // Material Properties
  _Ar(getMaterialProperty<Real>("Ar")),

  // Coupled Variables
  _em(coupledValue("em")),
  _em_id(coupled("em")),
  _Ars(coupledValue("Ars")),
  _Ars_id(coupled("Ars")),

  // Unique to kernel

  _k4(0.0),
  _k5(0.0)
  
{
}

ArpSource::~ArpSource()
{}

Real
ArpSource::computeQpResidual()
{
  // Clean expression for reading:
  //   return -_test[_i][_qp]*(_k4*_em[_qp]*_Ar[_qp]+_k5*_em[_qp]*_Ars[_qp]);

  return -_test[_i][_qp]*(_k4*std::max(_em[_qp],0.0)*std::max(_Ar[_qp],0.0)+_k5*std::max(_em[_qp],0.0)*std::max(_Ars[_qp],0.0));
}

Real
ArpSource::computeQpJacobian()
{
  return 0.0;
}

Real
ArpSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
    {
      return -_test[_i][_qp]*(_k4*_phi[_j][_qp]*_Ar[_qp]+_k5*_phi[_j][_qp]*_Ars[_qp]);
    }
  else if (jvar == _Ars_id)
    {
      return -_test[_i][_qp]*(_k5*_em[_qp]*_phi[_j][_qp]);
    }
  else
    {
      return 0.0;
    }
}
