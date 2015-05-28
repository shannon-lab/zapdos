[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 100
  xmax = 1e-5
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
  dt = 5.263e-5
#  dt = .1
  num_steps = 10
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

[LotsOfCoeffDiffusion]
  variables = 'em OHm H'
  diffusion_coeffs = 'Dem DOHm DH'
[]

[LotsOfVariables]
  variables = 'em OHm H'
[]

[LotsOfTimeDerivatives]
  variables = 'em OHm H'
[]

[LotsOfSources]
  variables = 'em OHm H'
[]

#[Variables]
#  [./em]
#  [../]
#[]

[Materials]
  [./water]
    block = 0
    type = Water
    user_potential_mult = 1.0
    user_electron_mult = 1.0
    em = em
    H = H
    OHm = OHm
  [../]
[]

#[Kernels]
#  [./em_source]
#    type = FirstOrderReaction
#    reaction_coeff = 1
#    variable = em
#  [../]
#[]

[BCs]
  [./electrons_flux_left]
    type = SpeciesNetFluxBC
    variable = em
    boundary = left
    x_boundary_species_current = -60.0
    species_charge = zem
  [../]
#  [./electron_dirichlet_left]
#    type = DirichletBC
#    variable = em
#    boundary = left
#    value = 1.0
#  [../]
  [./electron_dirichlet_right]
    type = DirichletBC
    variable = em
    boundary = right
    value = 0.0
  [../]
  [./OHm_dirichlet_right]
    type = DirichletBC
    variable = OHm
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
