//#ifndef ADDGENERALREACTIONS_H
//#define ADDGENERALREACTIONS_H
#pragma once

#include "AddVariableAction.h"
#include "Action.h"
#include "ChemicalReactionsBase.h"

class AddGeneralReactions;

template <>
InputParameters validParams<AddGeneralReactions>();

class AddGeneralReactions : public ChemicalReactionsBase
{
public:
  AddGeneralReactions(InputParameters params);

  virtual void act();

protected:
  // virtual void addEEDFReactionKernel(const std::string & var_name);
  virtual void addEEDFReactionKernel(std::vector<VariableName> potential,
                                     std::string n_e,
                                     unsigned int var_num,
                                     unsigned int rxn_num,
                                     std::string kernel_name,
                                     std::vector<SubdomainName> block);
  //virtual void addReactionCoefficient(const std::string & var_name);
  std::string _coefficient_format;
  std::vector<std::string> _aux_species;
};

//#endif // ADDZAPDOSREACTIONS_H
