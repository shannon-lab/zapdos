#ifndef WATER_H_
#define WATER_H_

#include "Material.h"

class Water;

template<>
InputParameters validParams<Water>();

class Water : public Material
{
 public:
  Water(const std::string & name, InputParameters parameters);

 protected:
  virtual void computeQpProperties();

  // Input Parameters

  const Real & _user_relative_permittivity;
  const Real & _user_potential_mult;
  const Real & _user_electron_mult;
  
  // Material Properties

  MaterialProperty<Real> & _eps_r;
  MaterialProperty<Real> & _e;
  MaterialProperty<Real> & _k;
  MaterialProperty<Real> & _T;
  MaterialProperty<Real> & _k1;
  MaterialProperty<Real> & _k2;
  MaterialProperty<Real> & _k3;
  MaterialProperty<Real> & _k4;
  MaterialProperty<Real> & _k5;
  MaterialProperty<Real> & _k6;
  MaterialProperty<Real> & _k7;
  MaterialProperty<Real> & _k8;
  MaterialProperty<Real> & _k9;
  MaterialProperty<Real> & _k10;
  MaterialProperty<Real> & _k11;
  MaterialProperty<Real> & _k12;
  MaterialProperty<Real> & _k13;
  MaterialProperty<Real> & _k14;
  MaterialProperty<Real> & _k15;
  MaterialProperty<Real> & _k16;
  MaterialProperty<Real> & _k17;
  MaterialProperty<Real> & _k18;
  MaterialProperty<Real> & _k19;
  MaterialProperty<Real> & _k20;
  MaterialProperty<Real> & _k21;
  MaterialProperty<Real> & _k22;
  MaterialProperty<Real> & _k23;
  MaterialProperty<Real> & _k24;
  MaterialProperty<Real> & _k25;
  MaterialProperty<Real> & _k26;
  MaterialProperty<Real> & _k27;
  MaterialProperty<Real> & _k28;
  MaterialProperty<Real> & _k29;
  MaterialProperty<Real> & _k30;
  MaterialProperty<Real> & _k31;
  MaterialProperty<Real> & _k32;
  MaterialProperty<Real> & _k33;
  MaterialProperty<Real> & _k34;
  MaterialProperty<Real> & _k35;
  MaterialProperty<Real> & _k36;
  MaterialProperty<Real> & _k37;
  MaterialProperty<Real> & _k38;
  MaterialProperty<Real> & _k39;
  MaterialProperty<Real> & _Dem;
  MaterialProperty<Real> & _DH;
  MaterialProperty<Real> & _DOHm;
  MaterialProperty<Real> & _DH2Op;
  MaterialProperty<Real> & _DOH;
  MaterialProperty<Real> & _DH2;
  MaterialProperty<Real> & _DOm;
  MaterialProperty<Real> & _DH3Op;
  MaterialProperty<Real> & _DH2O2;
  MaterialProperty<Real> & _DHO2m;
  MaterialProperty<Real> & _DO2;
  MaterialProperty<Real> & _DO2m;
  MaterialProperty<Real> & _DO;
  MaterialProperty<Real> & _DHO2;
  MaterialProperty<Real> & _DO3;
  MaterialProperty<Real> & _DO3m;
  MaterialProperty<Real> & _zem;
  MaterialProperty<Real> & _zH;
  MaterialProperty<Real> & _zOHm;
  MaterialProperty<Real> & _zH2Op;
  MaterialProperty<Real> & _zOH;
  MaterialProperty<Real> & _zH2;
  MaterialProperty<Real> & _zOm;
  MaterialProperty<Real> & _zH3Op;
  MaterialProperty<Real> & _zH2O2;
  MaterialProperty<Real> & _zHO2m;
  MaterialProperty<Real> & _zO2;
  MaterialProperty<Real> & _zO2m;
  MaterialProperty<Real> & _zO;
  MaterialProperty<Real> & _zHO2;
  MaterialProperty<Real> & _zO3;
  MaterialProperty<Real> & _zO3m;
  MaterialProperty<Real> & _muem;
  MaterialProperty<Real> & _muH;
  MaterialProperty<Real> & _muOHm;
  MaterialProperty<Real> & _muH2Op;
  MaterialProperty<Real> & _muOH;
  MaterialProperty<Real> & _muH2;
  MaterialProperty<Real> & _muOm;
  MaterialProperty<Real> & _muH3Op;
  MaterialProperty<Real> & _muH2O2;
  MaterialProperty<Real> & _muHO2m;
  MaterialProperty<Real> & _muO2;
  MaterialProperty<Real> & _muO2m;
  MaterialProperty<Real> & _muO;
  MaterialProperty<Real> & _muHO2;
  MaterialProperty<Real> & _muO3;
  MaterialProperty<Real> & _muO3m;
  MaterialProperty<Real> & _Dunity;
  MaterialProperty<Real> & _muunity;
  MaterialProperty<Real> & _munegunity;
  MaterialProperty<Real> & _electron_mult;
  MaterialProperty<Real> & _potential_mult;
};	      
		      
#endif //WATER_H
