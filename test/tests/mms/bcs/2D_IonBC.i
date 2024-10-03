#This MMS test was designed to test the log version of Zapdos'
#kernels with coupling between electrons, ions, potential, and
#the mean electron energy density.

#The mean electron energy density has a "correction" term that assumes
#an thermal conductivity coefficient of K=3/2*D_e*n_e (this is based on
#using the assumption of Einstein Relation)

#Note: The electron/mean energy's diffusion and mobility coefficients are
#directly proportional to the energy function.


[Mesh]
  [./geo]
    type = FileMeshGenerator
    file = '2D_IonBC_IC_out.e'
    use_for_exodus_restart = true
  [../]
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [./ion]
    initial_from_file_var = ion
  [../]

  [./Ex]
    initial_from_file_var = Ex
  [../]
  [./Ey]
    initial_from_file_var = Ey
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
    type = EffectiveEFieldAdvection
    variable = ion
    u = Ex
    v = Ey
    position_units = 1.0
  [../]
  [./ion_source]
    type = BodyForce
    variable = ion
    function = 'ion_source'
  [../]


#Eff. Efield
  [./EffEfield_X_time_deriv]
    type = TimeDerivative
    variable = Ex
  [../]
  [./EffEfield_X_diffusion]
    type = MatDiffusion
    diffusivity = diffEx
    variable = Ex
  [../]
  [./EffEfield_X_source]
    type = BodyForce
    variable = Ex
    function = 'Ex_source'
  [../]
  [./EffEfield_Y_time_deriv]
    type = TimeDerivative
    variable = Ey
  [../]
  [./EffEfield_Y_diffusion]
    type = MatDiffusion
    diffusivity = diffEy
    variable = Ey
  [../]
  [./EffEfield_Y_source]
    type = BodyForce
    variable = Ey
    function = 'Ey_source'
  [../]
[]

[AuxVariables]
  [./ion_sol]
  [../]

  [./Ex_sol]
  [../]
  [./Ey_sol]
  [../]
[]

[AuxKernels]
  [./ion_sol]
    type = FunctionAux
    variable = ion_sol
    function = ion_fun
  [../]

  [./Ex_sol]
    type = FunctionAux
    variable = Ex_sol
    function = Ex_fun
  [../]
  [./Ey_sol]
    type = FunctionAux
    variable = Ey_sol
    function = Ey_fun
  [../]
[]

[Functions]
#Material Variables
  #Ion diffusion coeff.
  [./diffion]
    type = ConstantFunction
    value = 0.05
  [../]
  [./muion]
    type = ConstantFunction
    value = 0.01
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
    value = 0.25
  [../]


