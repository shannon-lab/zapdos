[Mesh]
  [geo]
    type = FileMeshGenerator
    file = '2D_IonBC_NegivateOutWardFacingEfield_IC_out.e'
    use_for_exodus_restart = true
  []
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [ion]
    initial_from_file_var = ion
  []

  [Ex]
    initial_from_file_var = Ex
  []
  [Ey]
    initial_from_file_var = Ey
  []
[]

[Kernels]
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
    type = EffectiveEFieldAdvection
    variable = ion
    u = Ex
    v = Ey
    position_units = 1.0
  []
  [ion_source]
    type = BodyForce
    variable = ion
    function = 'ion_source'
  []


#Eff. Efield
  [EffEfield_X_time_deriv]
    type = TimeDerivative
    variable = Ex
  []
  [EffEfield_X_diffusion]
    type = MatDiffusion
    diffusivity = diffEx
    variable = Ex
  []
  [EffEfield_X_source]
    type = BodyForce
    variable = Ex
    function = 'Ex_source'
  []
  [EffEfield_Y_time_deriv]
    type = TimeDerivative
    variable = Ey
  []
  [EffEfield_Y_diffusion]
    type = MatDiffusion
    diffusivity = diffEy
    variable = Ey
  []
  [EffEfield_Y_source]
    type = BodyForce
    variable = Ey
    function = 'Ey_source'
  []
[]

[AuxVariables]
  [ion_sol]
  []

  [Ex_sol]
  []
  [Ey_sol]
  []
[]

[AuxKernels]
  [ion_sol]
    type = FunctionAux
    variable = ion_sol
    function = ion_fun
  []

  [Ex_sol]
    type = FunctionAux
    variable = Ex_sol
    function = Ex_fun
  []
  [Ey_sol]
    type = FunctionAux
    variable = Ey_sol
    function = Ey_fun
  []
[]

[Functions]
#Material Variables
  #Ion diffusion coeff.
  [diffion]
    type = ConstantFunction
    value = 0.05
  []
  [muion]
    type = ConstantFunction
    value = 0.01
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
    value = 0.25
  []


#Manufactured Solutions
  #The manufactured ion density solution
  [ion_fun]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((sin(pi*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 1.0 + sin(pi*x)) / N_A)'
  []
  #The manufactured eff. Efield solution
  [Ex_fun]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    expression = '(diffion*pi*cos(pi*x))/(muion*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1))'
  []
  [Ey_fun]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    expression = '(diffion*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5))/(muion*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1))'
  []

#Source Terms in moles
  #The ion source term.
  [ion_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    expression = '((2*pi*cos(2*pi*t)*cos(pi*y))/5) / N_A'
  []

  #The Ex source term.
  [Ex_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    expression = '-diffpotential*((2*diffion*pi^3*cos(pi*x)^3)/(muion*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1)^3) - (diffion*pi^3*cos(pi*x))/(muion*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)) + (3*diffion*pi^3*cos(pi*x)*sin(pi*x))/(muion*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1)^2)) - (2*diffion*diffpotential*pi*cos(pi*x)*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5)^2)/(muion*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1)^3) - (2*diffion*pi^2*cos(2*pi*t)*cos(pi*x)*cos(pi*y))/(5*muion*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1)^2) - (diffion*diffpotential*pi*cos(pi*x)*(pi^2*sin(pi*y) + (pi^2*cos(pi*y)*sin(2*pi*t))/5))/(muion*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1)^2)'
  []
  [Ey_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    expression = '-diffpotential*((2*diffion*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5)^3)/(muion*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1)^3) - (diffion*(pi^3*cos(pi*y) - (pi^3*sin(2*pi*t)*sin(pi*y))/5))/(muion*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)) + (3*diffion*(pi^2*sin(pi*y) + (pi^2*cos(pi*y)*sin(2*pi*t))/5)*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5))/(muion*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1)^2)) - (2*diffion*pi^2*cos(2*pi*t)*sin(pi*y))/(5*muion*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)) - (diffion*diffpotential*pi^2*sin(pi*x)*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5))/(muion*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1)^2) - (2*diffion*diffpotential*pi^2*cos(pi*x)^2*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5))/(muion*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1)^3) - (2*diffion*pi*cos(2*pi*t)*cos(pi*y)*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5))/(5*muion*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1)^2)'
  []


  [ion_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((3.0 + sin(pi/2*x)) / N_A)'
  []

  [ion_left_Flux_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    expression = '(0) / N_A'
  []
  [ion_down_Flux_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    expression = '(0) / N_A'
  []
[]

[BCs]
  #[ion_left_BC]
  #  type = FunctionDirichletBC
  #  variable = ion
  #  function = 'ion_fun'
  #  boundary = 3
  #  preset = true
  #[]
  [ion_left_physical_advection]
    type = SakiyamaIonAdvectionWithEffEfieldBC
    variable = ion
    Ex = Ex
    Ey = Ey
    boundary = 3
    position_units = 1.0
  []

  [ion_right_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_fun'
    boundary = 1
    preset = true
  []

  #[ion_down_BC]
  #  type = FunctionDirichletBC
  #  variable = ion
  #  function = 'ion_down_BC'
  #  boundary = 0
  #  preset = true
  #[]
  [ion_down_physical_advection]
    type = SakiyamaIonAdvectionWithEffEfieldBC
    variable = ion
    Ex = Ex
    Ey = Ey
    boundary = 0
    position_units = 1.0
  []

  [ion_up_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_fun'
    boundary = 2
    preset = true
  []

  [Ex_BC]
    type = FunctionDirichletBC
    variable = Ex
    function = 'Ex_fun'
    boundary = '0 1 2 3'
    preset = true
  []

  [Ey_BC]
    type = FunctionDirichletBC
    variable = Ey
    function = 'Ey_fun'
    boundary = '0 1 2 3'
    preset = true
  []
[]

[Materials]
  [Material_Coeff]
    type = GenericFunctionMaterial
    prop_names =  'e  N_A  diffEx         diffEy'
    prop_values = 'ee N_A  diffpotential  diffpotential '
  []
  [ADMaterial_Coeff_Set1]
    type = ADGenericFunctionMaterial
    prop_names =  'diffion  muion'
    prop_values = 'diffion  muion'
  []
  [Charge_Signs]
    type = GenericConstantMaterial
    prop_names =  'sgnion'
    prop_values = '1.0'
  []
[]

[Postprocessors]
  [ion_l2Error]
    type = ElementL2Error
    variable = ion
    function = ion_fun
  []

  [Ex_l2Error]
    type = ElementL2Error
    variable = Ex
    function = Ex_fun
  []
  [Ey_l2Error]
    type = ElementL2Error
    variable = Ey
    function = Ey_fun
  []

  [h]
    type = AverageElementSize
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

  # dt = 0.008
  dt = 0.02


  automatic_scaling = true
  compute_scaling_once = false
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  line_search = none
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'

  scheme = bdf2

  nl_abs_tol = 1e-13
[]

[Outputs]
  perf_graph = true
  [out]
    type = Exodus
    interval = 10
  []
[]
