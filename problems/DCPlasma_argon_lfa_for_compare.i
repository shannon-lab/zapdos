[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1000
  xmin = 0
  xmax = 1e-3
[]

[Problem]
  type = FEProblem
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  end_time = 1e-1
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type' # -pc_factor_mat_solver_package'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly' # mumps'
 # nl_rel_tol = 1e-8
 # l_tol = 1e-3
 # trans_ss_check = true
 # ss_check_tol = 1e-7
 nl_abs_tol = 1e-5
  l_max_its = 10
 nl_max_its = 50
  dtmin = 0.9e-9
  # line_search = 'none'
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.4
    dt = 1e-9
    growth_factor = 1.2
   optimal_iterations = 50
  [../]
[]

[Outputs]
  print_perf_log = true
  [./out]
    type = Exodus
    output_material_properties = true
    show_material_properties = 'EField'
    # show_material_properties = 'ElectronTotalFlux ElectronAdvectiveFlux ElectronDiffusiveFlux IonTotalFlux IonAdvectiveFlux IonDiffusiveFlux EField'
  [../]
[]

[Debug]
  show_var_residual_norms = true
[]

[UserObjects]
  [./data_provider]
    type = ProvideMobility
    electrode_area = 3.14e-6
    ballast_resist = 1e6
  [../]
[]

[Kernels]
  [./em_time_deriv]
    type = ElectronTimeDerivative
    variable = em
  [../]
  [./Arp_time_deriv]
    type = ElectronTimeDerivative
    variable = Arp
  [../]
  [./electrons]
    type = ElectronBolosKernel
    variable = em
    potential = potential
  [../]
  [./ions]
    type = IonBolosKernel
    variable = Arp
    em = em
    potential = potential
  [../]
  [./potential]
    type = PoissonKernel
    variable = potential
    em = em
    Arp = Arp
  [../]
[]

[Variables]
  [./potential]
    scaling = 1e-5
  [../]
  [./em]
    scaling = 1e-18
  [../]
  [./Arp]
    scaling = 1e-18
  [../]
[]

[AuxVariables]
  [./em_lin]
  [../]
  [./Arp_lin]
  [../]
  # [./e_field]
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  # [./advective_flux]
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  # [./diffusive_flux]
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  # [./art_diffusive_flux]
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  # [./total_flux]
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  # [./total_flux_mag]
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  # [./aux_source]
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
[]

[AuxKernels]
  [./em_lin]
    type = ElectronDensity
    variable = em_lin
    electron_density = em
  [../]
  [./Arp_lin]
    type = IonDensity
    variable = Arp_lin
    ion_density = Arp
  [../]
  # [./e_field]
  #   type = Efield
  #   variable = e_field
  #   potential = potential
  # [../]
  # [./a_flux]
  #   type = ElectronAdvectiveFlux
  #   variable = advective_flux
  #   electron_density = em
  #   potential = potential
  # [../]
  # [./d_flux]
  #   type = ElectronDiffusiveFlux
  #   variable = diffusive_flux
  #   em = em
  # [../]
  # [./ad_flux]
  #   type = ElectronArtDiffusiveFlux
  #   variable = art_diffusive_flux
  #   potential = potential
  #   em = em
  # [../]
  # [./total_flux]
  #   type = ElectronTotalFlux
  #   variable = total_flux
  #   potential = potential
  #   em = em
  # [../]
  # [./total_flux_mag]
  #   type = ElectronTotalFluxMag
  #   variable = total_flux_mag
  #   potential = potential
  #   em = em
  # [../]
  # [./source]
  #   type = AuxSource
  #   variable = aux_source
  #   potential = potential
  #   em = em
  # [../]
[]

[BCs]
  [./potential_left]
    type = NeumannCircuitVoltage
    variable = potential
    boundary = left
    function = potential_bc_func
    ip = Arp
    data_provider = data_provider
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
  [./em_physical]
    type = DCElectronBC
    variable = em
    boundary = 'left right'
    potential = potential
    Arp = Arp
  [../]
  [./Arp_physical]
    type = DCIonBC
    variable = Arp
    boundary = 'left right'
    potential = potential
  [../]
[]

[ICs]
  [./em_ic]
    type = ConstantIC
    variable = em
    value = 29.934
  [../]
  [./ip_ic]
    type = ConstantIC
    variable = Arp
    value = 29.934
  [../]
  [./potential_ic]
    type = ConstantIC
    variable = potential
    value = 0
  [../]
[]

[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    value = '1.25e3*tanh(1e5*t)'
  [../]
[]

[Materials]
  [./argon]
    block = 0
    type = ArgonConstTD
    em = em
    potential = potential
 [../]
[]