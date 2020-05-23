dom0Scale=1.0
dom1Scale=1.0
dom2Scale=1.0

[GlobalParams]
  #offset = 20
  offset = 30
  #offset = 40
  # offset = 0
  potential_units = kV
  use_moles = true
  # potential_units = V
[]

[Mesh]
  #skip_partitioning = true
  [./file]
    type = FileMeshGenerator
    #file = 'air_dry_reduced_mesh.msh'
    file = 'air_dry_scaled.msh' 
  [../]
  [./dielectric_left]
    # left dielectric master
    type = SideSetsBetweenSubdomainsGenerator
    master_block = '0'
    paired_block = '1'
    new_boundary = 'master01_interface'
    input = file
  [../]
  [./plasma_left]
    # plasma master
    type = SideSetsBetweenSubdomainsGenerator
    master_block = '1'
    paired_block = '0'
    new_boundary = 'master10_interface'
    input = dielectric_left
  [../]
  [./plasma_right]
    # plasma master
    type = SideSetsBetweenSubdomainsGenerator
    master_block = '1'
    paired_block = '2'
    new_boundary = 'master12_interface'
    input = plasma_left
  [../]
  [./dielectric_right]
    # left dielectric master
    type = SideSetsBetweenSubdomainsGenerator
    master_block = '2'
    paired_block = '1'
    new_boundary = 'master21_interface'
    input = plasma_right
  [../]
  [./left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = dielectric_right
  [../]
  [./right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  [../]
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
  automatic_scaling = true
  compute_scaling_once = false
  end_time = 10e-3
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  # petsc_options = '-snes_test_display'
  #solve_type = NEWTON
  solve_type = PJFNK
  line_search = 'basic'
  #petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_stol'
  #petsc_options_value = 'lu NONZERO 1.e-10 0'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
  nl_rel_tol = 1e-7
  nl_abs_tol = 1e-8
  dtmin = 1e-15
  dtmax = 1e-6
  l_max_its = 30
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.4
    dt = 1e-11
    growth_factor = 1.2
    optimal_iterations = 12
  [../]
  #[./TimeIntegrator]
  #  #type = LStableDirk2
  #  type = BDF2
  #[../]
[]

[Outputs]
  perf_graph = true
  #exodus = true
  [./out]
    type = Checkpoint
    interval = 3
    num_files = 2
  [../]
  [./exodus_out]
    type = Exodus
    output_material_properties = true
    show_material_properties = 'surface_charge'
  [../]
  #[./dof_map]
  #  type = DOFMap
  #[../]
[]

[Debug]
  #show_var_residual_norms = true
[]

[Variables]
  [./potential_dom0]
    block = 0
  [../]
  [./potential_dom1]
    block = 1
  [../]
  [./potential_dom2]
    block = 2
  [../]

  #[./mean_en]
  #  block = 1
  #[../]
[]

[DriftDiffusionAction]
  [./Plasma]
    electrons = em
    #charged_particle = 'N+ N2+ N3+ N4+ O+ O2+ O4+ O- O2- O3- O4- NO+ N2O+ NO2+ O2pN2 NO- N2O- NO2- NO3-'
    #Neutrals = 'N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2D N2P N O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 NO N2O NO2 NO3 N2O5'
    charged_particle = 'N4+ N2+ N+ O- O+ O2- O2+ NO+ O3- O4-'
    Neutrals = 'N2v N2* N2** N N* O O* O2* O21S O3 NO NO2 NO3 N2O3 N2O4 N2O5'
    mean_energy = mean_en
    potential = potential_dom1
    is_potential_unique = false
    using_offset = true
    #offset = 40
    offset = 30
    #offset = 25
    position_units = ${dom0Scale}
    #Additional_Outputs = 'ElectronTemperature EField'
    #Additional_Outputs = 'ElectronTemperature'
    block = 1
  [../]
[]

[Kernels]
  [./potential_diffusion_dom0]
    type = CoeffDiffusionLin
    variable = potential_dom0
    block = 0
    position_units = ${dom0Scale}
  [../]
  #[./potential_diffusion_dom1]
  #[./potential_dom1_diffusion1_block]
  #  type = CoeffDiffusionLin
  #  variable = potential_dom1
  #  block = 1
  #  position_units = ${dom1Scale}
  #[../]
  [./potential_diffusion_dom2]
    type = CoeffDiffusionLin
    variable = potential_dom2
    block = 2
    position_units = ${dom2Scale}
  [../]

  #[./mean_en_time_deriv]
  #  #type = ElectronTimeDerivative
  #  type = ADTimeDerivativeLog
  #  variable = mean_en
  #  block = 0
  #[../]
  #[./mean_en_advection]
  #  #type = ADEFieldAdvection
  #  type = EFieldAdvectionEnergy
  #  variable = mean_en
  #  potential = potential
  #  em = em
  #  block = 0
  #  position_units = ${dom0Scale}
  #[../]
  #[./mean_en_diffusion]
  #  #type = ADCoeffDiffusion
  #  type = CoeffDiffusionEnergy
  #  variable = mean_en
  #  block = 0
  #  position_units = ${dom0Scale}
  #[../]
  #[./mean_en_joule_heating]
  #  type = JouleHeating
  #  #type = ADJouleHeating
  #  variable = mean_en
  #  potential = potential
  #  em = em
  #  block = 0
  #  position_units = ${dom0Scale}
  #[../]
  #[./mean_en_log_stabilization]
  #  type = LogStabilizationMoles
  #  variable = mean_en
  #  block = 0
  #  #offset = 15
  #  offset = 28
  #[../]
[]

[InterfaceKernels] 
  [./potential_left]
    type = InterfacePotential
    neighbor_var = potential_dom1
    variable = potential_dom0
    em = em
    mean_en = mean_en
    ions = 'N4+ N2+ N+ O- O+ O2- O2+ O3- O4- NO+'
    boundary = master01_interface
    position_units = ${dom0Scale}
    neighbor_position_units = ${dom0Scale}
  [../]

  [./potential_right]
    type = InterfacePotential
    neighbor_var = potential_dom2
    variable = potential_dom1
    em = em
    mean_en = mean_en
    ions = 'N4+ N2+ N+ O- O+ O2- O2+ O3- O4- NO+'
    boundary = master21_interface
    position_units = ${dom0Scale}
    neighbor_position_units = ${dom0Scale}
  [../]
[]

[AuxVariables]
  #[./sigma_left]
  #  order = CONSTANT
  #  family = MONOMIAL
  #  initial_condition = 0
  #  block = 1
  #[../]
  #[./sigma_right]
  #  order = CONSTANT
  #  family = MONOMIAL
  #  initial_condition = 0
  #  block = 1
  #[../]
  [./Efield]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Te]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  [../]
  #[./H2O]
  #  order = CONSTANT
  #  family = MONOMIAL
  #  value = -0.982269  # 1% H2O
  #  block = 1
  #[../]
  [./N2]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 3.48094   # 80% N2, 20% O2
    #value = 3.19325   # 60% N2, 40% O2
    #value = 2.78779   # 40% N2, 60% O2
    #value = 2.09464   # 20% N2, 80% O2
    block = 1
  [../]
  [./O2]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 2.09464   # 80% N2, 20% O2
    #value = 2.78779   # 60% N2, 40% O2
    #value = 3.19325   # 40% N2, 60% O2
    #value = 3.48094   # 20% N2, 80% O2
    block = 1
  [../]
  [./NEUTRAL]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 3.70408
    block = 1
  [../]
  #[./e_temp]
  #  order = CONSTANT
  #  family = MONOMIAL
  #  block = 1
  #[../]
  [./N2_density]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  [../]
  [./O2_density]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  [../]
  ###########################
  # Water Species
  ###########################
  #[./H2O_lin]
  #  order = CONSTANT
  #  family = MONOMIAL
  #  block = 1
  #[../]
[]

[AuxKernels]
  #[./sigma_left]
  #  type = HagelaarChargedFlux
  #  variable = sigma_left
  #  potential = potential_dom1
  #  position_units = ${dom1Scale}
  #  mean_en = mean_en
  #  em = em 
  #  ions = 'N4+ N2+ N+ O- O+ O2- O2+ NO+'
  #  se_coeff = 0.005
  #  execute_on = 'NONLINEAR'
  #  boundary = 'master10_interface'
  #[../]
  #[./sigma_right]
  #  type = HagelaarChargedFlux
  #  variable = sigma_right
  #  potential = potential_dom1
  #  position_units = ${dom1Scale}
  #  mean_en = mean_en
  #  em = em 
  #  ions = 'N4+ N2+ N+ O- O+ O2- O2+ NO+'
  #  se_coeff = 0.005
  #  execute_on = 'NONLINEAR'
  #  boundary = 'master12_interface'
  #[../]
  [./e_temp]
    type = ElectronTemperature
    variable = Te
    electron_density = em
    mean_en = mean_en
    block = 1
    execute_on = 'INITIAL NONLINEAR LINEAR'
  [../]
  [./Efield_d0]
    type = Efield
    component = 0
    potential = potential_dom0
    #potential = potential
    variable = Efield
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./Efield_d1]
    type = Efield
    component = 0
    potential = potential_dom1
    variable = Efield
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./Efield_d2]
    type = Efield
    component = 0
    potential = potential_dom2
    #potential = potential
    variable = Efield
    position_units = ${dom0Scale}
    block = 2
  [../]
  [./x_g0]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./x_g1]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./x_g2]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    block = 2
  [../]

  [./N2_lin]
    type = DensityMoles
    variable = N2_density
    density_log = N2
    block = 1
  [../]
  [./O2_lin]
    type = DensityMoles
    variable = O2_density
    density_log = O2
    block = 1
  [../]

  ###########################
  # Water species
  ###########################
  #[./H2O_lin]
  #  type = DensityMoles
  #  variable = H2O_lin
  #  density_log = H2O
  #  block = 1
  #[../]
