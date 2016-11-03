dom0Scale = 1
d = .1
m = 1

[GlobalParams]
  mu = ${m}
  diff = ${d}
  muem = ${m}
  diffem = ${d}
  alpha_iz = 1
  EField = -1
[]

[Mesh]
	type = GeneratedMesh
        nx = 10
        dim = 1
        xmax = 1
[]

[Problem]
	type = FEProblem
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
  # end_time = 10
  # trans_ss_check = 1
  # ss_check_tol = 1E-10
  # dt = .1
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
  nl_rel_tol = 1e-8
  nl_abs_tol = 1e-10
[]

[Outputs]
	print_perf_log = true
	print_linear_residuals = false
	[./out]
		type = Exodus
#		execute_on = 'final'
	[../]
[]

[Debug]
	show_var_residual_norms = true
[]


[Kernels]
  # [./em_time_deriv]
  # 	type = ElectronTimeDerivative
  # 	variable = em
  # [../]
  [./em_leakage]
  	variable = em
          sign = -1
  	position_units = ${dom0Scale}
        use_material_props = false
        type = DriftDiffusion
  [../]
  [./em_ionization]
  	type = ElectronsFromIonization
  	variable = em
          em = em
          position_units = ${dom0Scale}
          use_material_props = false
  [../]
  # [./Arp_time_deriv]
  # 	type = ElectronTimeDerivative
  # 	variable = Arp
  # [../]
  [./Arp_leakage]
  	variable = Arp
          sign = 1
  	position_units = ${dom0Scale}
        use_material_props = false
          type = DriftDiffusion
  [../]
  [./Arp_ionization]
  	type = ElectronsFromIonization
  	variable = Arp
          em = em
          position_units = ${dom0Scale}
          use_material_props = false
  [../]
[]

[Variables]
	[./em]
	[../]
	[./Arp]
	[../]
[]

[AuxVariables]
  [./x]
  	order = CONSTANT
  	family = MONOMIAL
  [../]
  [./x_node]
  [../]
  # [./em_lin]
  # 	order = CONSTANT
  # 	family = MONOMIAL
  # [../]
  # [./Arp_lin]
  # 	order = CONSTANT
  # 	family = MONOMIAL
  # [../]
  [./flux_em]
  	order = CONSTANT
  	family = MONOMIAL
  [../]
  [./flux_Arp]
  	order = CONSTANT
  	family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./x_g]
  	type = Position
  	variable = x
  	position_units = ${dom0Scale}
  [../]
  [./x_ng]
  	type = Position
  	variable = x_node
  	position_units = ${dom0Scale}
  [../]
  # [./em_lin]
  # 	type = Density
  #       use_moles = false
  # 	convert_moles = false
  # 	variable = em_lin
  # 	density_log = em
  # [../]
  # [./Arp_lin]
  # 	type = Density
  # 	convert_moles = false
  #       use_moles = false
  # 	variable = Arp_lin
  # 	density_log = Arp
  # [../]
  [./flux_em]
    type = UserFlux
    variable = flux_em
    density_log = em
    sign = -1
  [../]
  [./flux_Arp]
    type = UserFlux
    variable = flux_Arp
    density_log = Arp
    sign = 1
  [../]
[]

[BCs]
  [./em_left]
    boundary = left
    type = NeumannBC
    value = 1
    variable = em
  [../]
  # [./em_left]
  #   boundary = left
  #   type = DirichletBC
  #   variable = em
  #   value = 1
  # [../]
  [./em_right]
    type = DriftDiffusionDoNothingBC
    boundary = right
    sign = -1
    variable = em
    position_units = ${dom0Scale}
    use_material_props = false
  [../]
  [./Arp_left]
    boundary = left
    sign = 1
    variable = Arp
    position_units = ${dom0Scale}
    use_material_props = false
    type = DriftDiffusionDoNothingBC
  [../]
  [./Arp_right]
    boundary = right
    type = NeumannBC
    value = 0
    variable = Arp
  [../]
[]

[ICs]
  [./em]
    type = ConstantIC
    variable = em
    value = 0
  [../]
  # [./Arp]
  #   type = ConstantIC
  #   variable = Arp
  #   value = 1
  # [../]
[]
