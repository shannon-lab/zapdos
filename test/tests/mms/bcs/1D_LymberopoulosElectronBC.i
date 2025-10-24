[Mesh]
  [geo]
    type = FileMeshGenerator
    file = 'LymberopoulosElectronBC_LeftBC_IC_out.e'
    #file = 'LymberopoulosElectronBC_RightBC_IC_out.e'
    use_for_exodus_restart = true
  []
  [left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = geo
  []
  [right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  []
[]

[Outputs]
  file_base = 'LymberopoulosElectronBC_LeftBC_out'
  #file_base = 'LymberopoulosElectronBC_RightBC_out'
  perf_graph = true
  [out]
    type = Exodus
    time_step_interval = 10
  []
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [em]
    initial_from_file_var = em
  []

  [potential]
    initial_from_file_var = potential
  []
  [ion]
    initial_from_file_var = ion
  []
[]

[Kernels]
#Electron Equations
  [em_time_derivative]
    type = TimeDerivativeLog
    variable = em
  []
  [em_diffusion]
    type = CoeffDiffusion
    variable = em
    position_units = 1.0
  []
  [em_advection]
    type = EFieldAdvection
    variable = em
    position_units = 1.0
  []
  [em_source]
    type = BodyForce
    variable = em
    function = 'em_source'
  []

#Ion Equations
  [ion_time_derivative]
    type = TimeDerivativeLog
    variable = ion
  []
  [ion_diffusion]
    type = CoeffDiffusion
    variable = ion
    position_units = 1.0
  []
  [ion_advection]
    type = EFieldAdvection
    variable = ion
    position_units = 1.0
  []
  [ion_source]
    type = BodyForce
    variable = ion
    function = 'ion_source'
  []

#Potential Equations
  [potential_diff]
    type = CoeffDiffusionLin
    variable = potential
    position_units = 1.0
  []
  [potential_source]
    type = BodyForce
    variable = potential
    function = 'potential_source'
  []
[]

[AuxVariables]
  [potential_sol]
  []
  [ion_sol]
  []

  [em_sol]
  []
[]

[AuxKernels]
  [potential_sol]
    type = FunctionAux
    variable = potential_sol
    function = potential_fun
  []
  [ion_sol]
    type = FunctionAux
    variable = ion_sol
    function = ion_fun
  []

  [em_sol]
    type = FunctionAux
    variable = em_sol
    function = em_fun
  []
[]

[Functions]
#Constants for the manufactured solutions
  #The lenght between electrode
  [l]
    type = ConstantFunction
    value = 1.0
  []
  #The frequency
  [f]
    type = ConstantFunction
    value = 1.0
  []

#Material Variables
  #Electron diffusion coeff.
  [diffem]
    type = ConstantFunction
    value = '1.0'
  []
  #Electron mobility coeff.
  [muem]
    type = ConstantFunction
    value = 1.0
  []
  #Ion diffusion coeff.
  [diffion]
    type = ParsedFunction
    vars = 'diffem'
    vals = 'diffem'
    expression = 'diffem'
  []
  #Ion mobility coeff.
  [muion]
    type = ParsedFunction
    vars = 'muem'
    vals = 'muem'
    expression = 'muem'
  []
  [N_A]
    type = ConstantFunction
    value = 1.0
  []
  [ee]
    type = ConstantFunction
    value = 1.0
  []
  [diffpotential]
    type = ConstantFunction
    value = 1.0
  []


#Manufactured Solutions
  #The manufactured electron density solution
  [em_fun]
    type = ParsedFunction
    vars = 'l f N_A'
    vals = 'l f N_A'
    expression = 'log(((sin(2.*pi*f*t) + 2.) * ((x/l)*(1. - x/l) + 1.)) / N_A)'
  []
  #The manufactured ion density solution
  [ion_fun]
    type = ParsedFunction
    vars = 'em_fun'
    vals = 'em_fun'
    expression = 'em_fun'
  []
  #The manufactured electron density solution
  [potential_fun]
    type = ParsedFunction
    vars = 'l f'
    vals = 'l f'
    expression = '-sin(2.*pi*f*t)*(x/l)^2. + (x/l)^2.'
  []

#Source Terms in moles
  #The electron source term.
  [em_source]
    type = ParsedFunction
    vars = 'l f diffem muem N_A'
    vals = 'l f diffem muem N_A'
    expression = '((2.*diffem*(sin(2.*pi*f*t) + 2.))/l^2. + (2.*f*pi*cos(2.*pi*f*t)*(l^2. + l*x - x^2.))/l^2. -
                   (2.*muem*(sin(2.*pi*f*t) - 1.)*(sin(2.*pi*f*t) + 2.)*(l^2. + l*x - x^2.))/l^4. -
                   (2.*muem*x*(sin(2.*pi*f*t) - 1.)*(sin(2.*pi*f*t) + 2.)*(l - 2.*x))/l^4.) / N_A'
  []
  [ion_source]
    type = ParsedFunction
    vars = 'l f diffion muion N_A'
    vals = 'l f diffion muion N_A'
    expression = '((2.*diffion*(sin(2.*pi*f*t) + 2.))/l^2. + (2.*f*pi*cos(2.*pi*f*t)*(l^2. + l*x - x^2.))/l^2. +
                   (2.*muion*(sin(2.*pi*f*t) - 1.)*(sin(2.*pi*f*t) + 2.)*(l^2. + l*x - x^2.))/l^4. +
                   (2.*muion*x*(sin(2.*pi*f*t) - 1.)*(sin(2.*pi*f*t) + 2.)*(l - 2.*x))/l^4.) / N_A'
  []
  [potential_source]
    type = ParsedFunction
    vars = 'l f'
    vals = 'l f'
    expression = 'sin(2.*pi*f*t)*(2./l^2.) - (2./l^2.)'
  []

  #The left BC dirichlet function
  [em_left_BC]
    type = ParsedFunction
    vars = 'l f N_A'
    vals = 'l f N_A'
    expression = 'log((sin(2.*pi*f*t) + 2.) / N_A)'
  []
  [ion_left_BC]
    type = ParsedFunction
    vars = 'l f N_A'
    vals = 'l f N_A'
    expression = 'log((sin(2.*pi*f*t) + 2.) / N_A)'
  []
  [potential_left_BC]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = '0.0'
  []
  #The right BC dirichlet function
  [em_right_BC]
    type = ParsedFunction
    vars = 'l f N_A'
    vals = 'l f N_A'
    expression = 'log((sin(2.*pi*f*t) + 2.) / N_A)'
  []
  [ion_right_BC]
    type = ParsedFunction
    vars = 'l f N_A'
    vals = 'l f N_A'
    expression = 'log((sin(2.*pi*f*t) + 2.) / N_A)'
  []
  [potential_right_BC]
    type = ParsedFunction
    vars = 'f N_A'
    vals = 'f N_A'
    expression = '1. - sin(2.*pi*f*t)'
  []

  [em_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((1.) / N_A)'
  []
  [ion_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((1.) / N_A)'
  []
[]

[BCs]
  #active = 'potential_left_BC potential_right_BC
  #          ion_left_BC       ion_right_BC
  #          em_left_BC        em_right_BC'

  #active = 'potential_left_BC potential_right_BC
  #          ion_left_BC       ion_right_BC
  #          em_left_Flux_BC   em_right_BC'

  #active = 'potential_left_BC potential_right_BC
  #          ion_left_BC       ion_right_BC
  #          em_left_BC        em_right_Flux_BC'

  active = 'potential_left_BC               potential_right_BC
            ion_left_BC                     ion_right_BC
            em_left_LymberopoulosElectronBC em_right_BC'

  #active = 'potential_left_BC               potential_right_BC
  #          ion_left_BC                     ion_right_BC
  #          em_left_BC                      em_right_LymberopoulosElectronBC'


  [potential_left_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_fun'
    boundary = 'left'
  []
  [potential_right_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_fun'
    boundary = 'right'
  []

  [ion_left_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_fun'
    boundary = 'left'
  []
  [ion_right_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_fun'
    boundary = 'right'
  []

  [em_left_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_fun'
    boundary = 'left'
  []
  [em_left_Flux_BC]
    type = FunctionNeumannBC
    variable = em
    function = 'em_left_Flux_BC'
    boundary = 'left'
  []
  [em_left_LymberopoulosElectronBC]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'left'
    emission_coeffs = 1.0
    ks = 1.0
    ions = ion
    position_units = 1.0
  []

  [em_right_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_fun'
    boundary = 'right'
  []
  [em_right_Flux_BC]
    type = FunctionNeumannBC
    variable = em
    function = 'em_right_Flux_BC'
    boundary = 'right'
  []
  [em_right_LymberopoulosElectronBC]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'right'
    emission_coeffs = 1.0
    ks = 1.0
    ions = ion
    position_units = 1.0
  []
[]

[Materials]
  [field_solver]
    type = FieldSolverMaterial
    potential = potential
  []
  [Material_Coeff]
    type = GenericFunctionMaterial
    prop_names =  'e  N_A'
    prop_values = 'ee N_A'
  []
  [ADMaterial_Coeff]
    type = ADGenericFunctionMaterial
    prop_names =  'diffpotential diffem muem diffion muion'
    prop_values = 'diffpotential diffem muem diffion muion'
  []
  [Charge_Signs]
    type = GenericConstantMaterial
    prop_names =  'sgnem  sgnion'
    prop_values = '-1.0   1.0'
  []
[]

[Postprocessors]
  [em_l2Error]
    type = ElementL2Error
    variable = em
    function = em_fun
  []
  [ion_l2Error]
    type = ElementL2Error
    variable = ion
    function = ion_fun
  []
  [potential_l2Error]
    type = ElementL2Error
    variable = potential
    function = potential_fun
  []
[]

[Preconditioning]
  active = 'smp'
  [smp]
    type = SMP
    full = true
  []

  [fdp]
    type = FDP
    full = true
  []
[]

[Executioner]
  type = Transient
  start_time = 50
  end_time = 51
  # dt = 0.0075
  dt = 0.02
  automatic_scaling = true
  compute_scaling_once = false
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  line_search = none
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'

  scheme = bdf2
  nl_abs_tol = 1e-14
[]
