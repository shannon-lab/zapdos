[Mesh]
  [./generate]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 10
    ny = 10
  [../]
  second_order = true
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

[AuxVariables]
  [./em]
    initial_condition = -24.8
  [../]
[]

[Kernels]
  [./curl_curl_real]
    type = CurlCurlField
    variable = E_real
  [../]
  [./time_derivative_real]
    type = VectorSecondTimeDerivative
    variable = E_real
    coefficient = '1/(3e8 * 3e8)' # 1/c^2 = mu_0 * eps_0
  [../]
  # [./time_derivative_real]
  #   type = PlasmaDielectricConstantSecondTimeDerivative
  #   variable = E_real
  #   component = real
  #   real_field = E_real
  #   imaginary_field = E_imag
  # [../]
  # [./time_derivative_real]
  #   type = VectorSecondTimeDerivative
  #   variable = E_real
  #   coefficient = 1
  # [../]
  [./curl_curl_imag]
    type = CurlCurlField
    variable = E_imag
  [../]
  # [./time_derivative_imag]
  #   type = PlasmaDielectricConstantSecondTimeDerivative
  #   variable = E_imag
  #   component = imaginary
  #   real_field = E_real
  #   imaginary_field = E_imag
  # [../]
  [./time_derivative_imag]
    type = VectorSecondTimeDerivative
    variable = E_imag
    coefficient = '1/(3e8 * 3e8)' # 1/c^2 = mu_0 * eps_0
  [../]
  [./source]
    type = VectorBodyForce
    variable = E_real
    value = 1
  [../]
  [./source_imag]
    type = VectorBodyForce
    variable = E_imag
    value = 1
  [../]
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
  #   imag_incoming = inc_imag_top
  #   mode = port
  #   boundary = 'Top_Insulator'
  # [../]
  # [./port_imag]
  #   type = VectorEMRobinBC
  #   variable = E_imag
  #   component = imaginary
  #   beta = '2*pi*40e6/3e8'
  #   coupled_field = E_real
  #   real_incoming = inc_real_top
  #   imag_incoming = inc_imag_top
  #   mode = port
  #   boundary = 'Top_Insulator'
  # [../]
  # ## An exit for the waves in the domain is through the bottom insulator
  # [./absorbing_real]
  #   type = VectorEMRobinBC
  #   variable = E_real
  #   component = real
  #   beta = '2*pi*40e6/3e8'
  #   coupled_field = E_imag
  #   real_incoming = inc_real_bottom
  #   imag_incoming = inc_imag_bottom
  #   mode = port
  #   boundary = 'Bottom_Insulator'
  # [../]
  # [./absorbing_imag]
  #   type = VectorEMRobinBC
  #   variable = E_imag
  #   component = imaginary
  #   beta = '2*pi*40e6/3e8'
  #   coupled_field = E_real
  #   real_incoming = inc_real_bottom
  #   imag_incoming = inc_imag_bottom
  #   mode = port
  #   boundary = 'Bottom_Insulator'
  # [../]
  # [./pen_real]
  #   type = VectorPenaltyDirichletBC
  #   variable = E_real
  #   boundary = left
  #   penalty = 1e10
  #   x_exact_sln = 10
  # [../]
  # [./pen_imag]
  #   type = VectorPenaltyDirichletBC
  #   variable = E_imag
  #   boundary = left
  #   penalty = 1e10
  #   x_exact_sln = 10
  # [../]
[]


# [Functions]
#   [./inc_real_top]
#     type = ParsedVectorFunction
#     value_x = '50*cos(2*pi*40e6*t)'
#   [../]
#   [./inc_imag_top]
#     type = ParsedVectorFunction
#     value_x = '50*sin(2*pi*40e6*t)'
#   [../]
#   [./inc_real_bottom]
#     type = ParsedVectorFunction
#     value_x = '-50*cos(2*pi*40e6*t)'
#   [../]
#   [./inc_imag_bottom]
#     type = ParsedVectorFunction
#     value_x = '-50*sin(2*pi*40e6*t)'
#   [../]
# []

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
  solve_type = PJFNK
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor -snes_test_jacobian'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
  # petsc_options_iname = '-pc_type -pc_hypre_type -pc_factor_shift_type -pc_factor_shift_amount'
  # petsc_options_value = 'hypre boomeramg NONZERO 1.e-10'
  num_steps = 20
  scheme = newmark-beta
  dt = 4e-10
  automatic_scaling = true
  compute_scaling_once = false
[]

[Outputs]
  exodus = true
  perf_graph = true
[]
