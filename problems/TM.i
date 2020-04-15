#Runs but Solve failed

[GlobalParams]
  f = 10e9
[]

[Mesh]
  type = FileMesh
  file = 'TM.msh'
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
  type = Transient
  # end_time = 2.18-9
  num_steps = 50
  solve_type = NEWTON
  # petsc_options = '-snes_converged_reason -snes_linesearch_monitor -ksp_converged_reason'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
  # petsc_options = '-snes_test_display'
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
 # nl_rel_tol = 1e-4
  dt = 2e-12
  dtmin = 1e-15
[]

[Outputs]
  perf_graph = true
  print_linear_residuals = false
  [./out]
    type = Exodus
  [../]
[]

# [Debug]
#   show_var_residual_norms = true
# []

[Kernels]
  [./TM]
    type = TM0Cylindrical
    variable = Hphi
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
[]

[AuxKernels]
  [./Hphi_mag]
    type = AbsValueAux
    u = Hphi
    variable = Hphi_mag
  [../]
[]

[Materials]
   [./vacuum]
     type = GenericConstantMaterial
     prop_names = 'eps_r'
     prop_values = '1'
     block = vacuum
   [../]
[]
