[GlobalParams]
  f = 10e9
[]

[Mesh]
  type = FileMesh
  file = 'TM.msh'
  coord_type = RZ
[]

[Problem]
  type = FEProblem
  # kernel_coverage_check = false
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
    ksp_norm = none
  []
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
  perf_graph = true
  print_linear_residuals = false
  [out]
    type = Exodus
  []
[]

[Kernels]
  [TM]
    type = TM0Cylindrical
    variable = Hphi
  []
[]

[Variables]
  [Hphi]
  []
[]

[BCs]
  [launcher]
    type = TM0AntennaVertBC
    boundary = Antenna
    variable = Hphi
  []
  [vert_wall]
    type = TM0PECVertBC
    variable = Hphi
    boundary = vert_pec
  []
  [axis]
    type = DirichletBC
    variable = Hphi
    boundary = Axis
    value = 0
  []
[]

[AuxVariables]
  [Hphi_mag]
  []
  [Er]
    order = FIRST
    family = MONOMIAL
  []
  [Electric_z]
    order = FIRST
    family = MONOMIAL
  []
[]

[AuxKernels]
  [Hphi_mag]
    type = AbsValueAux
    u = Hphi
    variable = Hphi_mag
  []
  [Er]
    type = TM0CylindricalErAux
    Hphi = Hphi
    variable = Er
  []
  [Electric_z]
    type = TM0CylindricalEzAux
    Hphi = Hphi
    variable = Electric_z
  []
[]

[Materials]
  [vacuum]
    type = ADGenericConstantMaterial
    prop_names = 'eps_r'
    prop_values = '1'
    block = vacuum
  []
[]
