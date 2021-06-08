#Need to Edit

#This MMS test was designed to test the log version of LymberopoulosIonBC,
#when coupled with a "potential" variable. This test is done twice with
#mixed BCs, once where the left is the LymberopoulosIonBC while the right
#is a DirichletBC and vice-versa.

[Mesh]
  [./geo]
    type = FileMeshGenerator
    file = 'LymberopoulosIonBC_LeftBC_IC_out.e'
    #file = 'LymberopoulosIonBC_RightBC_IC_out.e'
    use_for_exodus_restart = true
  [../]
  [./left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = geo
  [../]
  [./right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  [../]
[]

[Outputs]
  file_base = 'LymberopoulosIonBC_LeftBC_out'
  #file_base = 'LymberopoulosIonBC_RightBC_out'
  perf_graph = true
  [./out]
    type = Exodus
    interval = 10
  []
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [./ion]
    initial_from_file_var = ion
  [../]
  [./potential]
    initial_from_file_var = potential
  [../]
[]

[Kernels]
#Ion Equations
  [./ion_time_derivative]
    type = TimeDerivativeLog
    variable = ion
  [../]
  [./ion_diffusion]
    type = CoeffDiffusion
    variable = ion
    position_units = 1.0
  [../]
  [./ion_advection]
    type = EFieldAdvection
    variable = ion
    potential = 'potential'
    position_units = 1.0
  [../]
  [./ion_source]
    type = BodyForce
    variable = ion
    function = 'ion_source'
  [../]

#Potential Equations
  [./potential_time_derivative]
    type = TimeDerivative
    variable = potential
  [../]
  [./potential_diff]
    type = CoeffDiffusionLin
    variable = potential
    position_units = 1.0
  [../]
  [./potential_source]
    type = BodyForce
    variable = potential
    function = 'potential_source'
  [../]

[]

[AuxVariables]
  [./potential_sol]
  [../]

  [./ion_sol]
  [../]
[]

[AuxKernels]
  [./potential_sol]
    type = FunctionAux
    variable = potential_sol
    function = potential_fun
  [../]

  [./ion_sol]
    type = FunctionAux
    variable = ion_sol
    function = ion_fun
  [../]
[]

[Functions]
#Constants for the manufactured solutions
  #The lenght between electrode
  [./l]
    type = ConstantFunction
    value = 1.0
  [../]
  #The frequency
  [./f]
    type = ConstantFunction
    value = 1.0
  [../]

#Material Variables
  #Ion diffusion coeff.
  [./diffion]
    type = ConstantFunction
    value = 1.0
  [../]
  #Ion mobility coeff.
  [./muion]
    type = ConstantFunction
    value = 0.1
  [../]
  [./N_A]
    type = ConstantFunction
    value = 1.0
  [../]
  [./ee]
    type = ConstantFunction
    value = 1.0
  [../]
  [./diffpotential]
    type = ConstantFunction
    value = 0.01
  [../]



#Manufactured Solutions
  #The manufactured ion density solution
  [./ion_fun]
    type = ParsedFunction
    vars = 'l N_A'
    vals = 'l N_A'
    value = 'log((1.0 + x^2*(1 - x/l)^2/l^2) / N_A)'
  [../]
  #The manufactured electron density solution
  [./potential_fun]
    type = ParsedFunction
    vars = 'l f ee diffpotential'
    vals = 'l f ee diffpotential'
    value = '-(ee*l^2*sin((pi*x)/l)*sin(2*pi*f*t))/(5*diffpotential*pi^2)'
  [../]

#Source Terms in moles
  #The ion source term.
  [./ion_source]
    type = ParsedFunction
    vars = 'l f ee diffpotential diffion muion N_A'
    vals = 'l f ee diffpotential diffion muion N_A'
    value = '(-2*diffion/l^2 +
              12*diffion*x/l^3 -
              12*diffion*x^2/l^4 -
              0.2*ee*muion*sin(2*pi*f*t)*sin(pi*x/l)/diffpotential +
              2*ee*muion*x*sin(2*pi*f*t)*cos(pi*x/l)/(5*pi*diffpotential*l) -
              ee*muion*x^2*sin(2*pi*f*t)*sin(pi*x/l)/(5*diffpotential*l^2) -
              6*ee*muion*x^2*sin(2*pi*f*t)*cos(pi*x/l)/(5*pi*diffpotential*l^2) +
              2*ee*muion*x^3*sin(2*pi*f*t)*sin(pi*x/l)/(5*diffpotential*l^3) +
              4*ee*muion*x^3*sin(2*pi*f*t)*cos(pi*x/l)/(5*pi*diffpotential*l^3) -
              ee*muion*x^4*sin(2*pi*f*t)*sin(pi*x/l)/(5*diffpotential*l^4)) / N_A'
  [../]
  [./potential_source]
    type = ParsedFunction
    vars = 'l f ee diffpotential'
    vals = 'l f ee diffpotential'
    value = '-ee*sin(2*pi*f*t)*sin(pi*x/l)/5 - 2*ee*f*l^2*sin(pi*x/l)*cos(2*pi*f*t)/(5*pi*diffpotential)'
  [../]

  #The left BC dirichlet function
  [./ion_left_BC]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((1.0) / N_A)'
  [../]
  [./potential_left_BC]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = '0.0'
  [../]
  #The right BC dirichlet function
  [./ion_right_BC]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((1.0) / N_A)'
  [../]
  [./potential_right_BC]
    type = ParsedFunction
    vars = 'f N_A'
    vals = 'f N_A'
    value = '0.0'
  [../]

  #The left Flux BC function
  [./ion_left_Flux_BC]
    type = ParsedFunction
    vars = 'l f ee diffpotential muion N_A'
    vals = 'l f ee diffpotential muion N_A'
    value = '(0.2*ee*l*muion*sin(2*pi*f*t)/(pi*diffpotential)) / N_A'
  [../]
  #The right Flux BC function
  [./ion_right_Flux_BC]
    type = ParsedFunction
    vars = 'l f ee diffpotential muion N_A'
    vals = 'l f ee diffpotential muion N_A'
    value = '-1.0 * (-0.2*ee*l*muion*sin(2*pi*f*t)/(pi*diffpotential)) / N_A'
  [../]

  [./ion_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = '(1.) / N_A'
  [../]
[]

[BCs]

  #active = 'potential_left_BC potential_right_BC
  #          ion_left_BC       ion_right_BC'

  #active = 'potential_left_BC potential_right_BC
  #          ion_left_Flux_BC  ion_right_BC'

  #active = 'potential_left_BC potential_right_BC
  #          ion_left_BC       ion_right_Flux_BC'

  active = 'potential_left_BC           potential_right_BC
            ion_left_LymberopoulosIonBC ion_right_BC'

  #active = 'potential_left_BC           potential_right_BC
  #          ion_left_BC                 ion_right_LymberopoulosIonBC'

  [./potential_left_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_left_BC'
    boundary = 'left'
  [../]
  [./potential_right_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_right_BC'
    boundary = 'right'
  [../]

  [./ion_left_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_left_BC'
    boundary = 'left'
  [../]
  [./ion_left_Flux_BC]
    type = FunctionNeumannBC
    variable = ion
    function = 'ion_left_Flux_BC'
    boundary = 'left'
  [../]
  [./ion_left_LymberopoulosIonBC]
    type = LymberopoulosIonBC
    variable = ion
    potential = potential
    boundary = 'left'
    position_units = 1.0
  [../]


  [./ion_right_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_right_BC'
    boundary = 'right'
  [../]
  [./ion_right_Flux_BC]
    type = FunctionNeumannBC
    variable = ion
    function = 'ion_right_Flux_BC'
    boundary = 'right'
  [../]
  [./ion_right_LymberopoulosIonBC]
    type = LymberopoulosIonBC
    variable = ion
    potential = potential
    boundary = 'right'
    position_units = 1.0
  [../]
[]

[Materials]
  [./Material_Coeff]
    type = GenericFunctionMaterial
    prop_names =  'e  N_A'
    prop_values = 'ee N_A'
  [../]
  [./ADMaterial_Coeff]
    type = ADGenericFunctionMaterial
    prop_names =  'diffpotential diffion muion'
    prop_values = 'diffpotential diffion muion'
  [../]
  [./Charge_Signs]
    type = GenericConstantMaterial
    prop_names =  'sgnion'
    prop_values = '1.0'
  [../]
[]

[Postprocessors]
  [./ion_l2Error]
    type = ElementL2Error
    variable = ion
    function = ion_fun
  [../]
  [./potential_l2Error]
    type = ElementL2Error
    variable = potential
    function = potential_fun
  [../]
[]

[Preconditioning]
  active = 'smp'
  [./smp]
    type = SMP
    full = true
  [../]

  [./fdp]
    type = FDP
    full = true
  [../]
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
