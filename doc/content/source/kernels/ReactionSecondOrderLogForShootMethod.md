# ReactionSecondOrderLogForShootMethod

!syntax description /Kernels/ReactionSecondOrderLogForShootMethod

## Overview

`ReactionSecondOrderLogForShootMethod` is the derivative of a second order reaction term used to calculate the sensitivity variable for the shoothing method. For more information on the implementation of the shoothing method within Zapdos, please reference to [ShootMethodLog.md].

## Example Input File Syntax

An example of how to use `ReactionSecondOrderLogForShootMethod` can be found in the
test file `Acceleration_By_Shooting_Method_SensitivityMatrix.i`.

!listing test/tests/accelerations/Acceleration_By_Shooting_Method_SensitivityMatrix.i block=Kernels/SM_Ar*_quenching

!syntax parameters /Kernels/ReactionSecondOrderLogForShootMethod

!syntax inputs /Kernels/ReactionSecondOrderLogForShootMethod

!syntax children /Kernels/ReactionSecondOrderLogForShootMethod
