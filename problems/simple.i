[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  xmin = 0
  xmax = 1
[]

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
[]

[Executioner]
  type = Steady
 solve_type = NEWTON
[]

[Outputs]
  exodus = true
[]

[Debug]
  show_var_residual_norms = true
[]

[Kernels]
  active = 'transport'
  [./time_deriv]
    type = TimeDerivative
    variable = u
  [../]
  [./transport]
    type = CoupledDiffusion
    variable = u
  [../]
[]

[Variables]
  [./u]
  [../]
[]

[BCs]
  [./u_left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 1
  [../]
  [./u_right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 0
  [../]
[]

[Materials]
  [./dummy]
    type = ArgonConstTD
    block = 0
    mean_en = u
    interp_trans_coeffs = true
  [../]
[]

[ICs]
  [./u_begin]
    type = ConstantIC
    variable = u
    value = 0
  [../]
[]
