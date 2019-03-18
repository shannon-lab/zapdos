#ifndef ZAPDOSAPP_H
#define ZAPDOSAPP_H

#include "MooseApp.h"

class ZapdosApp;

template <>
InputParameters validParams<ZapdosApp>();

class ZapdosApp : public MooseApp
{
public:
  ZapdosApp(InputParameters parameters);
  virtual ~ZapdosApp();

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s);
};

#endif /* ZAPDOSAPP_H */
