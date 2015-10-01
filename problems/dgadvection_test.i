[GlobalParams]
	vx = 2.0
	vy = 0.0
	vz = 0.0
	u_input = 1.0
[]

[Mesh]
	type = GeneratedMesh
	dim = 2
	nx = 10
	ny = 4
	xmax = 1.0
	ymax = 1.0
[]

# [MeshModifiers]
# 	[./middle_nodeset]
# 		type = AddExtraNodeset
# 		new_boundary = 'middle_nodeset'
# 		coord = '0.5 0 0.5 0.25 0.5 0.5 0.5 0.75 0.5 1.0'
# 	[../]
# []

[Variables]

	[./u]
		order = FIRST
		family = L2_LAGRANGE
		initial_condition = 0.0
	[../]

[]

[AuxVariables]

[]

[ICs]

[]

[Kernels]

	[./u_dot]
		type = CoefTimeDerivative
		variable = u
		Coefficient = 1.0
	[../]

	[./u_gadv]
		type = GAdvection
		variable = u
	[../]
	[./u_gdiff]
		type = Diffusion
		variable = u
	[../]
	
[]

[DGKernels]

	[./u_dgadv]
		type = DGAdvection
		variable = u
	[../]
	# [./u_dgdiff]
	# 	type = DGDiffusion
	# 	variable = u
	# 	epsilon = -1
	# 	sigma = 1
	# 	# _boundary_id = 'middle_nodeset'
	# [../]

[]

[AuxKernels]

[]

[BCs]

	[./u_bcs]
		type = DGFluxBC
		variable = u
		boundary = 'top bottom left right'
	[../]

[]

[Materials]

[]

[Postprocessors]

	[./u_exit]
		type = SideAverageValue
		boundary = 'right'
		variable = u
	[../]

	[./u_enter]
		type = SideAverageValue
		boundary = 'left'
		variable = u
	[../]

[]

[Executioner]

type = Transient
scheme = bdf2

nl_rel_tol = 1e-06
picard_abs_tol = 1e-10
nl_abs_tol = 1e-10
nl_rel_step_tol = 1e-10
picard_rel_tol = 1e-10
nl_abs_step_tol = 1e-10

solve_type = PJFNK
start_time = 0.0
end_time = 1.0
petsc_options_iname = '-pc_type -pc_hypre_type'
petsc_options_value = 'hypre boomeramg'

[./TimeStepper]
	type = ConstantDT
	dt = 0.05
[../]

[]

[Adaptivity]

	marker = ef

	[./Indicators]
		[./u_grad_error]
			type = GradientJumpIndicator
			variable = u
		[../]

	[../]

	[./Markers]
		[./ef]
			type = ErrorFractionMarker
			indicator = u_grad_error
		[../]
	[../]

[]

[Outputs]
	exodus = true
	csv = true
[]
