# ArbitrarilyTiedValueConstraint

!syntax description /Constraints/ArbitrarilyTiedValueConstraint

## Overview

Similar to [TiedValueConstraint.md], except the value of a variable is forced based on
a user defined ratio at an interface.

!alert! warning title=Untested Class
The `ArbitrarilyTiedValueConstraint` does not have a formalized test, yet. For this reason,
users should beware of unforeseen bugs when using `ArbitrarilyTiedValueConstraint`. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards on how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).
!alert-end!

## Example Input File Syntax

```text
[Constraints]
  [diffusive_surface]
    variable = electrons
    secondary = water
    primary = plasma
    primary_variable = electrons
    H = 0.1
  []
[]
```

!syntax parameters /Constraints/ArbitrarilyTiedValueConstraint

!syntax inputs /Constraints/ArbitrarilyTiedValueConstraint

!syntax children /Constraints/ArbitrarilyTiedValueConstraint
