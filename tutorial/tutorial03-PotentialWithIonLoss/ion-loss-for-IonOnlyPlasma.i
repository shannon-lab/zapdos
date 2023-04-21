#This tutorial shows the decrease of potential in
#an ion-only plasma as ions leave the system.
#This is based on Lieberman’s Figure 2.2, page 27.

#A uniform scaling factor of the mesh.
#E.g if set to 1.0, there is not scaling
# and if set to 0.010, there mesh is scaled by a cm
dom0Scale = 1.0

[GlobalParams]
  #Scales the potential by V or kV
  potential_units = V
  #Converts density from #/m^3 to moles/m^3
  use_moles = true
[]

[Mesh]
  #Sets up a 1D mesh from 0 to 10cm with 100 points
  [geo]
    type = GeneratedMeshGenerator
    xmin = 0
    xmax = 0.10
    nx = 100
    dim = 1
  []
  #Renames all sides with the specified normal
  #For 1D, this is used to rename the end points of the mesh
  [left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = geo
  []
  [right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  []
[]

#Defines the problem type, such as FE, eigen value problem, etc.
[Problem]
  type = FEProblem
[]

#Zapdos's Drift-Diffusion Action that inputs the continuity equations for
# species and electon mean energy, and poisson's equation for potential
[DriftDiffusionAction]
  [Plasma]
    #User define name for ions
    charged_particle = Ar+
    #User define name for potential (usually 'potential')
    field = potential
    #Defines if this potential exist in only one block/material (set 'true' for single gases)
    Is_field_unique = true
    #The position scaling for the mesh, define at top of input file
    position_units = ${dom0Scale}
  []
[]

[AuxVariables]
  #Add a scaled position units used for plotting other Variables
  [x_node]
  []
[]

[AuxKernels]
  #Add at scaled position units used for plotting other Variables
  [x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
  []
[]

[BCs]
  #Voltage Boundary Condition
  [potential_left]
    type = DirichletBC
    variable = potential
    boundary = 'left right'
    value = 0
    preset = false
  []

  #Boundary conditions for ions
  [Arp_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = Ar+
    boundary = 'right left'
    r = 0
    position_units = ${dom0Scale}
  []
  [Arp_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = Ar+
    boundary = 'right left'
    r = 0
    position_units = ${dom0Scale}
  []
[]

#Initial conditions for variables.
#If left undefine, the IC is zero
[ICs]
  [Ar+_ic]
    type = FunctionIC
    variable = Ar+
    function = 'log(1e16/6.022e23)'
  []

  [potential_ic]
    type = FunctionIC
    variable = potential
    function = '0.5 * (1e16 * 1.6e-19) / 8.85e-12 * ((0.10/2)^2. - (x-0.10/2)^2.)'
  []
[]

[Materials]
  #The material properties for electrons.
  #Also hold universal constant, such as Avogadro's number, elementary charge, etc.
  [GasBasics]
    type = GasElectronMoments
    interp_trans_coeffs = false
    interp_elastic_coeff = false
    ramp_trans_coeffs = false
    user_p_gas = 13.3322
    #user_p_gas = 1.33322
    property_tables_file = rate_coefficients/electron_moments.txt
  []
  #The material properties of the ion
  [gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = Ar+
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
  []
[]

#Preconditioning options
#Learn more at: https://mooseframework.inl.gov/syntax/Preconditioning/index.html
[Preconditioning]
  active = 'smp'
  [smp]
    type = SMP
    full = true
  []

  [fdp]
    type = FDP
    full = true
  []
[]

#How to execute the problem.
#Defines type of solve (such as steady or transient),
# solve type (Newton, PJFNK, etc.) and tolerances
[Executioner]
  type = Transient
  end_time = 1e-10
  dt = 1e-12
  dtmin = 1e-14
  solve_type = NEWTON

  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 1e-3'
[]

#Defines the output type of the file (multiple output files can be define per run)
[Outputs]
  perf_graph = true
  [out]
    type = Exodus
  []
[]