[]

[BCs]
  # Match potential on dielectric sides
  [./match_phi_left]
    type = MatchedValueBC
    variable = potential_dom0
    v = potential_dom1
    boundary = 'master01_interface'
  [../]
  [./match_phi_right]
    type = MatchedValueBC
    variable = potential_dom2
    v = potential_dom1
    boundary = 'master21_interface'
  [../]

  # NEUTRAL BCS
  [./N2v_diffusion]
    type = HagelaarIonDiffusionBC
    variable = N2v
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  #[./O2v_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = O2v
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]

  [./N2*_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = N2* 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./N2**_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = N2**
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./N_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = N 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./O2*_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = O2*
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./O21S_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = O21S
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./O_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = O
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./O3_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = O3
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./NO_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = NO
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  #[./N2O_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = N2O
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  [./NO2_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = NO2
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./NO3_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = NO3
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./N2O3_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = N2O3
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./N2O4_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = N2O4
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./N2O5_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = N2O5
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  # ION BCS
  [./Np_advection_right]
    type = HagelaarIonAdvectionBC
    variable = N+
    potential = potential_dom1 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./Np_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = N+
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  [./N2p_advection_right]
    type = HagelaarIonAdvectionBC
    variable = N2+
    potential = potential_dom1 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./N2p_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = N2+
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  #[./N3p_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = N3+
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./N3p_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = N3+
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]

  [./N4p_advection_right]
    type = HagelaarIonAdvectionBC
    variable = N4+
    potential = potential_dom1 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./N4p_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = N4+
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  [./Op_advection_right]
    type = HagelaarIonAdvectionBC
    variable = O+
    potential = potential_dom1 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./Op_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = O+
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  [./O2p_advection_right]
    type = HagelaarIonAdvectionBC
    variable = O2+
    potential = potential_dom1 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./O2p_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = O2+
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  #[./O4p_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = O4+
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./O4p_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = O4+
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]

  [./Om_advection_right]
    type = HagelaarIonAdvectionBC
    variable = O-
    potential = potential_dom1 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./Om_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = O-
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  [./O2m_advection_right]
    type = HagelaarIonAdvectionBC
    variable = O2-
    potential = potential_dom1 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./O2m_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = O2-
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  [./O3m_advection_right]
    type = HagelaarIonAdvectionBC
    variable = O3-
    potential = potential_dom1 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./O3m_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = O3-
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  [./O4m_advection_right]
    type = HagelaarIonAdvectionBC
    variable = O4-
    potential = potential_dom1 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./O4m_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = O4-
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  #[./O3m_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = O3-
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./O3m_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = O3-
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]

  #[./O4m_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = O4-
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./O4m_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = O4-
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]

  [./NOp_advection_right]
    type = HagelaarIonAdvectionBC
    variable = NO+
    potential = potential_dom1 
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]
  [./NOp_diffusion_right]
    type = HagelaarIonDiffusionBC
    variable = NO+
    r = 0
    position_units = ${dom1Scale}
    boundary = 'master12_interface master10_interface'
  [../]

  #[./N2Op_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = N2O+
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./N2Op_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = N2O+
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #
  #[./NO2p_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = NO2+
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./NO2p_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = NO2+
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]

  #[./O2pN2_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = O2pN2
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./O2pN2_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = O2pN2
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #
  #[./NOm_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = NO-
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./NOm_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = NO-
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]

  #[./N2Om_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = N2O-
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./N2Om_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = N2O-
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #
  #[./NO2m_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = NO2-
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./NO2m_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = NO2-
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #
  #[./NO3m_advection_right]
  #  type = HagelaarIonAdvectionBC
  #  variable = NO3- 
  #  potential = potential_dom1 
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]
  #[./NO3m_diffusion_right]
  #  type = HagelaarIonDiffusionBC
  #  variable = NO3-
  #  r = 0
  #  position_units = ${dom1Scale}
  #  boundary = 'master12_interface master10_interface'
  #[../]

  [./mean_en_physical_right]
    #type = ADHagelaarEnergyBC
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'master12_interface master10_interface'
    potential = potential_dom1 
    em = em
    r = 0.0
    position_units = ${dom0Scale}
  [../]
  #[./secondary_energy_left]
  #  #type = ADSecondaryElectronEnergyBC
  #  type = SecondaryElectronEnergyBC
  #  variable = mean_en
  #  boundary = 'master12_interface master10_interface'
  #  potential = potential_dom1 
  #  em = em
  #  ip = 'N4+ N2+ N+ O- O+ O2- O2+ O3- O4- NO+'
  #  #ip = 'N4+ N2+ N+ O+ O2+ NO+'
  #  r = 0
  #  position_units = ${dom0Scale}
  #[../]

  [./potential_left]
    type = FunctionDirichletBC
    variable = potential_dom0
    function = potential_input
    boundary = 'left'
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential_dom2
    boundary = right
    value = 0
  [../]

  [./electron_boundary]
    #type = ADHagelaarElectronBC
    type = HagelaarElectronBC
    variable = em
    boundary = 'master12_interface master10_interface'
    potential = potential_dom1 
    mean_en = mean_en
    r = 0.0
    position_units = ${dom0Scale}
  [../]
  #[./sec_electrons]
  #  #type = ADSecondaryElectronBC
  #  type = SecondaryElectronBC
  #  variable = em
  #  boundary = 'master12_interface master10_interface'
  #  potential = potential_dom1 
  #  ip = 'N4+ N2+ N+ O- O+ O2- O2+ O3- O4- NO+'
  #  #ip = 'N4+ N2+ N+ O+ O2+ NO+'
  #  mean_en = mean_en
  #  r = 0
  #  position_units = ${dom0Scale}
  #[../]
[]

