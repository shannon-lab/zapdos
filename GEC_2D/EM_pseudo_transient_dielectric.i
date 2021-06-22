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
  [./coeff_real]
    type = PlasmaDielectricConstantCoeffField
    variable = E_real
    real_field = E_real
    imaginary_field = E_imag
    component = real
    driving_frequency = 40e6
  [../]
  [./curl_curl_imag]
    type = CurlCurlField
    variable = E_imag
  [../]
  [./coeff_imag]
    type = PlasmaDielectricConstantCoeffField
    variable = E_imag
    real_field = E_real
    imaginary_field = E_imag
    component = imaginary
    driving_frequency = 40e6
  [../]
[]

[BCs]
  ## The natural condition is the perfect electric conductor condition for all other surfaces
  [./top_electrode_real]
    type = VectorPenaltyDirichletBC
    boundary = Top_Electrode
    variable = E_real
    penalty = 1e5
    x_exact_sln = '(50/0.0254)*cos(2*pi*40e6*t)'
  [../]
  [./top_electrode_imag]
    type = VectorPenaltyDirichletBC
    boundary = Top_Electrode
    variable = E_imag
    penalty = 1e5
    x_exact_sln = '(50/0.0254)*sin(2*pi*40e6*t)'
  [../]
  [./bottom_electrode_real]
    type = VectorPenaltyDirichletBC
    boundary = Bottom_Electrode
    variable = E_real
    penalty = 1e5
    x_exact_sln = '(-50/0.0254)*cos(2*pi*40e6*t)'
  [../]
  [./bottom_electrode_imag]
    type = VectorPenaltyDirichletBC
    boundary = Bottom_Electrode
    variable = E_imag
    penalty = 1e5
    x_exact_sln = '(-50/0.0254)*sin(2*pi*40e6*t)'
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

[Materials]
  [./plasma_dielectric]
    type = PlasmaDielectricConstant
    drive_frequency = 40e6
    electron_neutral_collision_frequency = 0.5e9
    em = em
    output_properties = 'plasma_dielectric_constant_real plasma_dielectric_constant_imag'
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
