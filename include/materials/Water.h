#ifndef WATER_H_
#define WATER_H_

#include "Material.h"

class Water;

template<>
InputParameters validParams<Water>();

class Water : public Material
{
 public:
  Water(const InputParameters & parameters);

 protected:
  virtual void computeQpProperties();

  // Input Parameters

  const Real & _user_relative_permittivity;
  const Real & _user_potential_mult;
  const Real & _user_electron_mult;
  
  // Material Properties

  MaterialProperty<Real> & _cw;
  MaterialProperty<Real> & _electron_mult;
  MaterialProperty<Real> & _potential_mult;
  MaterialProperty<Real> & _N_A;
  MaterialProperty<Real> & _eps_r;
  MaterialProperty<Real> & _eps_0;  
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
  MaterialProperty<Real> & _rxn1;    
  MaterialProperty<Real> & _rxn2;    
  MaterialProperty<Real> & _rxn3;    
  MaterialProperty<Real> & _rxn4;    
  MaterialProperty<Real> & _rxn5;    
  MaterialProperty<Real> & _rxn6;    
  MaterialProperty<Real> & _rxn7;    
  MaterialProperty<Real> & _rxn8;    
  MaterialProperty<Real> & _rxn9;    
  MaterialProperty<Real> & _rxn10;   
  MaterialProperty<Real> & _rxn11;   
  MaterialProperty<Real> & _rxn12;   
  MaterialProperty<Real> & _rxn13;   
  MaterialProperty<Real> & _rxn14;   
  MaterialProperty<Real> & _rxn15;   
  MaterialProperty<Real> & _rxn16;   
  MaterialProperty<Real> & _rxn17;   
  MaterialProperty<Real> & _rxn18;   
  MaterialProperty<Real> & _rxn19;   
  MaterialProperty<Real> & _rxn20;   
  MaterialProperty<Real> & _rxn21;   
  MaterialProperty<Real> & _rxn22;   
  MaterialProperty<Real> & _rxn23;   
  MaterialProperty<Real> & _rxn24;   
  MaterialProperty<Real> & _rxn25;   
  MaterialProperty<Real> & _rxn26;   
  MaterialProperty<Real> & _rxn27;   
  MaterialProperty<Real> & _rxn28;   
  MaterialProperty<Real> & _rxn29;   
  MaterialProperty<Real> & _rxn30;   
  MaterialProperty<Real> & _rxn31;   
  MaterialProperty<Real> & _rxn32;   
  MaterialProperty<Real> & _rxn33;   
  MaterialProperty<Real> & _rxn34;   
  MaterialProperty<Real> & _rxn35;   
  MaterialProperty<Real> & _rxn36;   
  MaterialProperty<Real> & _rxn37;   
  MaterialProperty<Real> & _rxn38;   
  MaterialProperty<Real> & _rxn39;   
  MaterialProperty<Real> & _sem;     
  MaterialProperty<Real> & _sH;
  MaterialProperty<Real> & _sOHm;
  MaterialProperty<Real> & _sH2Op;
  MaterialProperty<Real> & _sOH;
  MaterialProperty<Real> & _sH2;
  MaterialProperty<Real> & _sOm;
  MaterialProperty<Real> & _sH3Op;
  MaterialProperty<Real> & _sH2O2;
  MaterialProperty<Real> & _sHO2m;
  MaterialProperty<Real> & _sO2;
  MaterialProperty<Real> & _sO2m;
  MaterialProperty<Real> & _sO;
  MaterialProperty<Real> & _sHO2;
  MaterialProperty<Real> & _sO3;
  MaterialProperty<Real> & _sO3m;
  MaterialProperty<Real> & _spotential;
  MaterialProperty<Real> & _Jac_em;
  MaterialProperty<Real> & _Jac_H;
  MaterialProperty<Real> & _Jac_OHm;
  MaterialProperty<Real> & _Jac_H2Op;
  MaterialProperty<Real> & _Jac_OH;
  MaterialProperty<Real> & _Jac_H2;
  MaterialProperty<Real> & _Jac_Om;
  MaterialProperty<Real> & _Jac_H3Op;
  MaterialProperty<Real> & _Jac_H2O2;
  MaterialProperty<Real> & _Jac_HO2m;
  MaterialProperty<Real> & _Jac_O2;
  MaterialProperty<Real> & _Jac_O2m;
  MaterialProperty<Real> & _Jac_O;
  MaterialProperty<Real> & _Jac_HO2;
  MaterialProperty<Real> & _Jac_O3;
  MaterialProperty<Real> & _Jac_O3m;
  MaterialProperty<Real> & _Jac_potential;

 private:

  VariableValue & _em;
  VariableValue & _H;
  VariableValue & _OHm;
  VariableValue & _H2Op;
  VariableValue & _OH;
  VariableValue & _H2;
  VariableValue & _Om;
  VariableValue & _H3Op;
  VariableValue & _H2O2;
  VariableValue & _HO2m;
  VariableValue & _O2;
  VariableValue & _O2m;
  VariableValue & _O;
  VariableValue & _HO2;
  VariableValue & _O3;
  VariableValue & _O3m;
};	      
		      
#endif //WATER_H