[ICs]
  [./potential_dom0_ic]
    type = FunctionIC
    variable = potential_dom0
    function = potential_ic_func
  [../]
  [./potential_dom1_ic]
    type = FunctionIC
    variable = potential_dom1 function = potential_ic_func
  [../]
  [./potential_dom2_ic]
    type = FunctionIC
    variable = potential_dom2
    function = potential_ic_func
  [../]

  [./mean_en_ic]
    type = ConstantIC
    variable = mean_en
    #value = -22.5187
    #value = -20
    value = -25
  [../]
  [./em_ic]
    type = ConstantIC
    variable = em 
    #value = -22.5187 
    value = -25
  [../]

  [./N2v]
    type = ConstantIC
    variable = N2v
    #value = -20
    value = -30
  [../]
  #[./O2v]
  #  type = ConstantIC
  #  variable = O2v1
  #  value = -30
  #[../]

  [./N2*_ic]
    type = ConstantIC
    variable = N2*
    #value = -20
    value = -30
  [../]

  [./N2exex_ic]
    type = ConstantIC
    variable = N2**
    #value = -20
    value = -30
  [../]

  [./N]
    type = ConstantIC
    variable = N 
    #value = -36.2055
    value = -30
  [../]

  [./N*]
    type = ConstantIC
    variable = N* 
    #value = -34.7430
    value = -30
  [../]

  [./Np]
    type = ConstantIC
    variable = N+
    #value = -22.5689
    value = -30
  [../]

  [./N2p]
    type = ConstantIC
    variable = N2+
    value = -30
  [../]

  #[./N3p]
  #  type = ConstantIC
  #  variable = N3+
  #  value = -30
  #[../]

  [./N4p]
    type = ConstantIC
    variable = N4+
    value = -30
  [../]

  ######################################
  # Oxygen species
  ######################################
  #[./O2v1]
  # type = ConstantIC
  #  variable = 
  #   value = -30.1169
  #[../]

  [./O2*]
    type = ConstantIC
    variable = O2*
    #value = -35.6115
    value = -30
  [../]

  [./O21S]
    type = ConstantIC
    variable = O21S
    value = -30
  [../]

  [./O]
    type = ConstantIC
    variable = O
    #value = -26.7471
    value = -30
  [../]

  [./O*]
    type = ConstantIC
    variable = O*
    #value = -30.4032
    value = -30
  [../]

  [./O3]
    type = ConstantIC
    variable = O3
    value = -30
  [../]

  [./Op]
    type = ConstantIC
    variable = O+
    #value = -28.9925
    value = -30
  [../]

  [./O2p]
    type = ConstantIC
    variable = O2+
    #value = -26.6322
    value = -25
  [../]

  [./O-]
    type = ConstantIC
    variable = O-
    value = -30
  [../]

  [./O2-]
    type = ConstantIC
    variable = O2-
    #value = -31.6695
    value = -30
  [../]

  [./O3-]
    type = ConstantIC
    variable = O3-
    value = -30
  [../]

  [./O4-]
    type = ConstantIC
    variable = O4-
    #value = -35.4103
    value = -30
  [../]

  #####################################
  # Nx-Oy species
  #####################################
  [./NO]
    type = ConstantIC
    variable = NO
    #value = -28.9390
    value = -30
  [../]

  [./NOp]
    type = ConstantIC
    variable = NO+
    #value = -26.7122
    value = -30
  [../]

  #[./NO-]
  #  type = ConstantIC
  #  variable = NO-
  #  value = -30
  #[../]

  #[./O2pN2]
  #  type = ConstantIC
  #  variable = O2pN2
  #  value = -34.1682
  #[../]

  #[./N2O]
  #  type = ConstantIC
  #  variable = N2O
  #  value = -30
  #[../]

  [./NO2]
    type = ConstantIC
    variable = NO2
    value = -30
  [../]

  [./NO3]
    type = ConstantIC
    variable = NO3
    value = -30
  [../]

  [./N2O3]
    type = ConstantIC
    variable = N2O3
    value = -30
  [../]

  [./N2O4]
    type = ConstantIC
    variable = N2O4
    value = -30
  [../]

  [./N2O5]
    type = ConstantIC
    variable = N2O5
    value = -30
  [../]

  #[./N2Op]
  #  type = ConstantIC
  #  variable = N2O+
  #  value = -30
  #[../]

  #[./NO2p]
  #  type = ConstantIC
  #  variable = NO2+
  #  value = -33.3563
  #[../]

  #[./N2O-]
  #  type = ConstantIC
  #  variable = N2O-
  #  value = -30
  #[../]

  #[./NO2-]
  #  type = ConstantIC
  #  variable = NO2-
  #  value = -30
  #[../]

  #[./NO3-]
  #  type = ConstantIC
  #  variable = NO3-
  #  value = -30
  #[../]

  ##################################
  # Hydrogen-based species
  # (For humid simulations)
  ##################################
  #[./H+]
  # type = ConstantIC
  #  variable = H+ 
  #   value = -30
  #[../]
  #
  #[./H2+]
  # type = ConstantIC
  #  variable = H2+
  #   value = -30
  #[../]
  #
  #[./H3+]
  #type = ConstantIC
  #  variable = H3+
    #  value = -30
  #[../]
  #
  #[./OH+]
  #type = ConstantIC
  #  variable = OH+
    #  value = -30
  #[../]
  #
  #[./H2O+]
  #type = ConstantIC
  #  variable = H2O+
    #  value = -28.4108
  #[../]
  #
  #[./H3O+]
  #type = ConstantIC
  #  variable = H3O+
    #  value = -33.8704
  #[../]
  #
  #[./H-]
  #type = ConstantIC
  #  variable = H-
    #  value = -30
  #[../]
  #
  #[./OH-]
  #type = ConstantIC
  #  variable = OH-
    #  value = -30
  #[../]
  #
  #[./H]
  #type = ConstantIC
  #  variable = H
    #  value = -30
  #[../]
  #
  #[./H2]
  #type = ConstantIC
  #  variable = H2
    #  value = -29.5567
  #[../]
  #
  #[./OH]
  #type = ConstantIC
  #  variable = OH
    #  value = -33.5219
  #[../]
  #
  #[./HO2]
  #type = ConstantIC
  #  variable = HO2
    #  value = -30
  #[../]
  #
  #[./H2O2]
  #type = ConstantIC
  #  variable = H2O2
    #  value = -30
  #[../]
  #
  #[./HNO]
  #type = ConstantIC
  #  variable = HNO
    #  value = -30
  #[../]
  #
  #[./HNO2]
  #type = ConstantIC
  #  variable = HNO2
    #  value = -30
  #[../]
  #
  #[./HNO3]
  #type = ConstantIC
  #  variable = HNO3
    #  value = -30
  #[../]
[]

[Functions]
  [./potential_input]
    type = PiecewiseLinear
    data_file = '/home/shane/projects/zapdos/problems/voltage_data.txt'
    format = columns
  [../]
  [./potential_input_dbd]
    type = ParsedFunction
    vars = 'f0'
    vals = '50e3'
    value = '-0.75*sin(2*3.1415926*f0*t)'
  [../]
  [./potential_bc_func]
    type = ParsedFunction
    #value = 1.25
    value = 4.0
  [../]
  [./potential_ic_func]
    type = ParsedFunction
    #value = '-1.25 * (1.0001e-3 - x)'
    value = '-4 * (1.0001e-3 - x)'
  [../]
[]

