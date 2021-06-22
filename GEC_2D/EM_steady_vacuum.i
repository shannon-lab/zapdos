[Mesh]
  type = FileMesh
  file = thesis_mesh.msh
[]

[Problem]
  type = FEProblem
  coord_type = RZ
  rz_coord_axis = Y
[]

[Variables]
  [./E_real]
    order = FIRST
    family = NEDELEC_ONE
  [../]
  [./E_imag]
    order = FIRST
    family = NEDELEC_ONE
  [../]
[]

[Kernels]
  [./curl_curl_real]
    type = CurlCurlField
    variable = E_real
  [../]
  [./coeff_real]
    type = VectorCoeffField
    variable = E_real
    func = '-(2*pi*40e6/3e8)*(2*pi*40e6/3e8)'  # -(wave number)^2
  [../]
  [./curl_curl_imag]
    type = CurlCurlField
    variable = E_imag
  [../]
  [./coeff_imag]
    type = VectorCoeffField
    variable = E_imag
    func = '-(2*pi*40e6/3e8)*(2*pi*40e6/3e8)'  # -(wave number)^2
  [../]
[]

[BCs]
  ## The natural condition is the perfect electric conductor condition for all other surfaces
  [./top_electrode_real]
    type = VectorPenaltyDirichletBC
    boundary = Top_Electrode
    variable = E_real
    penalty = 1e5
    x_exact_sln = '(50/0.0254)' #*cos(2*pi*40e6*t)'
  [../]
  [./top_electrode_imag]
    type = VectorPenaltyDirichletBC
    boundary = Top_Electrode
    variable = E_imag
    penalty = 1e5
    x_exact_sln = '(50/0.0254)' #*sin(2*pi*40e6*t)'
  [../]
  # [./bottom_electrode_real]
  #   type = VectorPenaltyDirichletBC
  #   boundary = Bottom_Electrode
  #   variable = E_real
  #   penalty = 1e5
  #   x_exact_sln = '(-50/0.0254)' #*cos(2*pi*40e6*t)'
  # [../]
  # [./bottom_electrode_imag]
  #   type = VectorPenaltyDirichletBC
  #   boundary = Bottom_Electrode
  #   variable = E_imag
  #   penalty = 1e5
  #   x_exact_sln = '(-50/0.0254)' #*sin(2*pi*40e6*t)'
  # [../]
  [./walls_real]
    type = VectorPenaltyDirichletBC
    boundary = 'penalty_walls'
    variable = E_real
    penalty = 1e5
  [../]
  [./walls_imag]
    type = VectorPenaltyDirichletBC
    boundary = 'penalty_walls'
    variable = E_imag
    penalty = 1e5
  [../]
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
  #num_steps = 700
  #scheme = newmark-beta
  #dt = 4e-10
  automatic_scaling = true
  compute_scaling_once = false
[]

[Outputs]
  exodus = true
  perf_graph = true
[]
