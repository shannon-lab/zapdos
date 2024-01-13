//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ZapdosTestApp.h"
#include "MooseMain.h"

// Begin the main program.
int main(int argc, char *argv[])
{
  Moose::main<ZapdosTestApp>(argc, argv);

  return 0;
}
