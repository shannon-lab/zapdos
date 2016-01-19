[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1
  xmax = 1
[]


[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
  [./v]
  [../]
  [./w]
  [../]
  [./Arp]
  [../]
[]

[Kernels]
  [./test_u]
    type = Diffusion
    variable = u
  [../]
  [./diff_v]
    type = Diffusion
    variable = v
  [../]
  [./diff_w]
    type = Diffusion
    variable = w
  [../]
  [./diff_Arp]
    type = Diffusion
    variable = Arp
  [../]
[]

[BCs]
  [./both]
    type = NeumannCircuitVoltageMoles_KV
    variable = u
    boundary = 'left right'
    em = v
    mean_en = w
    ip = Arp
    r = 0.5
    function = potential_bc_func
    data_provider = data_provider
    potential_units = V
  [../]
[]

[ICs]
  [./u_ic]
    type = RandomIC
    variable = u
  [../]
  [./v_ic]
    type = RandomIC
    variable = v
  [../]
  [./w_ic]
    type = RandomIC
    variable = w
  [../]
  [./Arp_ic]
    type = RandomIC
    variable = Arp
  [../]
[]

[Materials]
  [./jac_block]
    block = '0'
    type = JacMat
    em = v
    mean_en = w
  [../]
  [./jac_boundary]
    boundary = 'left right'
    type = JacMat
    em = v
    mean_en = w
  [../]
[]

[Preconditioning]
  [./fdp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  petsc_options = '-options_left -snes_test_display'
  petsc_options_iname = '-snes_type'
  petsc_options_value = 'test'
[]

[Outputs]
  exodus = true
  print_linear_residuals = false
  # [./DOFMap]
  #   type = DOFMap
  # [../]
[]

[Debug]
  show_var_residual_norms = true
[]

[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    value = 1.25
  [../]
[]

[UserObjects]
  [./data_provider]
    type = ProvideMobility
    electrode_area = 1.1
    ballast_resist = 1.1
    e = 1.1
  [../]
[]
