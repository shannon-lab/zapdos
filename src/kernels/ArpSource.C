#include "ArpSource.h"

template<>
InputParameters validParams<ArpSource>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addCoupledVar("Ars", "The excited state argon density in moles");
  params.addRequiredCoupledVar("Te", "The mean electron energy");

  return params;
}

ArpSource::ArpSource(const InputParameters & parameters) :
  Kernel(parameters),

  // Input Parameters

  // Material Properties
  _Ar(getMaterialProperty<Real>("Ar")),

  // Coupled Variables
  _em(coupledValue("em")),
  _em_id(coupled("em")),
  _Ars(isCoupled("Ars") ? coupledValue("Ars") : _zero),
  _Ars_id(isCoupled("Ars") ? coupled("Ars") : 0),
  _Te(coupledValue("Te")),
  _Te_id(coupled("Te")),

  // Unique to kernel

  _k_4(0.0),
  _k_5(0.0),
  _dk4_dTe(0.0),
  _dk5_dTe(0.0)
{
  ArsCoupling = isCoupled("Ars");
}

ArpSource::~ArpSource()
{}

Real
ArpSource::computeQpResidual()
{
  // Clean expression for reading:
  //   return -_test[_i][_qp]*(_k_4*std::max(_em[_qp],1.0)*_Ar[_qp]+_k_5*std::max(_em[_qp],1.0)*_Ars[_qp]);
  //  _k_4 = 2.34e-14*std::pow(std::max(_Te[_qp],1e-6),0.59)*std::exp(-17.44/(_Te[_qp]+1e-6));
  _k_4 = 5e-14*std::exp(-15.76/(std::max(_Te[_qp],1e-16)));

  if (ArsCoupling)
    _k_5 = 6.8e-15*std::pow(std::max(_Te[_qp],1e-6),0.67)*std::exp(-4.20/(_Te[_qp]+1e-6));
  else
    _k_5 = 0.0;

  return -_test[_i][_qp]*(_k_4*std::max(std::max(_em[_qp],1.0),0.0)*std::max(_Ar[_qp],0.0)+_k_5*std::max(std::max(_em[_qp],1.0),0.0)*std::max(_Ars[_qp],0.0));
}

Real
ArpSource::computeQpJacobian()
{
  return 0.0;
}

Real
ArpSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  /*  _k_4 = 2.34e-14*std::pow(std::max(_Te[_qp],1e-6),0.59)*std::exp(-17.44/(_Te[_qp]+1e-6));
      _dk4_dTe = 4.08096e-13*std::pow(std::max(_Te[_qp],1e-6),-1.41)*std::exp(-17.44/(_Te[_qp]+1e-6))+1.3806e-14*std::pow(std::max(_Te[_qp],1e-6),-0.41)*std::exp(-17.44/(_Te[_qp]+1e-6));*/
  _k_4 = 5e-14*std::exp(-15.76/(std::max(_Te[_qp],1e-16)));
  _dk4_dTe = 7.88e-13*std::exp(-15.76/std::max(_Te[_qp],1e-16))/std::max(std::pow(_Te[_qp],2),1e-16);

  if (ArsCoupling) 
    {
      _k_5 = 6.8e-15*std::pow(std::max(_Te[_qp],1e-6),0.67)*std::exp(-4.20/(_Te[_qp]+1e-6));
      _dk5_dTe = 2.856e-14*std::pow(std::max(_Te[_qp],1e-6),-1.33)*std::exp(-4.2/(_Te[_qp]+1e-6))+4.556e-15*std::pow(std::max(_Te[_qp],1e-6),-0.33)*std::exp(-4.2/(_Te[_qp]+1e-6));
    }
  else
    {
      _k_5 = 0.0;
      _dk5_dTe = 0.0;
    }

  if (jvar == _em_id)
    {
      return -_test[_i][_qp]*(_k_4*_phi[_j][_qp]*_Ar[_qp]+_k_5*_phi[_j][_qp]*_Ars[_qp]);
    }
  else if (ArsCoupling && jvar == _Ars_id)
    {
      return -_test[_i][_qp]*(_k_5*std::max(_em[_qp],1.0)*_phi[_j][_qp]);
    }
  else if (jvar == _Te_id)
    {
      return -_test[_i][_qp]*(std::max(_em[_qp],1.0)*_Ar[_qp]*_dk4_dTe*_phi[_j][_qp]+std::max(_em[_qp],1.0)*_Ars[_qp]*_dk5_dTe*_phi[_j][_qp]);
    }
  else
    {
      return 0.0;
    }
}