[Materials]
  [./Test]
    type = SurfaceCharge
    secondary_electrons = true
    potential = potential_dom1
    r_electron = 0
    r_ion = 0
    mean_en = mean_en
    em = em
    ions = 'N4+ N2+ N+ O- O+ O2- O2+ O3- O4- NO+'
    se_coeff = 0.05
    position_units = ${dom0Scale}
    boundary = 'master10_interface master12_interface'
  [../]

  [./electron_moments]
    type = GasElectronMoments
    block = 1
    em = em
    mean_en = mean_en
    potential = potential_dom1
    user_p_gas = 101325
    property_tables_file = 'townsend/electron_mobility_diffusion.txt'
    #property_tables_file = 'rate/electron_mobility_diffusion.txt'
    #property_tables_file = 'townsend_100dp/electron_mobility_diffusion.txt'
   
    user_se_coeff = 0.05
    interp_trans_coeffs = true
    interp_elastic_coeff = false
    ramp_trans_coeffs = false
    position_units = ${dom0Scale}
  [../]

  [./dielectric_left_side]
    type = GenericConstantMaterial
    block = 0
    #prop_names = 'diffpotential'
    prop_names = 'diffpotential_dom0'
    prop_values = '8.85e-11'
  [../]
  [./gas_eps0]
    type = GenericConstantMaterial
    block = 1
    #prop_names = 'diffpotential'
    prop_names = 'diffpotential_dom1'
    prop_values = '8.85e-12'
  [../]
  [./dielectric_right_side]
    type = GenericConstantMaterial
    block = 2
    #prop_names = 'diffpotential'
    prop_names = 'diffpotential_dom2'
    prop_values = '8.85e-11'
  [../]

  #[./electron_moments]
  #  type = ADGasElectronMoments
  #  block = 1
  #  em = em
  #  mean_en = mean_en
  #  property_tables_file = 'air_plasma_dry/files_N2-80_O2-20/electron_mobility_diffusion.txt'
  #[../]

  #[./gas_constants]
  #  type = GenericConstantMaterial
  #  block = 0
  #  prop_names = ' e         N_A      diffpotential k_boltz eps  se_coeff se_energy T_gas massem   p_gas  n_gas'
  #  prop_values = '1.6e-19 6.022e23 8.85e-12      1.38e-23 8.854e-12 0.05     3.        300   9.11e-31 1.01e5 40.4915'
  #[../]

  [./gas_species_N2]
    type = HeavySpeciesMaterial
    heavy_species_name = N2 
    heavy_species_mass = 4.651843e-26
    heavy_species_charge = 0
    diffusivity = 2.1e-5 
    block = 1
  [../]

  [./gas_species_N2v1]
    type = HeavySpeciesMaterial
    heavy_species_name = N2v
    heavy_species_mass = 4.651843e-26
    heavy_species_charge = 0
    diffusivity = 2.1e-5
    block = 1
  [../]

  [./gas_species_N2*]
    type = HeavySpeciesMaterial
    heavy_species_name = N2*
    heavy_species_mass = 4.651843e-26
    heavy_species_charge = 0
    diffusivity = 5.9e-5
    block = 1
  [../]

  [./gas_species_N2**]
    type = HeavySpeciesMaterial
    heavy_species_name = N2**
    heavy_species_mass = 4.651843e-26
    heavy_species_charge = 0
    diffusivity = 5.9e-5
    block = 1
  [../]

  [./gas_species_N]
    type = HeavySpeciesMaterial
    heavy_species_name = N
    heavy_species_mass = 2.325922e-26
    heavy_species_charge = 0
    diffusivity = 5.7e-5
    block = 1
  [../]

  [./gas_species_N*]
    type = HeavySpeciesMaterial
    heavy_species_name = N*
    heavy_species_mass = 4.651843e-26
    heavy_species_charge = 0
    diffusivity = 5.9e-5
    block = 1
  [../]

  [./gas_species_Np]
    type = HeavySpeciesMaterial
    heavy_species_name = N+
    heavy_species_mass = 2.325922e-26
    heavy_species_charge = 1
    diffusivity = 5.7e-5
    block = 1
  [../]

  [./gas_species_N2p]
    type = HeavySpeciesMaterial
    heavy_species_name = N2+
    heavy_species_mass = 4.651843e-26
    heavy_species_charge = 1
    diffusivity = 5.9e-5
    block = 1
  [../]

  #[./gas_species_N3p]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = N3+
  #  heavy_species_mass = 6.977765e-26
  #  heavy_species_charge = 1
  #  diffusivity = 4.1e-5
  #  block = 1
  #[../]

  [./gas_species_N4p]
    type = HeavySpeciesMaterial
    heavy_species_name = N4+
    heavy_species_mass = 9.303686e-26
    heavy_species_charge = 1
    diffusivity = 4.1e-5
    block = 1
  [../]

  [./gas_species_O2]
    type = HeavySpeciesMaterial
    heavy_species_name = O2
    heavy_species_mass = 5.313650e-26
    heavy_species_charge = 0
    diffusivity = 2.1e-5
    block = 1
  [../]

  #[./gas_species_O2v1]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = O2v1
  #  heavy_species_mass = 5.313650e-26
  #  heavy_species_charge = 0
  #  diffusivity = 2.1e-5
  #  block = 1
  #[../]

  [./gas_species_O2*]
    type = HeavySpeciesMaterial
    heavy_species_name = O2*
    heavy_species_mass = 5.313650e-26
    heavy_species_charge = 0
    diffusivity = 2.1e-5
    block = 1
  [../]

  [./gas_species_O21S]
    type = HeavySpeciesMaterial
    heavy_species_name = O21S
    heavy_species_mass = 5.313650e-26
    heavy_species_charge = 0
    diffusivity = 2.1e-5
    block = 1
  [../]

  [./gas_species_O]
    type = HeavySpeciesMaterial
    heavy_species_name = O
    heavy_species_mass = 2.656825e-26
    heavy_species_charge = 0
    diffusivity = 6e-5
    block = 1
  [../]

  [./gas_species_O*]
    type = HeavySpeciesMaterial
    heavy_species_name = O*
    heavy_species_mass = 2.656825e-26
    heavy_species_charge = 0
    diffusivity = 6e-5
    block = 1
  [../]

  #########
  # Diffusion coefficient unknown
  [./gas_species_O3]
    type = HeavySpeciesMaterial
    heavy_species_name = O3
    heavy_species_mass = 7.970475e-26
    heavy_species_charge = 0
    diffusivity = 2e-5 
    block = 1
  [../]

  [./gas_species_O3m]
    type = HeavySpeciesMaterial
    heavy_species_name = O3-
    heavy_species_mass = 7.970475e-26
    heavy_species_charge = -1
    diffusivity = 2e-5 
    block = 1
  [../]

  [./gas_species_O4m]
    type = HeavySpeciesMaterial
    heavy_species_name = O4-
    heavy_species_mass = 1.062678e-25
    heavy_species_charge = -1
    diffusivity = 1e-5 
    block = 1
  [../]

  [./gas_species_Op]
    type = HeavySpeciesMaterial
    heavy_species_name = O+
    heavy_species_mass = 2.656825e-26
    heavy_species_charge = 1
    diffusivity = 5.8e-5
    block = 1
  [../]

  [./gas_species_O2p]
    type = HeavySpeciesMaterial
    heavy_species_name = O2+
    heavy_species_mass = 5.313650e-26
    heavy_species_charge = 1
    diffusivity = 5.6e-5
    block = 1
  [../]

  [./gas_species_Om]
    type = HeavySpeciesMaterial
    heavy_species_name = O-
    heavy_species_mass = 2.656825e-26
    heavy_species_charge = -1
    diffusivity = 7.0e-5
    block = 1
  [../]

  [./gas_species_O2m]
    type = HeavySpeciesMaterial
    heavy_species_name = O2-
    heavy_species_mass = 5.313650e-26
    heavy_species_charge = -1
    diffusivity = 5.6e-5
    block = 1
  [../]

  [./gas_species_NO]
    type = HeavySpeciesMaterial
    heavy_species_name = NO 
    heavy_species_mass = 4.982747e-26
    heavy_species_charge = 0
    diffusivity = 2e-5
    block = 1
  [../]

  [./gas_species_NOp] # nitrogen monoxide
    type = HeavySpeciesMaterial
    heavy_species_name = NO+ 
    heavy_species_mass = 4.982747e-26
    heavy_species_charge = 1
    diffusivity = 5.6e-5
    block = 1
  [../]

  #[./gas_species_NOm] # nitrogen monoxide
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = NO- 
  #  heavy_species_mass = 4.982747e-26
  #  heavy_species_charge = -1
  #  diffusivity = 5.6e-5
  #  block = 1
  #[../]

  #[./gas_species_O2pN2]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = O2pN2
  #  heavy_species_mass = 9.965493e-26
  #  heavy_species_charge = 1
  #  diffusivity = 0.5e-5
  #  block = 1
  #[../]

  # Additional nitrogen-oxygen species

  #[./gas_species_N2O]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = N2O
  #  heavy_species_mass = 7.308668e-26
  #  heavy_species_charge = 0
  #  diffusivity = 1.6e-5
  #  block = 1
  #[../]

  [./gas_species_NO2]
    type = HeavySpeciesMaterial
    heavy_species_name = NO2
    heavy_species_mass = 7.639572e-26
    heavy_species_charge = 0
    diffusivity = 1.7e-5
    block = 1
  [../]

  [./gas_species_NO3]
    type = HeavySpeciesMaterial
    heavy_species_name = NO3
    heavy_species_mass = 1.029640e-25
    heavy_species_charge = 0
    diffusivity = 0.9e-5
    block = 1
  [../]

  [./gas_species_N2O3] # dinitrogen pentoxide
    type = HeavySpeciesMaterial
    heavy_species_name = N2O3
    heavy_species_mass = 1.246463e-25
    heavy_species_charge = 0
    diffusivity = 1e-5
    block = 1
  [../]

  [./gas_species_N2O4] # dinitrogen pentoxide
    type = HeavySpeciesMaterial
    heavy_species_name = N2O4
    heavy_species_mass = 1.527914e-25
    heavy_species_charge = 0
    diffusivity = 1e-5
    block = 1
  [../]

  [./gas_species_N2O5] # dinitrogen pentoxide
    type = HeavySpeciesMaterial
    heavy_species_name = N2O5
    heavy_species_mass = 1.793597e-25
    heavy_species_charge = 0
    diffusivity = 1e-5
    block = 1
  [../]

  #[./gas_species_N2Op]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = N2O+
  #  heavy_species_mass = 7.308668e-26
  #  heavy_species_charge = 1
  #  diffusivity = 4.8e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_NO2p]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = NO2+
  #  heavy_species_mass = 7.639572e-26
  #  heavy_species_charge = 1
  #  diffusivity = 4.6e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_N2Om]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = N2O-
  #  heavy_species_mass = 7.308668e-26
  #  heavy_species_charge = -1
  #  diffusivity = 4.8e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_NO2m]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = NO2-
  #  heavy_species_mass = 7.639572e-26
  #  heavy_species_charge = -1
  #  diffusivity = 4.6e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_NO3m]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = NO3-
  #  heavy_species_mass = 1.029640e-25
  #  heavy_species_charge = -1
  #  diffusivity = 0.9e-5 
  #  block = 1
  #[../]

  # Hydrogen species
  #[./gas_species_Hp]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = H+
  #  heavy_species_mass = 1.673597e-27
  #  heavy_species_charge = 1
  #  diffusivity = 8.8e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_H2p]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = H2+
  #  heavy_species_mass = 3.347526e-27
  #  heavy_species_charge = 1
  #  diffusivity = 7e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_H3p]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = H3+
  #  heavy_species_mass = 5.021289e-27
  #  heavy_species_charge = 1
  #  diffusivity = 9e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_OHp]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = OH+
  #  heavy_species_mass = 2.824311e-26
  #  heavy_species_charge = 1
  #  diffusivity = 4e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_H2Op]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = H2O+
  #  heavy_species_mass = 2.988e-26 
  #  heavy_species_charge = 1
  #  diffusivity = 5.9e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_H3Op]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = H3O+
  #  heavy_species_mass = 3.158951e-26 
  #  heavy_species_charge = 1
  #  diffusivity = 6e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_Hm]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = H-
  #  heavy_species_mass = 1.673597e-27
  #  heavy_species_charge = -1
  #  diffusivity = 8.8e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_OHm]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = OH-
  #  heavy_species_mass = 2.824311e-26
  #  heavy_species_charge = -1
  #  diffusivity = 7e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_H]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = H
  #  heavy_species_mass = 1.673597e-27
  #  heavy_species_charge = 0
  #  diffusivity = 8.8e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_H2]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = H2
  #  heavy_species_mass = 3.347526e-27
  #  heavy_species_charge = 0
  #  diffusivity = 7.8e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_OH]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = OH
  #  heavy_species_mass = 2.824311e-26
  #  heavy_species_charge = 0
  #  diffusivity = 4e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_HO2]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = HO2
  #  heavy_species_mass = 5.481069e-26
  #  heavy_species_charge = 0
  #  diffusivity = 2e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_H2O2]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = H2O2
  #  heavy_species_mass = 5.64829e-26
  #  heavy_species_charge = 0
  #  diffusivity = 2e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_HNO] # Nitroxyl
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = HNO
  #  heavy_species_mass = 5.150116e-26
  #  heavy_species_charge = 0
  #  diffusivity = 2.1e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_HNO2] # Nitrous acid
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = HNO2
  #  heavy_species_mass = 7.8087e-26
  #  heavy_species_charge = 0
  #  diffusivity = 2.1e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_HNO3] # Nitric acid
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = HNO3
  #  heavy_species_mass = 1.04633e-25
  #  heavy_species_charge = 0
  #  diffusivity = 2.1e-5
  #  block = 1
  #[../]
  #
  #[./gas_species_H2O]
  #  type = HeavySpeciesMaterial
  #  heavy_species_name = H2O
  #  heavy_species_mass = 2.988e-26
  #  heavy_species_charge = 0 
  #  diffusivity = 2.3e-5 
  #  block = 1
  #[../]
