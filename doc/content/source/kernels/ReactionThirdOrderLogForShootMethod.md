# ReactionThirdOrderLogForShootMethod

!syntax description /Kernels/ReactionThirdOrderLogForShootMethod

## Overview

`ReactionThirdOrderLogForShootMethod` is the derivative of a third-order reaction term used to calculate the sensitivity variable for the shooting method. For more information on the implementation of the shooting method within Zapdos, please reference [ShootMethodLog.md].

## Example Input File Syntax

An example of how to use `ReactionThirdOrderLogForShootMethod` can be found in the
test file `Acceleration_By_Shooting_Method_SensitivityMatrix.i`.

!listing test/tests/accelerations/Acceleration_By_Shooting_Method_SensitivityMatrix.i block=Kernels/SM_Ar*_3B_quenching

!syntax parameters /Kernels/ReactionThirdOrderLogForShootMethod

!syntax inputs /Kernels/ReactionThirdOrderLogForShootMethod

!syntax children /Kernels/ReactionThirdOrderLogForShootMethod
