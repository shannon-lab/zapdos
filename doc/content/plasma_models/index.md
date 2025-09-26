# Plasma Models In Zapdos

Zapdos uses various models that are derived from the fluid description of plasmas. This page serves as a brief introduction to the fluid description and the different models that Zapdos employs.

## [Multi-fluid Description of Plasma](multi-fluid_description.md)

!style halign=left
The foundational form of the multi-fluid description is derived by taking the moments of the Boltzmann equation. This allows for the tracking of group velocities and densities, instead of particle tracking (such as in PIC codes). All models within Zapdos are a variation of this underlying formulation. For a PIC description of plasmas in MOOSE, please refer to the MOOSE application, [SALAMANDER](https://mooseframework.inl.gov/salamander/).

Click the link in the section title to learn more about the multi-fluid description of plasma.

## [Drift-Diffusion Model](drift_diffusion_model.md)

!style halign=left
The drift-diffusion model is the primary model used in Zadpos for industrial applications of plasmas. It differs from the foundational form of the multi-fluid description in how the species flux is defined. For the foundational form, the flux is defined as the species density multiplied by velocity (i.e., $\vec{\Gamma} = n\vec{u}$), while in the drift-diffusion model, the flux is represented by a diffusion and an electric field driven advection term (i.e., $\vec{\Gamma} = \mu n \vec{E} - D \nabla n$).

Click the link in the section title to learn more about the drift-diffusion model.

## [Microwave Coupling](https://github.com/shannon-lab/zapdos/issues/259)

!style halign=left
MOOSE's [electromagnetics module](https://mooseframework.inl.gov/modules/electromagnetics/) has been coupled to Zapdos for simulating microwave driven discharges, [!cite](dechant). This capability is in the process of being merged into the default Zapdos GitHub branch.

Click the link in the section title to visit the GitHub page about the progress of merging this capability.

## [Braginskii Model](https://github.com/shannon-lab/zapdos/issues/294)

!style halign=left
The Braginskii fluid model is commonly used to simulate the edge region of the plasma for tokamak fusion devices (referenced in [!cite](dudson2016verification), [!cite](dull2024introducing), and [!cite](wiesen2015new)). Current efforts are focused on incorporating the Braginskii model into Zapdos, with initial merged capability coming soon.

Click the link in the section title to visit the GitHub page about the progress of merging this capability.