[]

[Reactions]
  [./DryAir]
    name = 'dry'
    species = 'em N2v N2* N2** N4+ N2+ N+ N N* O O* O- O+ O2- O2+ O3- O4- O2* O21S O3 NO+ NO NO2 NO3 N2O3 N2O4 N2O5'
    aux_species = 'N2 O2 NEUTRAL'
    reaction_coefficient_format = 'townsend'
    #reaction_coefficient_format = 'rate'
    gas_species = 'N2'
    electron_energy = 'mean_en'
    electron_density = 'em'
    include_electrons = true
    file_location = 'townsend'
    #file_location = 'townsend_100dp'
    #file_location = 'rate'
    equation_variables = 'Te'
    equation_constants = 'Tgas'
    equation_values = '300'
    potential = potential_dom1
    use_log = true
    position_units = ${dom0Scale}
    #track_rates = true
    #use_ad = true
    convert_to_moles = true
    #convert_to_meters = 1e-2
    block = 1


    # Reactions taken from this thesis:
    # Seth Norberg. MODELING ATMOSPHERIC PRESSURE PLASMA JETS: PLASMA DYNAMICS,
    # INTERACTION WITH DIELECTRIC SURFACES, LIQUID LAYERS AND CELLS
    reactions = 'em + N2 -> em + N2                         : EEDF [elastic] (C1_N2_Elastic)
                 em + N2 -> N2v + em                        : EEDF [-0.29] (C2_N2_Excitation_0.29_eV)
                 em + N2 -> N2* + em                        : EEDF [-6.17]  (C3_N2_Excitation_6.17_eV)
                 em + N2 -> N2* + em                        : EEDF [-7.35]  (C4_N2_Excitation_7.35_eV)
                 em + N2 -> N2** + em                       : EEDF [-11.03] (C6_N2_Excitation_11.03_eV)
                 em + N2 -> N2** + em                       : EEDF [-11.87] (C7_N2_Excitation_11.87_eV)
                 em + N2 -> N2** + em                       : EEDF [-12.25] (C8_N2_Excitation_12.25_eV)
                 em + N2 -> N2** + em                       : EEDF [-12.85] (C9_N2_Excitation_12.85_eV)
                 em + N2 -> N2** + em                       : EEDF [-12.94] (C10_N2_Excitation_12.94_eV)
                 em + N2 -> N + N + em                      : EEDF [-9.75] (C5_N2_Excitation_9.75_eV)
                 em + N2 -> N2+ + em + em                   : EEDF [-15.58] (C11_N2_Ionization_15.58_eV)
                 #em + N2v -> em + N2v                       : EEDF
                 em + N2v -> em + N2                        : EEDF [0.29] (C36_N2v1_De-excitation_0.29_eV)
                 #em + N2v -> N2* + em                       : EEDF
                 #em + N2v -> N2+ + em + em                  : EEDF
                 #em + N2* -> em + N2*                       : EEDF
                 em + N2* -> em + N2                        : EEDF [6.17] (C37_N2A3_De-excitation_6.17_eV)
                 em + N2* -> em + N2                        : EEDF [7.35] (C39_N2B3_De-excitation_7.35_eV)
                 em + N2* -> N2+ + em + em                  : EEDF [-10.79] (C38_N2A3_Ionization_10.79_eV)
                 #em + N2* -> em + N2v                       : EEDF
                 em + N2** -> em + N2                       : EEDF [11.03] (C40_N2C3_De-excitation_11.03_eV)
                 em + N -> em + N                           : EEDF [elastic] (C41_N_Elastic)
                 em + N -> em + N*                          : EEDF [-2.39] (C42_N_Excitation_2.39_eV)
                 em + N -> em + N*                          : EEDF [-3.57] (C43_N_Excitation_3.57_eV)
                 em + N -> em + em + N+                     : EEDF [-14.54] (C44_N_Ionization_14.54_eV)
                 em + N* -> em + N*                         : EEDF [elastic] (C45_N2p3_2Do_Elastic)
                 em + N* -> em + N*                         : EEDF [elastic] (C47_N2p3_2Po_Elastic)
                 em + N* -> em + N                          : EEDF [2.39] (C49_N2D_De-excitation_2.39_eV)
                 em + N* -> em + N                          : EEDF [3.57] (C50_N2P_De-excitation_3.57_eV)
                 em + N* -> em + em + N+                    : EEDF [-12.15] (C46_N2p3_2Do_Ionization_12.15_eV)
                 em + N* -> em + em + N+                    : EEDF [-10.97] (C48_N2p3_2Po_Ionization_10.97_eV)
                 ######################################################
                 # Additional reactions from larger model (just a few)
                 ######################################################
                 N2v + N -> N2 + N                          : {4.0e-22*(Tgas/300.0)^0.5}
                 N2v + O -> N2 + O                          : {1.20e-19 * exp(-27.6/Tgas^(1.0/3.0))}
                 em + O + O2 -> O- + O2                     : 1e-43
                 em + O + O2 -> O2- + O                     : 1e-43
                 em + O2 + N2 -> O2- + N2                   : {1.1e-43*(300/(Te*11600))^2*exp(-70/Tgas)*exp(1500*((Te*11600)-Tgas)/((Te*11600)*Tgas))}
                 N2* -> N2                                  : 0.5 
                 O2* -> O2                                  : 2.6e-4
                 #N2* + O -> N + O1D                         : 4e-19
                 #N2* + O2 -> NO + O                         : 5.2e-18
                 #N2* + NO -> N2 + O                         : 1.8e-16
                 ######################################################
                 # O3- AND O4- REACTIONS (added from smaller model)
                 #O4- + N2 -> O2- + O2 + N2                  : {1.0e-16 * exp(-1044/TeffN4)}
                 #O4- + O2 -> O2- + O2 + O2                  : {1.0e-16 * exp(-1044/TeffN4)}
                 #O-  + O2 + NEUTRAL -> O3- + NEUTRAL        : {1.1e-42 * (300./TeffN)}
                 #O2- + O2 + NEUTRAL -> O4- + NEUTRAL        : {3.5e-43 * (300./TeffN2)}
                 #O3- + N+ -> O3 + N                         : {2e-13 * (300/TionN)^0.5}
                 #O3- + N2+ -> O3 + N2                       : {2e-13 * (300/TionN)^0.5}
                 #O3- + O+ -> O3 + O                         : {2e-13 * (300/TionN)^0.5}
                 #O3- + O2+ -> O3 + O2                       : {2e-13 * (300/TionN)^0.5}
                 #O3- + NO+ -> O3 + NO                       : {2e-13 * (300/TionN)^0.5}
                 #O3- + N+ + NEUTRAL -> O3 + N + NEUTRAL     : {2e-37 * (300/TionN2)^2.5}
                 #O3- + N2+ + NEUTRAL -> O3 + N2 + NEUTRAL   : {2e-37 * (300/TionN2)^2.5}
                 #O3- + O+ + NEUTRAL -> O3 + O + NEUTRAL     : {2e-37 * (300/TionN2)^2.5}
                 #O3- + O2+ + NEUTRAL -> O3 + O2 + NEUTRAL   : {2e-37 * (300/TionN2)^2.5}
                 #O3- + NO+ + NEUTRAL -> O3 + NO + NEUTRAL   : {2e-37 * (300/TionN2)^2.5}
                 ######################################################
                 em + O3 + NEUTRAL -> O3- + NEUTRAL         : 1e-43
                 O3- + O -> O2  + O2 + em                   : 3.0e-16
                 O3- + N -> NO + O2 + em                    : 5e-16
                 #O3- + N2A3 -> O3 + N2 + em                 : 2.1e-15
                 #O3- + N2B3 -> O3 + N2 + em                 : 2.5e-15
                 O3- + N2* -> O3 + N2 + em                  : 4.6e-15
                 O- + O3 -> O3-  + O                        : 8.0e-16
                 O2- + O3 -> O3-  + O2                      : 3.5e-16
                 O3- + O -> O2-  + O2                       : 1.0e-17
                 O4- + N2 -> O2- + O2 + N2                  : {1.0e-16 * exp(-1044/300)}
                 O4- + O2 -> O2- + O2 + O2                  : {1.0e-16 * exp(-1044/300)}
                 O4- + O -> O3-  + O2                       : 4.0e-16
                 O4- + O -> O-   + O2  + O2                 : 3.0e-16
                 #O4- + O2a1 -> O2-  + O2  + O2              : 1.0e-16
                 #O4- + O2b1 -> O2-  + O2  + O2              : 1.0e-16
                 O4- + O2* -> O2- + O2  + O2                : 2.0e-16
                 O-  + O2 + NEUTRAL -> O3- + NEUTRAL        : 1.1e-42
                 O2- + O2 + NEUTRAL -> O4- + NEUTRAL        : 3.5e-43
                 O3- + N+ -> O3 + N                         : 2e-13
                 O3- + N2+ -> O3 + N2                       : 2e-13
                 O3- + O+ -> O3 + O                         : 2e-13
                 O3- + O2+ -> O3 + O2                       : 2e-13
                 O3- + NO+ -> O3 + NO                       : 2e-13
                 O3- + N2+ -> O3 + N + N                    : 1e-13
                 #O3- + N3+ -> O3 + N + N2                   : 1e-13
                 O3- + N4+ -> O3 + N2 + N2                  : 1e-13
                 O3- + O2+ -> O3 + O + O                    : 1e-13
                 #O3- + O4+ -> O3 + O2 + O2                 : 1e-13
                 O3- + N+ + NEUTRAL -> O3 + N + NEUTRAL     : 2e-37
                 O3- + N2+ + NEUTRAL -> O3 + N2 + NEUTRAL   : 2e-37
                 O3- + O+ + NEUTRAL -> O3 + O + NEUTRAL     : 2e-37
                 O3- + O2+ + NEUTRAL -> O3 + O2 + NEUTRAL   : 2e-37
                 O3- + NO+ + NEUTRAL -> O3 + NO + NEUTRAL   : 2e-37
                 O4- + N+ -> O2 + O2 + N                    : 1e-13 
                 O4- + N2+ -> O2 + O2 + N2                  : 1e-13 
                 O4- + O+ -> O2 + O2 + O                    : 1e-13 
                 O4- + O2+ -> O2 + O2 + O2                  : 1e-13 
                 O4- + NO+ -> O2 + O2 + NO                  : 1e-13 
                 O4- + N4+ -> O2 + O2 + N2 + N2             : 1e-13 
                 ######################################################
                 # O2 REACTIONS
                 ######################################################
                 em + O2 -> em + O2                         : EEDF [elastic] (C13_O2_Elastic)
                 em + O2 -> O + O-                          : EEDF (C12_O2_Attachment)
                 em + O2 -> em + O2*                        : EEDF [-0.98] (C14_O2_Excitation_0.98_eV)
                 em + O2 -> em + O21S                       : EEDF [-1.63] (C15_O2_Excitation_1.63_eV)
                 #em + O2 -> em + O + O                      : EEDF
                 em + O2 -> em + O + O*                     : EEDF [-4.6] (C23_O20.98_Excitation_4.60_eV)
                 em + O2 -> em + em + O2+                   : EEDF [-11.1] (C25_O20.98_Ionization_11.10_eV)
                 em + O2 -> em + em + O + O+                : EEDF [-18.52] (C26_O20.98_Ionization_18.52_eV)
                 em + O2* -> O + O-                         : EEDF (C20_O20.98_Attachment)
                 em + O2* -> em + O2*                       : EEDF [elastic] (C21_O20.98_Elastic)
                 em + O2* -> em + O21S                      : EEDF [-0.65] (C22_O20.98_Excitation_0.65_eV)
                 em + O2* -> em + O2                        : EEDF [0.98] (C27_O20.98_De-excitation_0.98_eV)
                 em + O2* -> em + O + O                     : EEDF [-4.6] (C23_O20.98_Excitation_4.60_eV)
                 em + O2* -> em + O + O*                    : EEDF [-6.34] (C24_O20.98_Excitation_6.34_eV)
                 em + O2* -> em + em + O2+                  : EEDF [-11.10] (C25_O20.98_Ionization_11.10_eV)
                 em + O2* -> em + em + O + O+               : EEDF [-18.52] (C26_O20.98_Ionization_18.52_eV)
                 #em + O21S -> em + O21S                     : EEDF
                 em + O21S -> em + O21S                     : EEDF [elastic] (C30_O21.63_Elastic) 
                 em + O21S -> O + O-                        : EEDF (C29_O21.63_Attachment)
                 em + O21S -> em + O2*                      : EEDF [0.65] (C28_O21.63_De-excitation_0.65_eV)
                 em + O21S -> em + O2                       : EEDF [1.63] (C35_O21.63_De-excitation_1.63_eV)
                 em + O21S -> em + O + O                    : EEDF [-3.95] (C31_O21.63_Excitation_3.95_eV)
                 em + O21S -> em + O + O*                   : EEDF [-6.77] (C32_O21.63_Excitation_6.77_eV)
                 em + O21S -> em + em + O2+                 : EEDF [-10.45] (C33_O21.63_Ionization_10.45_eV)
                 em + O21S -> em + em + O + O+              : EEDF [-17.87] (C34_O21.63_Ionization_17.87_eV)
                 em + O -> em + O                           : EEDF [elastic] (C53_O_Elastic)
                 em + O -> em + O*                          : EEDF [-1.96] (C54_O_Excitation_1.96_eV)
                 em + O -> em + O*                          : EEDF [-4.18] (C55_O_Excitation_4.18_eV)
                 em + O -> em + em + O+                     : EEDF [-13.6] (C56_O_Ionization_13.60_eV)
                 #em + O* -> em + O*                         : EEDF
                 em + O* -> em + O                          : EEDF [1.96] (C51_O1D_De-excitation_1.96_eV)
                 em + O* -> em + O                          : EEDF [4.18] (C52_O1S_De-excitation_4.18_eV)
                 #em + O* -> em + em + O+                    : EEDF
                 em + O3 -> O- + O2                         : EEDF (C58_O3_Attachment)
                 em + O3 -> O2- + O                         : EEDF (C59_O3_Attachment)
                 em + NO -> NO+ + em + em                   : EEDF [-9.26] (C57_NO_Ionization_9.26_eV)
                 em + N2+ -> N + N*                         : {2e-13*(Te^(-0.5))}
                 em + N4+ -> N2 + N2                        : {2e-13*(Te^(-0.5))}
                 em + O+ -> O*                              : {5.3e-18*(Te^(-0.5))}
                 em + em + O+ -> em + O*                    : {5.12e-39*(Te^(-4.5))}
                 em + O2+ -> O + O                          : {1.2e-14*(Te^(-0.7))}
                 em + O2+ -> O + O*                         : {8.88e-15*(Te^(-0.7))}
                 #em + O2+ -> O + O                   : {2.7e-13 * (300/Te)^0.7 * 0.55}
                 #em + O2+ -> O + O1D                 : {2.7e-13 * (300/Te)^0.7 * 0.40}
                 #em + O2+ -> O + O1S                 : {2.7e-13 * (300/Te)^0.7 * 0.05}
                 em + NO+ -> N + O                          : {2e-13*(Te^(-0.5))}
                 em + O2 + NEUTRAL -> O2- + NEUTRAL         : {2e-43*(Te^(-1))}
                 em + O2* + NEUTRAL -> O2- + NEUTRAL        : 1e-41
                 em + NO+ + NEUTRAL -> NO + NEUTRAL         : {3.12e-35*(Te^(-1.5))}
                 ###########################################################
                 # ION RECOMBINATION
                 ###########################################################
                 O- + N2+ -> N2 + O                         : 3e-12
                 O- + N+ -> N + O                           : 3e-12
                 O- + N4+ -> N2 + N2 + O                    : 3e-12
                 O- + O2+ -> O2 + O                         : 3e-12
                 O- + O+ -> O + O                           : 3e-12
                 O- + NO+ -> NO + O                         : 3e-12
                 O- + O2+ -> O + O + O                      : 1e-13
                 O- + N+ -> O + N                           : {2e-13*(Tgas/300)^(-0.5)}
                 O- + N2+ -> O + N + N                      : 1e-13
                 O- + NO+ -> O + N + O                      : 1e-13
                 O- + NO+ -> O + NO                         : {2e-13*(Tgas/300)^(-0.5)}
                 O- + NO+ + NEUTRAL -> O + NO + NEUTRAL     : {2e-37*(Tgas/300)^(-2.5)}
                 O- + NO+ + NEUTRAL -> NO2 + NEUTRAL        : {2e-37*(Tgas/300)^(-2.5)}
                 O- + O+ + NEUTRAL -> O2 + NEUTRAL          : 1.2e-37
                 O- + N+ + NEUTRAL -> NO + NEUTRAL          : 1.2e-37
                 O- + O2+ + NEUTRAL -> O + O2 + NEUTRAL     : {2e-37*(Tgas/300)^(-2.5)}
                 O2- + N2+ -> N2 + O2                       : 2e-12
                 O2- + N+ -> N2 + O2                        : 2e-12
                 O2- + N4+ -> N2 + N2 + O2                  : 2e-12
                 O2- + O2+ -> O2 + O2                       : 2e-12
                 O2- + O+ -> O + O2                         : 2e-12
                 O2- + NO+ -> O2 + NO                       : 2e-12
                 O2- + O2+ -> O2 + O + O                    : 1e-13
                 O2- + N+ -> O2 + N                         : {2e-13*(Tgas/300)^(-0.5)}
                 O2- + N2+ -> O2 + N + N                    : 1e-13
                 O2- + NO+ -> O2 + N + O                    : 1e-13
                 O2- + NO+ -> O2 + NO                       : {2e-13*(Tgas/300)^(-0.5)}
                 O2- + NO+ -> N + O + O + O                 : 1e-13
                 O2- + NO+ + NEUTRAL -> NO3 + NEUTRAL       : {2e-37*(Tgas/300)^(-2.5)}
                 O2- + NO+ + NEUTRAL -> O2 + NO + NEUTRAL   : {2e-37*(Tgas/300)^(-2.5)}
                 O- + O2 -> O2- + O                         : 1.5e-26
                 O- + O21S -> O + O2 + em                   : {6.9e-16*(Tgas/300)^(0.5)}
                 O- + O -> O2 + em                          : 1.9e-16
                 O- + O3 -> O2 + O2 + em                    : {3.01e-16*(Tgas/300)^(0.5)}
                 O- + O3 -> O2- + O2                        : 1.02e-17
                 O2- + O -> O3 + em                         : 1.5e-16
                 O2- + O -> O- + O2                         : 3.3e-16
                 O2- + O2* -> em + O2 + O2                  : 2e-16
                 N2+ + O2 -> NO + NO+                       : 1e-23
                 O2+ + N2 -> NO + NO+                       : 1e-23
                 O- + N -> NO + em                          : 2.6e-16
                 O- + N2* -> N2 + O + em                    : 1.9e-15
                 O- + O2 -> O3 + em                         : 1e-18
                 O- + O2* -> O3 + em                        : 3e-16
                 O- + O3 -> O2 + O2 + em                    : 3e-16
                 O- + NO -> NO2 + em                        : 2.6e-16
                 O- + O2* -> O2- + O                        : 1e-16
                 O2- + N2 -> N2 + O2 + em                   : {1.9e-18*(Tgas/300)^0.5 * exp(-4990/Tgas)}
                 O2- + N -> NO2 + em                        : 5e-16
                 O2- + N2* -> N2 + O2 + em                  : 2.1e-15
                 O2- + O2 -> O2 + O2 + em                   : {2.7e-16*(Tgas/300)^0.5 * exp(-5590/Tgas)}
                 O2- + O3 -> O3 + O2 + em                   : 6e-16
                 N+ + O2 -> NO+ + O                         : 2.7e-16
                 N+ + O2 -> O+ + NO                         : 3.6e-17
                 N+ + O2 -> O2+ + N                         : 3.1e-16
                 N+ + NO -> NO+ + N                         : 9e-16
                 N2+ + O -> NO+ + N                         : 1.4e-16
                 N2+ + O -> NO+ + N*                        : {1.8e-16*(Tgas/300)^0.5}
                 N2+ + N2 + NEUTRAL -> N4+ + NEUTRAL        : {6.8e-41*(Tgas/300)^(-1.64)}
                 O+ + N + NEUTRAL -> NO+ + NEUTRAL          : 1e-41
                 O+ + N2 + NEUTRAL -> NO+ + N + NEUTRAL     : 1e-41
                 O+ + O + NEUTRAL -> NO+ + N + NEUTRAL      : 1e-41
                 O+ + O2 -> O2+ + O                         : {2.1e-17*(Tgas/300)^(-0.5)}
                 O+ + O3 -> O2+ + O2                        : 1e-16
                 O+ + N* -> N+ + O                          : 1.3e-16
                 O+ + NO -> NO+ + O                         : 1.7e-18
                 O2+ + N -> NO+ + O                         : 1.5e-16
                 O2+ + NO -> NO+ + O2                       : 4.6e-16
                 N+ + O2 -> O2+ + N                         : 3.1e-16
                 N+ + O -> O+ + N                           : 1e-18
                 N+ + N -> N + N+                           : 1e-18
                 N2+ + N -> N+ + N2                         : 5e-18
                 N2+ + N* -> N+ + N2                        : 1e-16
                 N2+ + O2 -> O2+ + N2                       : 5.1e-17
                 N4+ + O2 -> O2+ + N2 + N2                  : 2.4e-16
                 N2+ + NO -> NO+ + N2                       : 3.9e-16
                 N2+ + O -> O+ + N2                         : {1e-17*(Tgas/300)^(-0.5)}
                 N4+ + N2 -> N2+ + N2 + N2                  : {2.1e-16*exp(121/Tgas)}
                 N4+ + N -> N+ + N2 + N2                    : 1.e-17
                 N4+ + NO -> NO+ + N2 + N2                  : 3.9e-16
                 N4+ + O -> O+ + N2 + N2                    : 2.5e-16
                 O+ + O2 -> O2+ + O                         : 1.9e-17
                 #O+ + O -> O + O+                           : 1e-18
                 #O2+ + O2 -> O2 + O2+                       : 1e-15
                 ##########################################################
                 # METASTABLE QUENCHING
                 ##########################################################
                 O* + O3 -> O2 + O + O                      : 1.2e-16
                 O* + O3 -> O2 + O2                         : 5.04e-16
                 O* + O2* -> O + O2                         : 1e-17
                 O* + O -> O + O                            : 1e-17
                 O* + N2 -> O + N2                          : {1.8e-17*exp(107/Tgas)}
                 O* + O2 -> O + O2                          : 3.8e-17
                 O* + NO -> O2 + N                          : 8.5e-17
                 O* + NO2 -> O2 + NO                        : 1.4e-16
                 O21S + O21S -> O2* + O2                    : {3.6e-23*(Tgas/300)^0.5}
                 O21S + O2 -> O2* + O2                      : {3.6e-23*(Tgas/300)^0.5}
                 O21S + O2 -> O2 + O2                       : {4e-24*(Tgas/300)^0.5}
                 O21S + O -> O2* + O                        : {7.2e-20*(Tgas/300)^0.5}
                 O21S + O -> O2 + O                         : {8e-21*(Tgas/300)^0.5}
                 O21S + O3 -> O + O2 + O2                   : {7.33e-18*(Tgas/300)^0.5}
                 O21S + O3 -> O2* + O3                      : {7.33e-18*(Tgas/300)^0.5}
                 O21S + O3 -> O2 + O3                       : {7.33e-18*(Tgas/300)^0.5}
                 O2* + O2 -> O2 + O2                        : 2.2e-24
                 O2* + O2* -> O21S + O2                     : {9e-23*exp(-560/Tgas)}
                 O2* + O2 -> O + O3                         : 2.95e-27
                 O2* + O3 -> O2 + O2 + O                    : {9.96e-17*exp(-3050/Tgas)}
                 N* + N2 -> N + N2                          : 2.4e-20
                 N2* + N2 -> N2 + N2                        : 1.9e-18
                 N2* + O2 -> O + O + N2                     : 1.5e-18
                 N2* + O2 -> O2 + N2                        : 2.8e-17
                 N2* + NO2 -> NO + O + N2                   : 1e-18
                 N2v + N2 -> N2 + N2                        : 1e-21
                 N2v + N -> N2 + N                          : 1e-22
                 N2v + O2 -> N2 + O2                        : 1e-21
                 N2v + O -> N2 + O                          : 1e-22
                 ##########################################################
                 # THREE BODY NEUTRAL RECOMBINATION
                 ##########################################################
                 O + O2 + NEUTRAL -> O3 + NEUTRAL           : {3.4e-46*(Tgas/300)^(-1.2)}
                 O + O + NEUTRAL -> O2 + NEUTRAL            : 1.18e-45
                 O + O + NEUTRAL -> O2* + NEUTRAL           : 9.88e-47
                 N + N + NEUTRAL -> N2 + NEUTRAL            : 3.9e-45
                 N + O + NEUTRAL -> NO + NEUTRAL            : {5.46e-45*exp(155/Tgas)}
                 NO + O + NEUTRAL -> NO2 + NEUTRAL          : {1e-43*(Tgas/300)^(-1.6)}
                 NO + O + O2* -> NO2 + O2*                  : {1e-43*(Tgas/300)^(-1.6)}
                 NO + O + O3 -> NO2 + O3                    : {1e-43*(Tgas/300)^(-1.6)}
                 NO + O + O -> NO2 + O                      : {1e-43*(Tgas/300)^(-1.6)}
                 ##########################################################
                 # HIGHER TEMPERATURE AND CRITICAL REACTIONS
                 ##########################################################
                 O + O3 -> O2 + O2                          : {8e-18*exp(-2060/Tgas)}
                 O3 + NEUTRAL -> O2 + O + NEUTRAL           : {1.56e-15*exp(-11490/Tgas)}
                 N2 + NEUTRAL -> N + N + NEUTRAL            : {4.29e-16*exp(-86460/Tgas)}
                 O2 + NEUTRAL -> O + O + NEUTRAL            : {5.17e-16*exp(-58410/Tgas)}
                 ##########################################################
                 # NO and NxOy REACTIONS
                 ##########################################################
                 N + O2 -> NO + O                           : {4.4e-18*exp(-3270/Tgas)}
                 N + O3 -> NO + O2                          : 5e-22
                 N + NO2 -> NO + NO                         : {1.33e-18*exp(220/Tgas)}
                 NO + O3 -> O2 + NO2                        : {1.4e-18*exp(-1310/Tgas)}
                 NO + O2* -> O2 + NO                        : 3.5e-23
                 NO + O2* -> O + NO2                        : 4.88e-24
                 N* + O2 -> NO + O                          : {1.22e-17*exp(-317/Tgas)}
                 N* + O2 -> NO + O*                         : {6e-18*(Tgas/300)^0.5}
                 N* + NO -> N2 + O                          : 6.3e-17
                 N* + NO2 -> NO + NO                        : 1.5e-18
                 N2** + O -> NO + N                         : 5e-16
                 N2* + O -> NO + N                          : 5e-16
                 O + N2* -> NO + N*                         : 1e-18
                 O + NO2 -> NO + O2                         : {6.5e-18*exp(120/Tgas)}
                 O + NO2 -> O2 + NO2                        : 1e-17
                 O* + NO2 -> NO + O2                        : 3e-16
                 O2* + N -> O + NO                          : {2e-20*exp(-600/Tgas)}
                 O21S + N -> O + NO                         : 2.5e-16
                 O3 + N -> NO + O2                          : 5e-22
                 O3 + N* -> NO + O2                         : 1e-16
                 O3 + N2* -> NO + NO + O                    : 8.4e-18
                 O3 + N2** -> NO + NO + O                   : 8.4e-18
                 NO2 + O2* -> O2 + NO2                      : 5e-24
                 NO2 + O -> O2 + NO                         : {4.21e-18*exp(273/Tgas)}
                 NO2 + O + NEUTRAL -> NO3 + NEUTRAL         : {9e-44*(Tgas/300)^(-2)}
                 N + NO -> N2 + O                           : 3.14e-17
                 O + NO + NEUTRAL -> NO2 + NEUTRAL          : 1e-43
                 ##########################################################
                 # PATH TO NxOy and HNOx
                 ##########################################################
                 NO + NO2 -> N2O3                           : 7.9e-18
                 NO + NO O2 -> NO2 + NO2                    : 2e-50
                 NO + NO2 + NEUTRAL -> N2O3 + NEUTRAL       : 3.1e-46
                 NO + NO3 -> NO2 + NO2                      : {1.6e-17*exp(150/Tgas)}
                 NO2 + O3 -> NO + O2 + O2                   : 1e-24
                 NO2 + O3 -> O2 + NO3                       : {1.4e-18*exp(-2470/Tgas)}
                 NO2 + NO2 -> N2O4                          : 1e-18
                 NO2 + NO2 + NEUTRAL -> N2O4 + NEUTRAL      : 1.4e-45
                 NO3 + NO2 -> N2O5                          : 1.9e-18
                 NO3 + NO2 + NEUTRAL -> N2O5 + NEUTRAL      : 3.6e-42
                 NO3 + NO3 -> NO2 + NO2 + O2                : 1.2e-21
                 NO3 + NO2 -> NO2 + NO + O2                 : {8.21e-20*exp(-1480/Tgas)}
                 NO3 + NEUTRAL -> NO + O2 + NEUTRAL         : {1.94e-18*exp(-1610/Tgas)}
                 ##########################################################
                 # OTHER POSSIBLE REACTIONS? (From Moon Soo Bak, Mark A. Cappelli. 
                 # "A Reduced Set of Air Plasma Reactions for Nanosecond Pulsed Plasmas."
                 # IEEE Transactions on Plasma Science, Vol. 43, No. 4, April 2015
                 ##########################################################

                 # RADIATION
                 ##########################################################
                 N2** -> N2                                 : 2e8
                 N2** -> N2*                                : 2e8'
                 #O2 -> O2+ + em                             : 1e-15
                 #N2 -> N2+ + em                             : 1e-15'
  [../]
[]
