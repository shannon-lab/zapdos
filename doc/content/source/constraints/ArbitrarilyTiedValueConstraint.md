# ArbitrarilyTiedValueConstraint

!syntax description /Constraints/ArbitrarilyTiedValueConstraint

## Overview

Similar to [`TiedValueConstraint`](TiedValueConstraint.md), except the value of a variable is forced based on
a user defined ratio at an interface.

!alert warning title=Untested Class
The `ArbitrarilyTiedValueConstraint` does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using `ArbitrarilyTiedValueConstraint`. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the ArbitrarilyTiedValueConstraint object.

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
