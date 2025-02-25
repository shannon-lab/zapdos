#In this tutorial, users input the missing data for
#Zapdos’s Drift-Diffusion Action and CRANE’s Reactions Action.
#The simulation is a simple electron and ion only argon plasma,
#where “reaction1” is the metastable excitation reaction
#and “reaction2” is ionization.  The reaction coefficients are in “rate” form.

#A uniform scaling factor of the mesh.
#E.g if set to 1.0, there is not scaling
# and if set to 0.010, there mesh is scaled by a cm
dom0Scale=25.4e-3

[GlobalParams]
  #Scales the potential by V or kV
  potential_units = kV
  #Converts density from #/m^3 to moles/m^3
  use_moles = true
[]

[Mesh]
  #Mesh is define by a Gmsh file
  [geo]
    type = FileMeshGenerator
    file = 'Lymberopoulos_paper.msh'
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

[DriftDiffusionAction]
  [Plasma]
    #User define name for electrons (usually 'em')
    electrons =
    #User define name for ions
    charged_particle =
    #User define name for potential (usually 'potential')
    potential =
    #Defines if this potential exist in only one block/material (set 'true' for single gases)
    Is_potential_unique =
    #User define name for the electron mean energy density (usually 'mean_en')
    mean_energy =
    #The position scaling for the mesh, define at top of input file
    position_units = ${dom0Scale}
    #Additional outputs, such as ElectronTemperature, Current, and EField.
    Additional_Outputs =
  []
[]

[Reactions]
  [Gas]
    #Name of reactant species that are variables
    species =
    #Name of reactant species that are auxvariables
    aux_species =
    #Type of coefficient (rate or townsend)
    reaction_coefficient_format =
    #Name of background gas
    gas_species =
    #Name of the electron mean energy density (usually 'mean_en')
    electron_energy =
    #Name of the electrons (usually 'em')
    electron_density =
    #Defines if electrons are tracked
    include_electrons =
    #Name of name for potential (usually 'potential')
    potential =
    #Defines if log form is used (true for Zapdos)
    use_log = true
    #Defines if automatic differentiation is used (true for Zapdos)
    use_ad = true
    #The position scaling for the mesh, define at top of input file
    position_units = ${dom0Scale}
    #Name of material block ('0' for an user undefined block)
    block = 0
    #Inputs of the plasma chemsity
    #e.g. Reaction : Constant or EEDF dependent [Threshold Energy] (Text file name)
    #     em + Ar -> em + Ar*        : EEDF [-11.56] (reaction1)
    reactions =
  []
[]

[AuxVariables]
  #Add a scaled position units used for plotting other element AuxVariables
  [x_node]
  []

  #Background gas (e.g Ar)
  [Ar]
  []
[]

[AuxKernels]
  #Add at scaled position units used for plotting other element AuxVariables
  [x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
  []

  #Background gas number density (e.g. for 1Torr)
  [Ar_val]
    type = FunctionAux
    variable = Ar
    function = 'log(3.22e22/6.022e23)'
    execute_on = INITIAL
  []
[]

#Currently there is no Action for BC (but one is currently in development)
#Below is the Lymberopulos family of BC
#(For other BC example, please look at Tutorial 04 and Tutorial 06)
[BCs]
#Voltage Boundary Condition Ffor a Power-Ground RF Discharge
  [potential_left]
    type = FunctionDirichletBC
    variable = potential
    boundary = 'left'
    function = potential_bc_func
    preset = false
  []
  [potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = 'right'
    value = 0
    preset = false
  []

#Boundary conditions for electons
  [em_physical_right]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'right left'
    emission_coeffs = 0.01  #Secondary electron coeff.
    ks = 1.19e5 #Thermal electron velocity
    ions = Ar+
    position_units = ${dom0Scale}
  []

#Boundary conditions for ions
  [Ar+_physical_right_advection]
    type = LymberopoulosIonBC
    variable = Ar+
    boundary = 'right left'
    position_units = ${dom0Scale}
  []

#Boundary conditions for mean energy
  [mean_en_physical_right]
    type = ElectronTemperatureDirichletBC
    variable = mean_en
    electrons = em
    value = 0.5 #Electron Temperature in eV
    boundary = 'right left'
  []
[]

#Initial conditions for variables.
#If left undefine, the IC is zero
[ICs]
  [em_ic]
    type = FunctionIC
    variable = em
    function = density_ic_func
  []
  [Ar+_ic]
    type = FunctionIC
    variable = Ar+
    function = density_ic_func
  []
  [mean_en_ic]
    type = FunctionIC
    variable = mean_en
    function = energy_density_ic_func
  []
  [potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
  []
[]

#Define function used throughout the input file (e.g. BCs and ICs)
[Functions]
  [potential_bc_func]
    type = ParsedFunction
    expression = '0.100*sin(2*3.1415926*13.56e6*t)'
  []
  [potential_ic_func]
    type = ParsedFunction
    expression = '0.100 * (25.4e-3 - x)'
  []
  [density_ic_func]
    type = ParsedFunction
    expression = 'log((1e13 + 1e15 * (1-x/1)^2 * (x/1)^2)/6.022e23)'
  []
  [energy_density_ic_func]
    type = ParsedFunction
    expression = 'log(3./2.) + log((1e13 + 1e15 * (1-x/1)^2 * (x/1)^2)/6.022e23)'
  []
[]

[Materials]
  #The material properties for electrons.
  #Also hold universal constant, such as Avogadro's number, elementary charge, etc.
  [GasBasics]
    type = GasElectronMoments
    #False means constant electron coeff, defined by user
    interp_trans_coeffs = false
    #Leave as false (CRANE accounts of elastic coeff.)
    interp_elastic_coeff = false
    #Leave as false, unless computational error is due to rapid coeff. changes
    ramp_trans_coeffs = false
    #User difine pressure in pa
    user_p_gas = 133.322
    #Name for electrons (usually 'em')
    em = em
    #Name for the electron mean energy density (usually 'mean_en')
    mean_en = mean_en
    #User define electron mobility coeff. (define as 0.0 if not used)
    user_electron_mobility = 30.0
    #User define electron diffusion coeff. (define as 0.0 if not used)
    user_electron_diffusion_coeff = 119.8757763975
    #Name of text file with electron properties
    property_tables_file = rate_coefficients/electron_moments.txt
  []
  #The material properties of the ion
  [gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = Ar+
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    mobility = 0.144409938
    diffusivity = 6.428571e-3
  []
  #The material properties of the background gas
  [gas_species_2]
    type = ADHeavySpecies
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
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
  end_time = 7.3746e-5
  dt = 1e-9
  dtmin = 1e-14
  scheme = bdf2
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
