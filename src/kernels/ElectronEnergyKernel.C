#include "ElectronEnergyKernel.h"

template<>
InputParameters validParams<ElectronEnergyKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("potential","The electric potential");

  return params;
}

ElectronEnergyKernel::ElectronEnergyKernel(const InputParameters & parameters) :
  Kernel(parameters),

  _em(coupledValue("em")),
  _grad_em(coupledGradient("em")),
  _em_id(coupled("em")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("em")),

  // Material properties

  _muel(getMaterialProperty<Real>("muel")),
  _muem(getMaterialProperty<Real>("muem")),
  _diffem(getMaterialProperty<Real>("diffem")),
  _diffel(getMaterialProperty<Real>("diffel")),
  _Ar(getMaterialProperty<Real>("Ar")),
  _mem(getMaterialProperty<Real>("mem")),
  _mip(getMaterialProperty<Real>("mip")),
  _Eiz_en(getMaterialProperty<Real>("Eiz_en")),
  _rate_coeff_ion_en(getMaterialProperty<Real>("rate_coeff_ion_en")),
  _rate_coeff_elastic(getMaterialProperty<Real>("rate_coeff_elastic")),
  _N_A(getMaterialProperty<Real>("N_A"))

// Kernel members

  // _alpha(0.0),
  // _Pe(0.0),
  // _vd_mag(0.0),
  // _delta(0.0)
{}

ElectronEnergyKernel::~ElectronEnergyKernel()
{}

Real
ElectronEnergyKernel::computeQpResidual()
{
  // _vd_mag = std::abs(_muel[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffel[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muel[_qp]*-_grad_potential[_qp] // Advective motion
  						 -_diffel[_qp]*_grad_u[_qp]) // Diffusive motion
    +_test[_i][_qp]*-_grad_potential[_qp]*(-_muem[_qp]*std::exp(_em[_qp])*-_grad_potential[_qp] // Joule Heating
  						-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]) // Joule Heating
 -_test[_i][_qp]*_rate_coeff_ion_en[_qp]*std::exp(-_Eiz_en[_qp]/(2.0/3*std::exp(_u[_qp]-_em[_qp])))*_Ar[_qp]*std::exp(_em[_qp])*-_Eiz_en[_qp] // Energy loss from ionization. Reaction rate formulation
         -_test[_i][_qp]*-_rate_coeff_elastic[_qp]*_Ar[_qp]*3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp]) // Energy loss from elastic collisions
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp]); // Source stabilization
  	 // -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
ElectronEnergyKernel::computeQpJacobian()
{
  // _vd_mag = std::abs(_muel[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffel[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  
  return  -_grad_test[_i][_qp]*(-_muel[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp] // Advective motion
  			       -_diffel[_qp]*_grad_phi[_j][_qp]*std::exp(_u[_qp])-_diffel[_qp]*_grad_u[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]) // Diffusive motion
    +_test[_i][_qp]*3.0/2*_Ar[_qp]*std::pow(_Eiz_en[_qp],2)*_rate_coeff_ion_en[_qp]*std::exp(_em[_qp])*std::exp(-3.0/2*_Eiz_en[_qp]*std::exp(_em[_qp]-_u[_qp]))*std::exp(_em[_qp]-_u[_qp])*_phi[_j][_qp] // Energy loss from ionization
         -_test[_i][_qp]*-_rate_coeff_elastic[_qp]*_Ar[_qp]*3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp])*_phi[_j][_qp] // Energy loss from elastic collisions
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp])*-1.0*_phi[_j][_qp]; // Source stabilization
  	 // -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

Real
ElectronEnergyKernel::computeQpOffDiagJacobian(unsigned int jvar)
{

  if (jvar == _potential_id) {
    return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muel[_qp]*-_grad_phi[_j][_qp]); // Advective motion
           +_test[_i][_qp]*(-_grad_phi[_j][_qp]*(-_muem[_qp]*std::exp(_em[_qp])*-_grad_potential[_qp] // Joule Heating
    						 -_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]) // Joule Heating
    			    -_grad_potential[_qp]*(-_muem[_qp]*std::exp(_em[_qp])*-_grad_phi[_j][_qp])); // Joule Heating
  }

  else if (jvar == _em_id) {
  
    return +_test[_i][_qp]*-_grad_potential[_qp]*(-_muem[_qp]*std::exp(_em[_qp])*_phi[_j][_qp]*-_grad_potential[_qp] // Joule Heating
    						  -_diffem[_qp]*(std::exp(_em[_qp])*_grad_phi[_j][_qp]+std::exp(_em[_qp])*_phi[_j][_qp]*_grad_em[_qp])) // Joule Heating
      -_test[_i][_qp]*3.0/2*_Ar[_qp]*std::pow(_Eiz_en[_qp],2)*_rate_coeff_ion_en[_qp]*std::exp(_em[_qp])*std::exp(-3.0/2*_Eiz_en[_qp]*std::exp(_em[_qp]-_u[_qp]))*std::exp(_em[_qp]-_u[_qp])*_phi[_j][_qp] // Energy loss from ionization
      +_test[_i][_qp]*_Ar[_qp]*_Eiz_en[_qp]*_rate_coeff_ion_en[_qp]*std::exp(_em[_qp])*std::exp(-3.0/2*_Eiz_en[_qp]*std::exp(_em[_qp]-_u[_qp]))*_phi[_j][_qp]; // Energy loss from ionization
   }

  else {
    return 0.0;
  }

}
