#ifndef BOVINEAPP_H
#define BOVINEAPP_H

#include "MooseApp.h"

class BovineApp;

template<>
InputParameters validParams<BovineApp>();

class BovineApp : public MooseApp
{
public:
  BovineApp(const std::string & name, InputParameters parameters);
  virtual ~BovineApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* BOVINEAPP_H */
