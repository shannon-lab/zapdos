[Mesh]
  [./geo]
    type = FileMeshGenerator
    file = '2D_Single_Fluid_Diffusion_Advection_IC_out.e'
    use_for_exodus_restart = true
  [../]
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [./em]
    initial_from_file_var = em
  [../]
[]

[Kernels]
#Electron Equations
  [./em_time_derivative]
    type = TimeDerivativeLog
    variable = em
  [../]
  [./em_diffusion]
    type = CoeffDiffusion
    variable = em
    position_units = 1.0
  [../]
  [./em_advection]
    type = EFieldAdvection
    variable = em
    potential = 'potential'
    position_units = 1.0
  [../]
  [./em_source]
    type = BodyForce
    variable = em
    function = 'em_source'
  [../]
[]

[AuxVariables]
  [./potential]
  [../]

  [./em_sol]
  [../]
[]

[AuxKernels]
  [./potential_sol]
    type = FunctionAux
    variable = potential
    function = potential_fun
  [../]

  [./em_sol]
    type = FunctionAux
    variable = em_sol
    function = em_fun
  [../]
[]

[Functions]
#Material Variables
  #Electron diffusion coeff.
  [./diffem_coeff]
    type = ConstantFunction
    value = 0.05
  [../]
  #Electron mobility coeff.
  [./muem_coeff]
    type = ConstantFunction
    value = 0.01
  [../]

  [./N_A]
    type = ConstantFunction
    value = 1.0
  [../]
  [./ee]
    type = ConstantFunction
    value = 1.0
  [../]
  [./diffpotential]
    type = ConstantFunction
    value = 0.01
  [../]


#Manufactured Solutions
  #The manufactured electron density solution
  [./em_fun]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((sin(pi*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 1.0 + cos(pi/2*x)) / N_A)'
  [../]
  #The manufactured electron density solution
  [./potential_fun]
    type = ParsedFunction
    vars = 'ee diffpotential'
    vals = 'ee diffpotential'
    value = '-(ee*(2*cos((pi*x)/2) + cos(pi*y)*sin(2*pi*t)))/(5*diffpotential*pi^2)'
  [../]

#Source Terms in moles
  #The electron source term.
  [./em_source]
    type = ParsedFunction
    vars = 'ee diffem_coeff muem_coeff diffpotential N_A'
    vals = 'ee diffem_coeff muem_coeff diffpotential N_A'
    value = '(diffem_coeff*(pi^2*sin(pi*y) + (pi^2*cos(pi*y)*sin(2*pi*t))/5) +
              (2*pi*cos(2*pi*t)*cos(pi*y))/5 + (diffem_coeff*pi^2*cos((pi*x)/2))/4 +
              (ee*muem_coeff*(5*cos((pi*x)/2) - 4*cos(2*pi*t)^2*cos(pi*y)^2 +
              10*cos(pi*y)*sin(2*pi*t) + 5*cos((pi*x)/2)*sin(pi*y) + 2*cos(2*pi*t)^2 +
              10*cos((pi*x)/2)^2 + 4*cos(pi*y)^2 + 11*cos((pi*x)/2)*cos(pi*y)*sin(2*pi*t) +
              20*cos(pi*y)*sin(2*pi*t)*sin(pi*y) - 7))/(50*diffpotential)) / N_A'
  [../]

  #The left BC dirichlet function
  [./em_left_BC]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2) / N_A)'
  [../]

  #The right BC dirichlet function
  [./em_right_BC]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1) / N_A)'
  [../]

  #The Down BC dirichlet function
  [./em_down_BC]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((cos((pi*x)/2) + sin(2*pi*t)/5 + 1) / N_A)'
  [../]

  #The up BC dirichlet function
  [./em_up_BC]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((cos((pi*x)/2) - sin(2*pi*t)/5 + 1) / N_A)'
  [../]

  [./em_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((3.0 + cos(pi/2*x)) / N_A)'
  [../]
[]

[BCs]
  [./em_left_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_left_BC'
    boundary = 3
    preset = true
  [../]
  [./em_right_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_right_BC'
    boundary = 1
    preset = true
  [../]
  [./em_down_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_down_BC'
    boundary = 0
    preset = true
  [../]
  [./em_up_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_up_BC'
    boundary = 2
    preset = true
  [../]
[]

[Materials]
  [./Material_Coeff]
    type = GenericFunctionMaterial
    prop_names =  'e N_A'
    prop_values = 'ee N_A'
  [../]
  [./ADMaterial_Coeff]
    type = ADGenericFunctionMaterial
    prop_names =  'diffem        muem        diffpotential'
    prop_values = 'diffem_coeff  muem_coeff  diffpotential'
  [../]
  [./Charge_Signs]
    type = GenericConstantMaterial
    prop_names =  'sgnem'
    prop_values = '-1.0'
  [../]
[]

[Postprocessors]
  [./em_l2Error]
    type = ElementL2Error
    variable = em
    function = em_fun
  [../]

  [./h]
    type = AverageElementSize
  [../]
[]

[Preconditioning]
  active = 'smp'
  [./smp]
    type = SMP
    full = true
  [../]

  [./fdp]
    type = FDP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  start_time = 50
  end_time = 51

  # dt = 0.008
  dt = 0.02


  automatic_scaling = true
  compute_scaling_once = false
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  line_search = none
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'

  scheme = bdf2

  nl_abs_tol = 1e-13
[]

[Outputs]
  perf_graph = true
  [./out]
    type = Exodus
    interval = 10
  []
[]