#Manufactured Solutions
  #The manufactured ion density solution
  [./ion_fun]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((cos(pi/2*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 1.0 + cos(pi/2*x)) / N_A)'
  [../]
  #The manufactured eff. Efield solution
  [./Ex_fun]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '-pi*cos(pi*x)*(sin(pi*t) + 1)'
  [../]
  [./Ey_fun]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '-pi*cos(pi*y)*(sin(pi*t) + 1)'
  [../]

#Source Terms in moles
  #The ion source term.
  [./ion_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '(diffion*((pi^2*cos((pi*y)/2))/4 + (pi^2*sin(2*pi*t)*(2*cos((pi*y)/2)^2 - 1))/5) +
             (2*pi*cos(2*pi*t)*cos(pi*y))/5 + (diffion*pi^2*cos((pi*x)/2))/4 + muion*pi^2*sin(pi*x)*(sin(pi*t) + 1)*(cos((pi*x)/2) +
             cos((pi*y)/2) + (cos(pi*y)*sin(2*pi*t))/5 + 1) + muion*pi^2*sin(pi*y)*(sin(pi*t) + 1)*(cos((pi*x)/2) + cos((pi*y)/2) +
             (cos(pi*y)*sin(2*pi*t))/5 + 1) + muion*pi*cos(pi*y)*((pi*sin((pi*y)/2))/2 + (pi*sin(2*pi*t)*sin(pi*y))/5)*(sin(pi*t) + 1) +
             (muion*pi^2*cos(pi*x)*sin((pi*x)/2)*(sin(pi*t) + 1))/2) / N_A'
  [../]

  #The Ex source term.
  [./Ex_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '-pi^2*cos(pi*t)*cos(pi*x) - diffpotential*pi^3*cos(pi*x)*(sin(pi*t) + 1)'
  [../]
  [./Ey_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '-pi^2*cos(pi*t)*cos(pi*y) - diffpotential*pi^3*cos(pi*y)*(sin(pi*t) + 1)'
  [../]

  #The left BC dirichlet function
  [./ion_left_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = 'log((cos((pi*y)/2) + (cos(pi*y)*sin(2*pi*t))/5 + 2) / N_A)'
  [../]
  [./Ex_left_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '-pi*(sin(pi*t) + 1)'
  [../]
  [./Ey_left_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '-pi*cos(pi*y)*(sin(pi*t) + 1)'
  [../]

  #The right BC dirichlet function
  [./ion_right_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = 'log((cos((pi*y)/2) + (cos(pi*y)*sin(2*pi*t))/5 + 1) / N_A)'
  [../]
  [./Ex_right_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = 'pi*(sin(pi*t) + 1)'
  [../]
  [./Ey_right_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '-pi*cos(pi*y)*(sin(pi*t) + 1)'
  [../]

  #The Down BC dirichlet function
  [./ion_down_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = 'log((cos((pi*x)/2) + sin(2*pi*t)/5 + 2) / N_A)'
  [../]
  [./Ex_down_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '-pi*cos(pi*x)*(sin(pi*t) + 1)'
  [../]
  [./Ey_down_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '-pi*(sin(pi*t) + 1)'
  [../]

  #The up BC dirichlet function
  [./ion_up_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = 'log((cos((pi*x)/2) - sin(2*pi*t)/5 + 1) / N_A)'
  [../]
  [./Ex_up_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '-pi*cos(pi*x)*(sin(pi*t) + 1)'
  [../]
  [./Ey_up_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = 'pi*(sin(pi*t) + 1)'
  [../]


  [./ion_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((3.0 + sin(pi/2*x)) / N_A)'
  [../]

  [./ion_left_Flux_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '((diffion*pi*sin((pi*x)/2))/2 - muion*pi*(2*cos((pi*x)/2)^2 - 1)*(sin(pi*t) + 1)*(cos((pi*x)/2) +
              cos((pi*y)/2) + (2*cos(pi*t)*sin(pi*t)*(2*cos((pi*y)/2)^2 - 1))/5 + 1)) / N_A'
  [../]
  [./ion_down_Flux_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffion muion'
    vals = 'ee N_A diffpotential diffion muion'
    value = '(diffion*((pi*sin((pi*y)/2))/2 + (pi*sin(2*pi*t)*sin(pi*y))/5) -
              muion*pi*cos(pi*y)*(sin(pi*t) + 1)*(cos((pi*x)/2) + cos((pi*y)/2) + (cos(pi*y)*sin(2*pi*t))/5 + 1)) / N_A'
  [../]
[]

[BCs]
  #[./ion_left_BC]
  #  type = FunctionDirichletBC
  #  variable = ion
  #  function = 'ion_left_BC'
  #  boundary = 3
  #  preset = true
  #[../]
  [./ion_left_physical_advection]
    type = SakiyamaIonAdvectionWithEffEfieldBC
    variable = ion
    Ex = Ex
    Ey = Ey
    boundary = 3
    position_units = 1.0
  [../]

  [./ion_right_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_right_BC'
    boundary = 1
    preset = true
  [../]

  #[./ion_down_BC]
  #  type = FunctionDirichletBC
  #  variable = ion
  #  function = 'ion_down_BC'
  #  boundary = 0
  #  preset = true
  #[../]
  [./ion_down_physical_advection]
    type = SakiyamaIonAdvectionWithEffEfieldBC
    variable = ion
    Ex = Ex
    Ey = Ey
    boundary = 0
    position_units = 1.0
  [../]

  [./ion_up_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_up_BC'
    boundary = 2
    preset = true
  [../]

  [./Ex_left_BC]
    type = FunctionDirichletBC
    variable = Ex
    function = 'Ex_left_BC'
    boundary = 3
    preset = true
  [../]
  [./Ex_right_BC]
    type = FunctionDirichletBC
    variable = Ex
    function = 'Ex_right_BC'
    boundary = 1
    preset = true
  [../]
  [./Ex_down_BC]
    type = FunctionDirichletBC
    variable = Ex
    function = 'Ex_down_BC'
    boundary = 0
    preset = true
  [../]
  [./Ex_up_BC]
    type = FunctionDirichletBC
    variable = Ex
    function = 'Ex_up_BC'
    boundary = 2
    preset = true
  [../]

  [./Ey_left_BC]
    type = FunctionDirichletBC
    variable = Ey
    function = 'Ey_left_BC'
    boundary = 3
    preset = true
  [../]
  [./Ey_right_BC]
    type = FunctionDirichletBC
    variable = Ey
    function = 'Ey_right_BC'
    boundary = 1
    preset = true
  [../]
  [./Ey_down_BC]
    type = FunctionDirichletBC
    variable = Ey
    function = 'Ey_down_BC'
    boundary = 0
    preset = true
  [../]
  [./Ey_up_BC]
    type = FunctionDirichletBC
    variable = Ey
    function = 'Ey_up_BC'
    boundary = 2
    preset = true
  [../]
[]

[Materials]
  [./Material_Coeff]
    type = GenericFunctionMaterial
    prop_names =  'e  N_A  diffEx         diffEy'
    prop_values = 'ee N_A  diffpotential  diffpotential '
  [../]
  [./ADMaterial_Coeff_Set1]
    type = ADGenericFunctionMaterial
    prop_names =  'diffion  muion'
    prop_values = 'diffion  muion'
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

  [./Ex_l2Error]
    type = ElementL2Error
    variable = Ex
    function = Ex_fun
  [../]
  [./Ey_l2Error]
    type = ElementL2Error
    variable = Ey
    function = Ey_fun
  [../]

  [./h]
    type = AverageElementSize
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
  [./out]
    type = Exodus
    interval = 10
  []
[]
