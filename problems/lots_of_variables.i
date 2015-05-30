[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  xmax = 2.31e-9
#  xmax = 1.0
[]

[Preconditioning]
  [./SMP]
    type = FDP
    full = true
  #Preconditioned JFNK (default)
#    solve_type = 'PJFNK'
#    petsc_options_iname = '-pc_type -mat_fd_coloring_err -mat_fd_type'
#    petsc_options_value = 'lu       1e-6                 ds'
  [../]
[]

[Executioner]
  type = Transient
  dt = 1.14e-11
#  dt = .1
#  num_steps = 10
  end_time = 1.14e-10
#  solve_type = PJFNK
#  petsc_options_iname = '-pc_type -pc_hypre_type'
#  petsc_options_value = 'hypre boomeramg'
  trans_ss_check = true
  ss_check_tol = 1e-7
#  nl_rel_tol = 1e-2
#  l_tol = 1e-1
##  nl_abs_tol = 1e-3
#  l_max_its = 9
#  nl_max_its = 3
[]

[Outputs]
  exodus = true
  print_perf_log = true
  print_linear_residuals = true
  output_initial = true
[]

[Debug]
  show_var_residual_norms = true
[]

[LotsOfCoeffDiffusion]
  variables = 'em H OHm H2Op OH H2 Om H3Op H2O2 HO2m O2 O2m O HO2 O3 O3m'
[]

#[LotsOfVariables]
#  variables = 'em H OHm H2Op OH H2 Om H3Op H2O2 HO2m O2 O2m O HO2 O3 O3m'
#[]

[LotsOfTimeDerivatives]
  variables = 'em H OHm H2Op OH H2 Om H3Op H2O2 HO2m O2 O2m O HO2 O3 O3m'
[]

[LotsOfSources]
  variables = 'em H OHm H2Op OH H2 Om H3Op H2O2 HO2m O2 O2m O HO2 O3 O3m'
[]

[LotsOfEFieldAdvection]
  variables = 'em H OHm H2Op OH H2 Om H3Op H2O2 HO2m O2 O2m O HO2 O3 O3m'
  potential = 'potential'
[]

[Kernels]
  [./potential_diffusion]
    type = Diffusion
    variable = potential
  [../]
[]

[Variables]
  [./potential]
    scaling = 1e12
  [../]
  [./em]
    scaling = 1e17
  [../]
  [./H]
    scaling = 1e23
  [../]
  [./OHm]
    scaling = 1e18
  [../]
  [./H2Op]
  [../]
  [./OH]
    scaling = 1e29
  [../]
  [./H2]
    scaling = 1e18
  [../]
  [./Om]
    scaling = 1e33
  [../]
  [./H3Op]
    scaling = 1e56
  [../]
  [./H2O2]
    scaling = 1e33
  [../]
  [./HO2m]
    scaling = 1e48
  [../]
  [./O2]
    scaling = 1e67
  [../]
  [./O2m]
    scaling = 1e51
  [../]
  [./O]
  [../]
  [./HO2]
    scaling = 1e51
  [../]
  [./O3]
  [../]
  [./O3m]
   scaling = 1e74
  [../]
[]

[Materials]
  [./water]
    block = 0
    type = Water
    user_potential_mult = 1.0
    user_electron_mult = 1.0
    em = em
    H = H
    OHm = OHm
    H2Op = H2Op
    OH = OH
    H2 = H2
    Om = Om
    H3Op = H3Op
    H2O2 = H2O2
    HO2m = HO2m
    O2 = O2
    O2m = O2m
    O = O
    HO2 = HO2
    O3 = O3
    O3m = O3m
  [../]
[]

[BCs]
  [./electrons_flux_left]
    type = SpeciesNetFluxBC
    variable = em
    boundary = left
    x_boundary_species_current = -60.0
    species_charge = zem
  [../]
  [./electron_dirichlet_right]
    type = DirichletBC
    variable = em
    boundary = right
    value = 0.0
  [../]
#  [./OHm_dirichlet_right]
#    type = DirichletBC
#    variable = OHm
#    boundary = right
#    value = 0.0
#  [../]
  [./potential_left]
    type = EFieldBC
    variable = potential
    boundary = left
    x_boundary_e_field = -5.0e5
  [../]
  [./potential_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0.0
  [../]
[]

#[ICs]
#  [./electron_ic]
#    type = ConstantIC
#    variable = em
#    value = 0.0
#  [../]
#[]
