# EffectiveEFieldAdvection

!syntax description /Kernels/EffectiveEFieldAdvection

## Overview

`EffectiveEFieldAdvection` is the effective electric field driven advection term used for variables in logarithmic form.
The effective electric field is supplied as scalar componets of the field.

The strong form for an advection term is usually defined as

\begin{equation}
\nabla \cdot \Gamma_{\text{adv}} = \nabla \cdot \left[ \text{sign}_{j} \mu_{j} n_{j} \ \vec{E}_{\text{Eff.}} \right]
\end{equation}

where

- $\Gamma_{\text{adv}}$ is the advection component of a species' flux,
- $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species)
- $\mu_{j}$ is the mobility coefficient, $n_{j}$ is the density, and
- $\vec{E}_{\text{Eff.}}$ is the effective electric field acting on the ions.

\begin{equation}
\nabla \cdot \Gamma_{\text{adv}} = \nabla \cdot \left[ \text{sign}_{j} \mu_{j} \exp(N_{j}) \ (\vec{E}_{\text{Eff.}} / l_{c}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and
$l_{c}$ is the scaling factor of the mesh.


## Example Input File Syntax

!listing test/tests/mms/continuity_equations/2D_Coupling_Electons_Potential_Ions_MeanEnergy_Einstein_Relation_EffEfield.i block=Kernels/ion_advection

!syntax parameters /Kernels/EffectiveEFieldAdvection

!syntax inputs /Kernels/EffectiveEFieldAdvection

!syntax children /Kernels/EffectiveEFieldAdvection
