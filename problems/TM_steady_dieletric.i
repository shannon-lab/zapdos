[GlobalParams]
  f = 10e9
[]

[Mesh]
  type = FileMesh
  file = 'TM_dieletric.msh'
[]


[Problem]
  type = FEProblem
  coord_type = RZ
  # kernel_coverage_check = false
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  # petsc_options = '-snes_converged_reason -snes_linesearch_monitor -ksp_converged_reason'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
  # petsc_options = '-snes_test_display'
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
 # nl_rel_tol = 1e-4
[]

[Outputs]
  print_perf_log = true
  print_linear_residuals = false
  [./out]
    type = Exodus
  [../]
[]

[Kernels]
  [./TM_vacuum]
    type = TM0Cylindrical
    variable = Hphi
    block = 0
    eps_r = 1
  [../]
  [./TM_dieletric]
    type = TM0Cylindrical
    variable = Hphi
    block = 1
    eps_r = 16
  [../]
[]

[Variables]
  [./Hphi]
  [../]
[]

[BCs]
  [./launcher]
    type = TM0AntennaVertBC
    boundary = Antenna
    variable = Hphi
  [../]
  [./vert_wall]
    type = TM0PECVertBC
    variable = Hphi
    boundary = vert_pec
  [../]
  [./axis]
    type = DirichletBC
    variable = Hphi
    boundary = Axis
    value = 0
  [../]
[]

[AuxVariables]
  [./Hphi_mag]
  [../]
  [./Er]
    order = FIRST
    family = MONOMIAL
  [../]
  [./Electric_z]
    order = FIRST
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./Hphi_mag]
    type = AbsValueAux
    u = Hphi
    variable = Hphi_mag
  [../]
  [./Er]
    type = TM0CylindricalEr
    Hphi = Hphi
    variable = Er
  [../]
  [./Electric_z]
    type = TM0CylindricalEz
    Hphi = Hphi
    variable = Electric_z
  [../]
[]
