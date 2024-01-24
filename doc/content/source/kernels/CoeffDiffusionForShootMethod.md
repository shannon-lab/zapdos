# CoeffDiffusionForShootMethod

!syntax description /Kernels/CoeffDiffusionForShootMethod

## Overview

`CoeffDiffusionForShootMethod` is the derivative of the generic diffusion term [CoeffDiffusion.md] used to calculate
the sensitivity value for the shoothing method. For more information on the implementation of the shoothing method within Zapdos, please reference to [ShootMethodLog.md].

## Example Input File Syntax

An example of how to use `CoeffDiffusionForShootMethod` can be found in the
test file `Acceleration_By_Shooting_Method_SensitivityMatrix.i`.

!listing test/tests/accelerations/Acceleration_By_Shooting_Method_SensitivityMatrix.i block=Kernels/SM_Ar*_diffusion

!syntax parameters /Kernels/CoeffDiffusionForShootMethod

!syntax inputs /Kernels/CoeffDiffusionForShootMethod

!syntax children /Kernels/CoeffDiffusionForShootMethod
