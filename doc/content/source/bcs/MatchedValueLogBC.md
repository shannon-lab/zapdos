# MatchedValueLogBC

!syntax description /BCs/MatchedValueLogBC

## Overview

`MatchedValueLogBC` is based on Henry’s Law, such that `MatchedValueLogBC` matches a variable to the value of a coupled variable based on the ratio of liquid phase density to gas phase density, in the form of:

\begin{equation}
H  u = v
\end{equation}

Where $u$ is our variable of interest, $v$ is the coupled variable we are trying to match, and $H$ is the ratio between variables.

!alert warning title=Untested Class
The MatchedValueLogBC does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using MatchedValueLogBC. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the MatchedValueLogBC object.

```text
[BCs]
  [liquid_surface]
    type = MatchedValueLogBC
    variable = O2_gas
    v = O2_water
    henry_solubility = 1.3e-3
    boundary = 'water'
  []
[]
```

!syntax parameters /BCs/MatchedValueLogBC

!syntax inputs /BCs/MatchedValueLogBC

!syntax children /BCs/MatchedValueLogBC
