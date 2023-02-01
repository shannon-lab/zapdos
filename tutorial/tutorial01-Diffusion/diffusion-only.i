#This tutorial is a sample simple diffusion case with
#pin density at the center (x=0) and end of a wall (x=0.5).
#This is based on Lieberman’s Figure 5.1, page 141.

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
  #Sets up a 1D mesh from 0 to 0.5m with 1000 element
  [geo]
    type = GeneratedMeshGenerator
    xmin = 0
    xmax = 0.5
    nx = 1000
    dim = 1
  []
  #Renames all sides with the specified normal
  #For 1D, this is used to rename the end points of the mesh
  [left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0' #Outward facing normal
    new_boundary = 'left'
    input = geo
  []
  [right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right' #Outward facing normal
    input = left
  []
[]

#Defines the problem type, such as FE, eigen value problem, etc.
[Problem]
  type = FEProblem
[]

#User defined name for the variables.
#Other variable properties are defined here,
# such as family of shape function and variable order
# (the default family/order is Lagrange/First)
[Variables]
  [Ar+]
  []
[]

[Kernels]
  #Adds the diffusion for the variable
  [Ar+_diffusion]
    type = CoeffDiffusion
    variable = Ar+
    position_units = ${dom0Scale}
  []
  #Adds the source term for the variable.
  #In this case, adds a first order reaction of k*Ar+
  [Ar+_source]
    type = ReactionFirstOrderLog
    variable = Ar+
    # v is a constant density of 1e16 #/m^3 in mole-log form
    # (i.e v  = ln(1e16/6.022e23) = -17.9135)
    v = -17.9135
    _v_eq_u = false
    coefficient = 1
    reaction = FirstOrder
  []
[]

#User defined name for the auxvariables.
#Other variable properties are defined here,
# such as family of shape function and variable order
[AuxVariables]
  [x]
    #Monomial is a family set for elemental variables
    #(variable that are solve for the elements vs the nodes)
    order = CONSTANT
    family = MONOMIAL
  []

  #The auxvariable used to converts the mole-log form of the density to #/m^3
  [Ar+_density]
    order = CONSTANT
    family = MONOMIAL
  []

  #The auxvariable for the known solution for this diffusion problem
  [Solution]
  []
[]

[AuxKernels]
  #Add a scaled position units used for plotting other element AuxVariables
  [x_ng]
    type = Position
    variable = x
    position_units = ${dom0Scale}
  []
  #Converts the mole-log form of the density to #/m^3
  [Ar+_density]
    type = DensityMoles
    variable = Ar+_density
    density_log = Ar+
    execute_on = 'LINEAR TIMESTEP_END'
  []
  #The know solution for this diffusion problem
  [Solution]
    type = FunctionAux
    variable = Solution
    function = '1e16 * 9.8696 / 8. * (1 - (2*x)^2.)'
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
[]

[BCs]
  #Dirichlet boundary conditions for mole-log density
  #Value is in #/m^3
  [Ar+_physical_right_diffusion]
    type = LogDensityDirichletBC
    variable = Ar+
    boundary = 'right'
    value = 100
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
    user_p_gas = 133.3322
    user_electron_diffusion_coeff = 1.0
    property_tables_file = rate_coefficients/electron_moments.txt
  []
  #The material properties of the ion
  [gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = Ar+
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    diffusivity = 1
    #diffusivity = 2
  []
  #The rate constant for the first order reaction of the source term
  [FirstOrder_Reaction]
    type = GenericRateConstant
    reaction = FirstOrder
    reaction_rate_value = 9.8696
    #reaction_rate_value = 4.9348
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
  type = Steady
  solve_type = NEWTON

  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 1e-3'

  nl_rel_tol = 1e-08
  l_max_its = 20
[]

#Defines the output type of the file (multiple output files can be define per run)
[Outputs]
  perf_graph = true
  [out]
    type = Exodus
  []
[]
