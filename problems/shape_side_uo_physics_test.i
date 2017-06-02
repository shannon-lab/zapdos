u_left = 0.5

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
  [./pot]
  [../]
[]

[Kernels]
  [./diff_u]
    type = Diffusion
    variable = u
  [../]
  [./adv_u]
    type = PotentialAdvection
    variable = u
    potential = pot
  [../]
  [./diff_pot]
    type = Diffusion
    variable = pot
  [../]
  [./source]
    type = PotentialGradientSource
    variable = u
    potential = pot
  [../]
  [./time_u]
    type = TimeDerivative
    variable = u
  [../]
[]

[BCs]
  [./left]
    boundary = left
    type = VacuumBC
    variable = u
  [../]
  [./right]
    boundary = right
    type = VacuumBC
    variable = u
  [../]

  [./left_pot]
    boundary = left
    type = ExampleShapeSideIntegratedBC
    variable = pot
    num_user_object = num_user_object
    denom_user_object = denom_user_object
    v = u
    Vb = 1
  [../]
  [./right_pot]
    boundary = right
    type = DirichletBC
    variable = pot
    value = 0
  [../]
[]

[UserObjects]
  [./num_user_object]
    type = NumShapeSideUserObject
    u = u
    boundary = left
    execute_on = 'linear nonlinear'
  [../]
  [./denom_user_object]
    type = DenomShapeSideUserObject
    u = u
    boundary = left
    execute_on = 'linear nonlinear'
  [../]
[]

[AuxVariables]
  [./u_flux]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./sigma_aux]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./u_flux]
    type = DriftDiffusionFluxAux
    variable = u_flux
    u = u
    potential = pot
    component = 0
  [../]
  [./sigma_aux]
    type = Sigma
    variable = sigma_aux
    n = u
    potential = pot
    boundary = 'left right'
  [../]
[]

[Problem]
  type = FEProblem
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
  dt = .1

  solve_type = NEWTON
  petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -sub_pc_type -sub_ksp_type'
  petsc_options_value = 'asm      lu           preonly'
[]

[Outputs]
  print_perf_log = true
  [./out]
    type = Exodus
    execute_on = 'timestep_end'
    output_material_properties = true
    show_material_properties = 'sigma'
  [../]
[]

[ICs]
  [./u]
    type = FunctionIC
    variable = u
    function = ic_u
  [../]
  [./pot]
    type = FunctionIC
    variable = pot
    function = ic_pot
  [../]
[]

[Functions]
  [./ic_u]
    type = ParsedFunction
    value = '${u_left} * (1 - x)'
  [../]
  [./ic_pot]
    type = ParsedFunction
    value = '1 - x'
  [../]
[]

[Materials]
  [./sigma_mat]
    type = SigmaMat
    n = u
    potential = pot
    boundary = 'left right'
  [../]
[]
