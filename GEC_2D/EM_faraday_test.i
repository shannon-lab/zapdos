[Mesh]
  [./gmg]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 200
    ny = 25
    xmax = 0.2
    ymax = 0.0254
  [../]
  second_order = true
[]

[Problem]
  type = FEProblem
  coord_type = RZ
  rz_coord_axis = Y
[]

[Variables]
  [./u]
    order = FIRST
    family = NEDELEC_ONE
  [../]
[]

[Kernels]
  [./curl_curl]
    type = CurlCurlField
    variable = u
  [../]
  [./coeff_real]
    type = VectorCoeffField
    variable = u
    func = '-(38750.077500155)*(2*pi*40e6/3e8)*(2*pi*40e6/3e8)'  # -(relative permittivity)*(wave number)^2
  [../]
[]

[BCs]
  [./h_phi_current] # Magnetic field time derivative (based on applied RF current) into the page that excites the wave
    type = FaradayCurrentBC
    variable = u
    driving_frequency = 40e6
    applied_current_dot = current_dot
    boundary = right
  [../]
[]

[Functions]
  [./current_dot]
    type = ParsedVectorFunction
    value_z = '-1*sin(2*pi*40e6*t)'
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
  num_steps = 50
  scheme = newmark-beta
  dt = 4e-10
  automatic_scaling = true
  compute_scaling_once = false
[]

[Outputs]
  exodus = true
  perf_graph = true
[]
