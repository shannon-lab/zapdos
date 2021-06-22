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
  [./time_derivative_real_plasma]
    type = VectorSecondTimeDerivative
    variable = E_real
    coefficient = '1/(3e8 * 3e8)' # 1/c^2 = mu_0 * eps_0
    block = plasma
  [../]
  [./curl_curl_imag]
    type = CurlCurlField
    variable = E_imag
  [../]
  [./time_derivative_imag_plasma]
    type = VectorSecondTimeDerivative
    variable = E_imag
    coefficient = '1/(3e8 * 3e8)' # 1/c^2 = mu_0 * eps_0
    block = plasma
  [../]
[]

[BCs]
  ## The natural condition is the perfect electric conductor condition for all other surfaces
  [./electrode_real]
    type = VectorPenaltyDirichletBC
    boundary = Top_Electrode
    variable = E_real
    penalty = 1e5
    x_exact_sln = '(50/0.0254)*cos(2*pi*40e6*t)'
  [../]
  [./electrode_imag]
    type = VectorPenaltyDirichletBC
    boundary = Top_Electrode
    variable = E_imag
    penalty = 1e5
    x_exact_sln = '(50/0.0254)*sin(2*pi*40e6*t)'
  [../]
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
  type = Transient
  solve_type = NEWTON
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
  num_steps = 700
  scheme = newmark-beta
  dt = 4e-10
  automatic_scaling = true
  compute_scaling_once = false
[]

[Outputs]
  exodus = true
  perf_graph = true
[]
