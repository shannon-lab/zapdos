#ifndef BOVINEAPP_H
#define BOVINEAPP_H

#include "MooseApp.h"

class ZapdosApp;

template<>
InputParameters validParams<ZapdosApp>();

class ZapdosApp : public MooseApp
{
public:
  ZapdosApp(InputParameters parameters);
  virtual ~ZapdosApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* BOVINEAPP_H */
