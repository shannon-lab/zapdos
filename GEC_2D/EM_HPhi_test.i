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

[GlobalParams]
  driving_frequency = 40e6
[]

[Variables]
  [./HPhi_real]
    family = LAGRANGE
    order = SECOND
  [../]
  [./HPhi_imag]
    family = LAGRANGE
    order = SECOND
  [../]
  [./Er_real]
    family = LAGRANGE
    order = SECOND
  [../]
  [./Er_imag]
    family = LAGRANGE
    order = SECOND
  [../]
  [./Ez_real]
    family = LAGRANGE
    order = SECOND
  [../]
  [./Ez_imag]
    family = LAGRANGE
    order = SECOND
  [../]
[]

[AuxVariables]
  [./em]
    initial_condition = -24.8
  [../]
[]

[Kernels]
  [./wave_equation_real]
    type = HPhiCylindricalPlasmaWaveEquation
    variable = HPhi_real
    component = real
    real_field = HPhi_real
    imaginary_field = HPhi_imag
  [../]
  [./wave_equation_imag]
    type = HPhiCylindricalPlasmaWaveEquation
    variable = HPhi_imag
    component = imaginary
    real_field = HPhi_real
    imaginary_field = HPhi_imag
  [../]
  [./Er_eqn_real]
    type = HPhiCylindricalPlasmaEr
    variable = Er_real
    component = real
    real_field = Er_real
    imaginary_field = Er_imag
    real_Hphi = HPhi_real
    imaginary_HPhi = HPhi_imag
  [../]
  [./Er_eqn_imag]
    type = HPhiCylindricalPlasmaEr
    variable = Er_imag
    component = imaginary
    real_field = Er_real
    imaginary_field = Er_imag
    real_Hphi = HPhi_real
    imaginary_HPhi = HPhi_imag
  [../]
  [./Ez_eqn_real]
    type = HPhiCylindricalPlasmaEz
    variable = Ez_real
    component = real
    real_field = Ez_real
    imaginary_field = Ez_imag
    real_Hphi = HPhi_real
    imaginary_HPhi = HPhi_imag
  [../]
  [./Ez_eqn_imag]
    type = HPhiCylindricalPlasmaEz
    variable = Ez_imag
    component = imaginary
    real_field = Ez_real
    imaginary_field = Ez_imag
    real_Hphi = HPhi_real
    imaginary_HPhi = HPhi_imag
  [../]
[]

[BCs]
  [./h_phi_real_current] # Magnetic field into the page at the edge of the domain (based on applied rf current)
    type = ADFunctionDirichletBC
    variable = HPhi_real
    function = HPhi0
    boundary = right
  [../]
  [./h_phi_imag_right]
    type = ADDirichletBC
    variable = HPhi_imag
    value = 0
    boundary = right
  [../]
[]

[Functions]
  [./HPhi0] # Irf = 2*pi*x*HPhi0
    type = ParsedFunction
    value = 'cos(2*pi*40e6*t)/(2*pi*x)'
  [../]
[]

[Materials]
  [./plasma_dielectric]
    type = PlasmaDielectricConstant
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
