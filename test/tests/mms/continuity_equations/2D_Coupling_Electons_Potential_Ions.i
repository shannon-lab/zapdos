[Mesh]
  [geo]
    type = FileMeshGenerator
    file = '2D_Coupling_Electons_Potential_Ions_IC_out.e'
    use_for_exodus_restart = true
  []
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [em]
    initial_from_file_var = em
  []
  [potential]
    initial_from_file_var = potential
  []
  [ion]
    initial_from_file_var = ion
  []
[]

[Kernels]
#Electron Equations
  [em_time_derivative]
    type = TimeDerivativeLog
    variable = em
  []
  [em_diffusion]
    type = CoeffDiffusion
    variable = em
    position_units = 1.0
  []
  [em_advection]
    type = EFieldAdvection
    variable = em
    position_units = 1.0
  []
  [em_source]
    type = BodyForce
    variable = em
    function = 'em_source'
  []

#Ion Equations
  [ion_time_derivative]
    type = TimeDerivativeLog
    variable = ion
  []
  [ion_diffusion]
    type = CoeffDiffusion
    variable = ion
    position_units = 1.0
  []
  [ion_advection]
    type = EFieldAdvection
    variable = ion
    position_units = 1.0
  []
  [ion_source]
    type = BodyForce
    variable = ion
    function = 'ion_source'
  []

#Potential Equations
  [potential_diffusion]
    type = CoeffDiffusionLin
    variable = potential
    position_units = 1.0
  []
  [ion_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = ion
    potential_units = V
  []
  [em_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = em
    potential_units = V
  []
[]

[AuxVariables]
  [potential_sol]
  []

  [em_sol]
  []

  [ion_sol]
  []
[]

[AuxKernels]
  [potential_sol]
    type = FunctionAux
    variable = potential_sol
    function = potential_fun
  []

  [em_sol]
    type = FunctionAux
    variable = em_sol
    function = em_fun
  []

  [ion_sol]
    type = FunctionAux
    variable = ion_sol
    function = ion_fun
  []
[]

[Functions]
#Material Variables
  #Electron diffusion coeff.
  [diffem_coeff]
    type = ConstantFunction
    value = 0.05
  []
  #Electron mobility coeff.
  [muem_coeff]
    type = ConstantFunction
    value = 0.01
  []
  #Ion diffusion coeff.
  [diffion]
    type = ConstantFunction
    value = 0.1
  []
  #Ion mobility coeff.
  [muion]
    type = ConstantFunction
    value = 0.025
  []
  [N_A]
    type = ConstantFunction
    value = 1.0
  []
  [ee]
    type = ConstantFunction
    value = 1.0
  []
  [diffpotential]
    type = ConstantFunction
    value = 0.01
  []
  [diffpotential_mat]
    type = ParsedFunction
    symbol_names = 'diffpotential'
    symbol_values = 'diffpotential'
    expression = 'diffpotential * (1.6e-19 * 6.02e23)'
  []


#Manufactured Solutions
  #The manufactured electron density solution
  [em_fun]
    type = ParsedFunction
    symbol_names = 'N_A'
    symbol_values = 'N_A'
    expression = 'log((sin(pi*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 1.0 + cos(pi/2*x)) / N_A)'
  []
  #The manufactured ion density solution
  [ion_fun]
    type = ParsedFunction
    symbol_names = 'N_A'
    symbol_values = 'N_A'
    expression = 'log((sin(pi*y) + 1.0 + 0.9*cos(pi/2*x)) / N_A)'
  []
  #The manufactured electron density solution
  [potential_fun]
    type = ParsedFunction
    symbol_names = 'ee diffpotential'
    symbol_values = 'ee diffpotential'
    expression = '-(ee*(2*cos((pi*x)/2) + cos(pi*y)*sin(2*pi*t)))/(5*diffpotential*pi^2)'
  []

#Source Terms in moles
  #The electron source term.
  [em_source]
    type = ParsedFunction
    symbol_names = 'ee diffpotential diffem_coeff muem_coeff N_A'
    symbol_values = 'ee diffpotential diffem_coeff muem_coeff N_A'
    expression = '(diffem_coeff*(pi^2*sin(pi*y) + (pi^2*cos(pi*y)*sin(2*pi*t))/5) +
                   (2*pi*cos(2*pi*t)*cos(pi*y))/5 + (diffem_coeff*pi^2*cos((pi*x)/2))/4 +
                   (ee*muem_coeff*(5*cos((pi*x)/2) - 4*cos(2*pi*t)^2*cos(pi*y)^2 +
                   10*cos(pi*y)*sin(2*pi*t) + 5*cos((pi*x)/2)*sin(pi*y) + 2*cos(2*pi*t)^2 +
                   10*cos((pi*x)/2)^2 + 4*cos(pi*y)^2 + 11*cos((pi*x)/2)*cos(pi*y)*sin(2*pi*t) +
                   20*cos(pi*y)*sin(2*pi*t)*sin(pi*y) - 7))/(50*diffpotential)) / N_A'
  []
  #The ion source term.
  [ion_source]
    type = ParsedFunction
    symbol_names = 'ee diffpotential diffion muion N_A'
    symbol_values = 'ee diffpotential diffion muion N_A'
    expression = '((diffion*pi^2*(9*cos((pi*x)/2) + 40*sin(pi*y)))/40 +
                   (9*ee*muion*sin((pi*x)/2)^2)/(100*diffpotential) -
                   (ee*muion*cos((pi*x)/2)*((9*cos((pi*x)/2))/10 + sin(pi*y) + 1))/(10*diffpotential) -
                   (ee*muion*cos(pi*y)*sin(2*pi*t)*sin(pi*y))/(5*diffpotential) -
                   (ee*muion*cos(pi*y)*sin(2*pi*t)*((9*cos((pi*x)/2))/10 +
                   sin(pi*y) + 1))/(5*diffpotential)) / N_A'
  []

  [em_ICs]
    type = ParsedFunction
    symbol_names = 'N_A'
    symbol_values = 'N_A'
    expression = 'log((3.0 + cos(pi/2*x)) / N_A)'
  []
  [ion_ICs]
    type = ParsedFunction
    symbol_names = 'N_A'
    symbol_values = 'N_A'
    expression = 'log((3.0 + 0.9*cos(pi/2*x)) / N_A)'
  []
