# EEDFReactionLogForShootMethod

!syntax description /Kernels/EEDFReactionLogForShootMethod

## Overview

`EEDFReactionLogForShootMethod` is the derivative of an Electron Energy Distribution Function (EEDF) reaction term used to calculate the
 sensitivity variable for the shoothing method. For more information on the implementation of the shoothing method within Zapdos, please reference [ShootMethodLog.md].

## Example Input File Syntax

An example of how to use `EEDFReactionLogForShootMethod` can be found in the
test file `Acceleration_By_Shooting_Method.i`.

!listing test/tests/accelerations/Acceleration_By_Shooting_Method.i block=Kernels/SM_Ar*_stepwise_ionization

!syntax parameters /Kernels/EEDFReactionLogForShootMethod

!syntax inputs /Kernels/EEDFReactionLogForShootMethod

!syntax children /Kernels/EEDFReactionLogForShootMethod
