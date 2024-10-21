[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1
[]

[Variables]
  [./e]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  [../]

  [./Ar]
    family = SCALAR
    order = FIRST
    initial_condition = 2.5e19
    scaling = 2.5e-19
  [../]

  [./Ar+]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  [../]
[]

[ScalarKernels]
  [./de_dt]
    type = ODETimeDerivative
    variable = e
  [../]

  [./dAr_dt]
    type = ODETimeDerivative
    variable = Ar
  [../]

  [./dAr+_dt]
    type = ODETimeDerivative
    variable = Ar+
  [../]
[]

[ChemicalReactions]
  [./ScalarNetwork]
    species = 'e Ar Ar+'
    file_location = 'Example5'
    sampling_variable = 'reduced_field'
    track_rates = true
    # Add reactions here
    reactions = 'e + Ar -> e + e + Ar+   : EEDF
                 e + Ar+ + Ar -> Ar + Ar : 1e-25
                 Ar+ -> Ar+               : 1e-5'

   [../]
[]

[AuxVariables]
  [./reduced_field]
    order = FIRST
    family = SCALAR
    initial_condition = 50e-21
  [../]
 [./Production0]
    order = FIRST
    family = SCALAR
  [../]   
 
 [./Production1]
    order = FIRST
    family = SCALAR
  [../]   
 [./Production2]
    order = FIRST
    family = SCALAR
  [../]    
[]

[AuxScalarKernels]

  [./Prod2_Calc]
    type = ProductionFirstOrder
    variable = Production2
    v = 'Ar+'
    rate_coefficient = 'rate_constant2' 
    coefficient = 1
    execute_on = 'TIMESTEP_BEGIN'
  [../]
  [./Prod0_Calc]
    type = ProductionSecondOrder
    variable = Production0
    v = 'e'
    w = 'Ar'
    rate_coefficient = 'rate_constant0' 
    coefficient = 1
    execute_on = 'TIMESTEP_BEGIN'
  [../]
  
  [./Prod1_Calc]
    type = ProductionThirdOrder
    variable = Production1
    v = 'e'
    w = 'Ar'
    z = 'Ar+'
    rate_coefficient = 'rate_constant1'
    coefficient = 1 
    execute_on = 'TIMESTEP_BEGIN'
  [../]
[]

[Executioner]
  type = Transient
  end_time = 0.28e-6
  dt = 1e-9
  solve_type = NEWTON
  line_search = basic
  nl_rel_tol = 1e-5
  # nl_abs_tol = 7.6e-2
  # petsc_options_iname = '-pc_type -ksp_type -snes_linesearch_minlambda'
  # petsc_options_value = 'lu preonly 1e-3'
  # petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  # petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
  # petsc_options_iname = '-snes_linesearch_type'
  # petsc_options_value = 'basic'
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    # ksp_norm = none
  [../]
[]

[Outputs]
  csv = true
  interval = 10
  [./console]
    type = Console
    #execute_scalars_on = 'none'
  [../]
[]