[]

[BCs]
  [potential_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_fun'
    boundary = '0 1 2 3'
    preset = true
  []

  [em_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_fun'
    boundary = '0 1 2 3'
    preset = true
  []

  [ion_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_fun'
    boundary = '0 1 2 3'
    preset = true
  []
[]

[Materials]
  [field_solver]
    type = FieldSolverMaterial
    potential = potential
  []
  [Material_Coeff]
    type = GenericFunctionMaterial
    prop_names =  'e N_A'
    prop_values = 'ee N_A'
  []
  [ADMaterial_Coeff_Set1]
    type = ADGenericFunctionMaterial
    prop_names =  'diffpotential     diffion muion'
    prop_values = 'diffpotential_mat diffion muion'
  []
  [ADMaterial_Coeff_Set2]
    type = ADGenericFunctionMaterial
    prop_names =  'diffem        muem'
    prop_values = 'diffem_coeff  muem_coeff'
  []
  [Charge_Signs]
    type = GenericConstantMaterial
    prop_names =  'sgnem  sgnion'
    prop_values = '-1.0   1.0'
  []
[]

[Postprocessors]
  [em_l2Error]
    type = ElementL2Error
    variable = em
    function = em_fun
  []
  [ion_l2Error]
    type = ElementL2Error
    variable = ion
    function = ion_fun
  []
  [potential_l2Error]
    type = ElementL2Error
    variable = potential
    function = potential_fun
  []

  [h]
    type = AverageElementSize
  []
[]

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
  [out]
    type = Exodus
    time_step_interval = 10
  []
[]
