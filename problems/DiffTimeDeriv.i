[Mesh]
  type = GeneratedMesh
  nx = 10
  ny = 10
  xmax = 10
  ymax = 10
  dim = 2
[]

[Kernels]
  [./time_deriv]
    type = TimeDerivative
    variable = u
    save_in = 'total_aux time_deriv_aux'
  [../]
  [./diff]
    type = Diffusion
    variable = u
    save_in = 'total_aux diff_aux'
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    value = 1
    variable = u
    boundary = left
  [../]
  [./right]
    type = DirichletBC
    value = 0
    variable = u
    boundary = right
  [../]
[]

[Executioner]
  type = Transient
  dt = 1
  end_time = 10
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'timestep_end'
  [./csv]
    type = CSV
    output_nonlinear = false
    output_linear = true
  [../]
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./time_deriv_aux]
  [../]
  [./diff_aux]
  [../]
  [./total_aux]
  [../]
[]

[Postprocessors]
  [./time_deriv_contrib]
    type = NodalL2Norm
    variable = time_deriv_aux
    execute_on = 'linear'
    block = 0
    outputs = 'csv'
  [../]
  [./diff_contrib]
    type = NodalL2Norm
    variable = diff_aux
    execute_on = 'linear'
    block = 0
    outputs = 'csv'
  [../]
  [./total_contrib]
    type = NodalL2Norm
    variable = total_aux
    execute_on = 'linear'
    block = 0
    outputs = 'csv'
  [../]
[]
