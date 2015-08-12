#include "ArsSource.h"

template<>
InputParameters validParams<ArsSource>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("Te", "The mean electron energy");

  return params;
}

ArsSource::ArsSource(const InputParameters & parameters) :
  Kernel(parameters),

  // Input Parameters

  // Material Properties
  _k6(getMaterialProperty<Real>("k6")),
  _k7(getMaterialProperty<Real>("k7")),
  _Ar(getMaterialProperty<Real>("Ar")),

  // Coupled Variables
  _em(coupledValue("em")),
  _em_id(coupled("em")),
  _Te(coupledValue("Te")),
  _Te_id(coupled("Te")),

  // Unique to kernel

  _k2(0.0),
  _k3(0.0),
  _k5(0.0),
  _dk2_dTe(0.0),
  _dk3_dTe(0.0),
  _dk5_dTe(0.0)
{
}

ArsSource::~ArsSource()
{}

Real
ArsSource::computeQpResidual()
{
  // Clean expression for reading:

  _k2 = 5.0e-15*std::pow(std::max(_Te[_qp],1e-6),0.74)*std::exp(-11.56/(_Te[_qp]+1e-6)); // Electron impact excitation of ground state argon to create Ars (Ar(4s) in Liebermans text)
  _k3 = 4.3e-16*std::pow(std::max(_Te[_qp],1e-6),0.74); // Electron impact dexcitation of Ars (Ar(4s) in Liebermans text)
  _k5 = 6.8e-15*std::pow(std::max(_Te[_qp],1e-6),0.67)*std::exp(-4.20/(_Te[_qp]+1e-6));

  return -_test[_i][_qp]*(_k2*std::max(_Ar[_qp],0.0)*std::max(std::max(_em[_qp],1.0),0.0)-_k3*std::max(std::max(_em[_qp],1.0),0.0)*std::max(_u[_qp],0.0)-_k5*std::max(std::max(_em[_qp],1.0),0.0)*std::max(_u[_qp],0.0)-_k6[_qp]*std::max(_Ar[_qp],0.0)*std::max(_u[_qp],0.0)-_k7[_qp]*std::pow(_u[_qp],2));
}

Real
ArsSource::computeQpJacobian()
{
  return -_test[_i][_qp]*(-_k3*std::max(_em[_qp],1.0)*_phi[_j][_qp]-_k5*std::max(_em[_qp],1.0)*_phi[_j][_qp]-_k6[_qp]*_Ar[_qp]*_phi[_j][_qp]-_k7[_qp]*2.0*_u[_qp]*_phi[_j][_qp]);
}

Real
ArsSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  _k2 = 5.0e-15*std::pow(std::max(_Te[_qp],1e-6),0.74)*std::exp(-11.56/(_Te[_qp]+1e-6)); // Electron impact excitation of ground state argon to create Ars (Ar(4s) in Liebermans text)
  _k3 = 4.3e-16*std::pow(std::max(_Te[_qp],1e-6),0.74); // Electron impact dexcitation of Ars (Ar(4s) in Liebermans text)
  _k5 = 6.8e-15*std::pow(std::max(_Te[_qp],1e-6),0.67)*std::exp(-4.20/(_Te[_qp]+1e-6));
  _dk2_dTe = 5.78e-14*std::pow(std::max(_Te[_qp],1e-6),-1.26)*std::exp(-11.56/(_Te[_qp]+1e-6))+3.7e-15*std::pow(std::max(_Te[_qp],1e-6),-0.26)*std::exp(-11.56/(_Te[_qp]+1e-6));
  _dk3_dTe = 3.182e-16*std::pow(std::max(_Te[_qp],1e-6),-0.26);
  _dk5_dTe = 2.856e-14*std::pow(std::max(_Te[_qp],1e-6),-1.33)*std::exp(-4.2/(_Te[_qp]+1e-6))+4.556e-15*std::pow(std::max(_Te[_qp],1e-6),-0.33)*std::exp(-4.2/(_Te[_qp]+1e-6));

  // Easy-to-read residual
  //   return -_test[_i][_qp]*(_k2*_Ar[_qp]*std::max(_em[_qp],1.0)-_k3*std::max(_em[_qp],1.0)*_u[_qp]-_k5*std::max(_em[_qp],1.0)*_u[_qp]-_k6[_qp]*_Ar[_qp]*_u[_qp]-_k7[_qp]*std::pow(_u[_qp],2));
  // Rate constands depending on Te: k2, k3, k5

  if (jvar == _em_id)
    {
      return -_test[_i][_qp]*(_k2*_Ar[_qp]*_phi[_j][_qp]-_k3*_phi[_j][_qp]*_u[_qp]-_k5*_phi[_j][_qp]*_u[_qp]);
    }
  else if (jvar == _Te_id)
    {
      //      std::cout << "In the Te off-diagonal calculations for u = Ars" << std::endl;
      return -_test[_i][_qp]*(_Ar[_qp]*std::max(_em[_qp],1.0)*_dk2_dTe*_phi[_j][_qp]-std::max(_em[_qp],1.0)*_u[_qp]*_dk3_dTe*_phi[_j][_qp]-_k5*std::max(_em[_qp],1.0)*_u[_qp]*_dk5_dTe*_phi[_j][_qp]);
    }
  else
    {
      return 0.0;
    }
}
