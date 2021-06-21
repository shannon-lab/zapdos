[Mesh]
  type = FileMesh
  #file = thesis_mesh_coaxial.msh
  file = thesis_mesh.msh
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

# [AuxVariables]
#   [./em]
#     initial_condition = -24.8
#   [../]
# []

[Kernels]
  [./curl_curl_real]
    type = CurlCurlField
    variable = E_real
  [../]
  # [./coeff_real]
  #   type = VectorCoeffField
  #   variable = E_real
  #   func = '-(2*pi*40e6/3e8)*(2*pi*40e6/3e8)'  # -(wave number)^2
  # [../]
  # [./time_derivative_real_coax]
  #   type = VectorSecondTimeDerivative
  #   variable = E_real
  #   coefficient = '2.53/(3e8 * 3e8)' # 1/c^2 = mu_0 * eps_0, eps_r is Rexolite
  #   block = coax
  # [../]
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
  # [./time_derivative_imag_coax]
  #   type = VectorSecondTimeDerivative
  #   variable = E_imag
  #   coefficient = '2.53/(3e8 * 3e8)' # 1/c^2 = mu_0 * eps_0, eps_r is Rexolite
  #   block = coax
  # [../]
  [./time_derivative_imag_plasma]
    type = VectorSecondTimeDerivative
    variable = E_imag
    coefficient = '1/(3e8 * 3e8)' # 1/c^2 = mu_0 * eps_0
    block = plasma
  [../]
  # [./coeff_imag]
  #   type = VectorCoeffField
  #   variable = E_imag
  #   func = '-(2*pi*40e6/3e8)*(2*pi*40e6/3e8)'  # -(wave number)^2
  # [../]
[]

[BCs]
  # ## The natural condition is the perfect electric conductor condition for all other surfaces
  # [./port_real]
  #   type = VectorEMRobinBC
  #   variable = E_real
  #   component = real
  #   beta = '2*pi*40e6/3e8'
  #   coupled_field = E_imag
  #   real_incoming = inc_real_top
  #   #imag_incoming = inc_imag_top
  #   mode = port
  #   boundary = 'source'
  # [../]
  # [./port_imag]
  #   type = VectorEMRobinBC
  #   variable = E_imag
  #   component = imaginary
  #   beta = '2*pi*40e6/3e8'
  #   coupled_field = E_real
  #   real_incoming = inc_real_top
  #   #imag_incoming = inc_imag_top
  #   mode = port
  #   boundary = 'source'
  # [../]
  # ## An exit for the waves in the domain is through the bottom insulator
  # [./absorbing_real]
  #   type = VectorEMRobinBC
  #   variable = E_real
  #   component = real
  #   beta = '2*pi*40e6/3e8'
  #   coupled_field = E_imag
  #   mode = absorbing
  #   boundary = 'Walls'
  # [../]
  # [./absorbing_imag]
  #   type = VectorEMRobinBC
  #   variable = E_imag
  #   component = imaginary
  #   beta = '2*pi*40e6/3e8'
  #   coupled_field = E_real
  #   mode = absorbing
  #   boundary = 'Walls'
  # [../]
  [./electrode_real]
    type = VectorPenaltyDirichletBC
    boundary = Top_Electrode
    variable = E_real
    penalty = 1e5
    x_exact_sln = '(50/0.0254)*cos(2*pi*1e9*t)'
  [../]
  [./electrode_imag]
    type = VectorPenaltyDirichletBC
    boundary = Top_Electrode
    variable = E_imag
    penalty = 1e5
    x_exact_sln = '(50/0.0254)*sin(2*pi*1e9*t)'
  [../]
  [./walls_real]
    type = VectorPenaltyDirichletBC
    boundary = Walls
    variable = E_real
    penalty = 1e5
  [../]
  [./walls_imag]
    type = VectorPenaltyDirichletBC
    boundary = Walls
    variable = E_imag
    penalty = 1e5
  [../]
[]


[Functions]
  [./inc_real_top]
    type = ParsedVectorFunction
    value_y = 'cos(2*pi*40e6*t)'
  [../]
  [./inc_imag_top]
    type = ParsedVectorFunction
    value_y = '(50/0.0015)*sin(2*pi*40e6*t)'
  [../]
  [./inc_real_bottom]
    type = ParsedVectorFunction
    value_x = '-50*cos(2*pi*40e6*t)'
  [../]
  [./inc_imag_bottom]
    type = ParsedVectorFunction
    value_x = '-50*sin(2*pi*40e6*t)'
  [../]
[]

# [Materials]
#   [./plasma_dielectric]
#     type = PlasmaDielectricConstant
#     drive_frequency = 40e6
#     electron_neutral_collision_frequency = 0.5e9
#     em = em
#   [../]
# []

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
  # [./FDP]
  #   type = FDP
  #   full = true
  # [../]
[]

[Executioner]
  type = Transient
  solve_type = NEWTON
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor' # -snes_test_jacobian'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
  # petsc_options_iname = '-pc_type -pc_hypre_type -pc_factor_shift_type -pc_factor_shift_amount'
  # petsc_options_value = 'hypre boomeramg NONZERO 1.e-10'
  num_steps = 500
  scheme = newmark-beta
  dt = 4e-10
  automatic_scaling = true
  compute_scaling_once = false
[]

[Outputs]
  exodus = true
  perf_graph = true
[]
