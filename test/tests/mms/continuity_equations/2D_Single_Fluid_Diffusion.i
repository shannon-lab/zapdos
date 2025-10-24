[Mesh]
  [geo]
    type = FileMeshGenerator
    file = '2D_Single_Fluid_Diffusion_IC_out.e'
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
  [em_source]
    type = BodyForce
    variable = em
    function = 'em_source'
  []
[]

[AuxVariables]
  [em_sol]
  []
[]

[AuxKernels]
  [em_sol]
    type = FunctionAux
    variable = em_sol
    function = em_fun
  []
[]

[Functions]
#Material Variables
  #Electron diffusion coeff.
  [diffem_coeff]
    type = ConstantFunction
    value = 0.05
  []

  [N_A]
    type = ConstantFunction
    value = 1.0
  []
  [ee]
    type = ConstantFunction
    value = 1.0
  []


#Manufactured Solutions
  #The manufactured electron density solution
  [em_fun]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((sin(pi*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 1.0 + cos(pi/2*x)) / N_A)'
  []

#Source Terms in moles
  #The electron source term.
  [em_source]
    type = ParsedFunction
    vars = 'ee diffem_coeff N_A'
    vals = 'ee diffem_coeff N_A'
    expression = '(diffem_coeff*(pi^2*sin(pi*y) + (pi^2*cos(pi*y)*sin(2*pi*t))/5) +
                   (2*pi*cos(2*pi*t)*cos(pi*y))/5 +
                   (diffem_coeff*pi^2*cos((pi*x)/2))/4) / N_A'
  []

  #The left BC dirichlet function
  [em_left_BC]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2) / N_A)'
  []

  [em_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((3.0 + cos(pi/2*x)) / N_A)'
  []
[]

[BCs]
  [em_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_fun'
    boundary = '0 1 2 3'
    preset = true
  []
[]

[Materials]
  [Material_Coeff]
    type = GenericFunctionMaterial
    prop_names =  'e N_A'
    prop_values = 'ee N_A'
  []
  [ADMaterial_Coeff]
    type = ADGenericFunctionMaterial
    prop_names =  'diffem'
    prop_values = 'diffem_coeff'
  []
  [Charge_Signs]
    type = GenericConstantMaterial
    prop_names =  'sgnem'
    prop_values = '-1.0'
  []
[]

[Postprocessors]
  [em_l2Error]
    type = ElementL2Error
    variable = em
    function = em_fun
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
