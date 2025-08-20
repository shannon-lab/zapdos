# AnalyticalDiffIndicator

!syntax description /Adaptivity/Indicators/AnalyticalDiffIndicator

## Overview

The `AnalyticalDiffIndicator` object computes the raw difference between a solution variable and
a known function.

For more information about the Indicators System within MOOSE, please see the [Indicators System page](syntax/Adaptivity/Indicators/index.md).

!alert! warning title=Untested Class
The `AnalyticalDiffIndicator` object does not have a formalized test, yet. For this reason,
users should beware of unforeseen bugs when using `AnalyticalDiffIndicator`. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards on how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).
!alert-end!

## Example Input File Syntax

```text
[Adaptivity]
  [Indicators]
    [diff]
      type = AnalyticalDiffIndicator
      variable = u
      function = solution
    []
  []
[]
```

!syntax parameters /Adaptivity/Indicators/AnalyticalDiffIndicator

!syntax inputs /Adaptivity/Indicators/AnalyticalDiffIndicator

!syntax children /Adaptivity/Indicators/AnalyticalDiffIndicator
