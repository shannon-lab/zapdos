[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 20
  xmax = 2
  xmin = 0
[]

[MeshModifiers]
  [./vacuum]
    type = SubdomainBoundingBox
    bottom_left = '1 0 0'
    top_right = '2 0 0'
    block_id = 1
  [../]
  # [./interface]
  #   type = SideSetsBetweenSubdomains
  #   master_block = '1'
  #   paired_block = '0'
  #   new_boundary = 'interface'
  #   depends_on = 'vacuum'
  # [../]
[]


[Problem]
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
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
[]

[Outputs]
  perf_graph = true
  print_linear_residuals = false
  [./out]
    type = Exodus
  [../]
[]

[Kernels]
  [./curl_z]
    type = AxisymmetricCurlZ
    variable = Bphi
  [../]
  [./source]
    type = UserSource
    variable = Bphi
    source_magnitude = 1
    block = 0
  [../]
[]

[Variables]
  [./Bphi]
  [../]
[]

[BCs]
  [./center_of_wire]
    type = DirichletBC
    boundary = left
    variable = Bphi
    value = 0
  [../]
[]
