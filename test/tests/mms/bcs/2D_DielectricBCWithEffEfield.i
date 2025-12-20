[Mesh]
  [geo]
    type = FileMeshGenerator
    file = '2D_DielectricBCWithEffEfield_IC_out.e'
    use_for_exodus_restart = true
  []
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [em]
    initial_from_file_var = em
  []
  [ion]
    initial_from_file_var = ion
  []
  [mean_en]
    initial_from_file_var = mean_en
  []

  [Ex]
    initial_from_file_var = Ex
  []
  [Ey]
    initial_from_file_var = Ey
  []

  [potential]
    initial_from_file_var = potential
  []
[]

# [ICs]
#   [em_IC]
#     type = FunctionIC
#     variable = em
#     function = 'em_ICs'
#   []
#   [ion_IC]
#     type = FunctionIC
#     variable = ion
#     function = 'ion_ICs'
#   []
#   [mean_en_IC]
#     type = FunctionIC
#     variable = mean_en
#     function = 'mean_en_ICs'
#   []
# []

[Kernels]
  #Electron Equations
  [em_time_derivative]
    type = ElectronTimeDerivative
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
    type = ElectronTimeDerivative
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
    # position_units = 1.0
    position_units = '${fparse sqrt(1/(1.6e-19 * 6.02e23))}' # e * N_A / 2
  []
  [ion_source]
    type = BodyForce
    variable = ion
    function = 'ion_source'
  []

  #Eff. Efield
  [EffEfield_X_time_deriv]
    type = ADTimeDerivative
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
    type = ADTimeDerivative
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

  #Potential
  [Potential_time_deriv]
    type = ADTimeDerivative
    variable = potential
  []
  [Potential_diffusion]
    type = CoeffDiffusionLin
    variable = potential
    position_units = 1.0
  []
  [Potential_source]
    type = BodyForce
    variable = potential
    function = 'potential_source'
  []

  #Electron Energy Equations
  [mean_en_time_deriv]
    type = ElectronTimeDerivative
    variable = mean_en
  []
  [mean_en_diffusion]
    type = CoeffDiffusion
    variable = mean_en
    position_units = 1.0
  []
  [mean_en_source]
    type = BodyForce
    variable = mean_en
    function = 'energy_source'
  []
[]

[AuxVariables]
  [mean_en_sol]
  []

  [em_sol]
  []

  [ion_sol]
  []

  [Ex_sol]
  []
  [Ey_sol]
  []

  [potential_sol]
  []
[]

[AuxKernels]
  [mean_en_sol]
    type = FunctionAux
    variable = mean_en_sol
    function = mean_en_fun
  []

  [em_sol]
    type = FunctionAux
    variable = em_sol
    function = em_fun
  []

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

  [potential_sol]
    type = FunctionAux
    variable = potential_sol
    function = potential_fun
  []
[]

[Functions]
  #Material Variables
  [massem]
    type = ConstantFunction
    value = 2.0
  []

  [massem_mat]
    type = ParsedFunction
    symbol_names = massem
    symbol_values = massem
    value = 'massem * 1.6e-19 * (1.6e-19 * 6.02e23)^2'
  []

  #Electron diffusion coeff.
  [diffem]
    type = ConstantFunction
    value = 0.05
  []
  [muem]
    type = ConstantFunction
    value = 0.01
  []
  #Electron energy mobility coeff.
  [diffmean_en]
    type = ConstantFunction
    value = 0.05
  []
  #Ion diffusion coeff.
  [diffion]
    type = ParsedFunction
    symbol_names = diffem
    symbol_values = diffem
    expression = diffem
  []
  [muion]
    type = ParsedFunction
    symbol_names = muem
    symbol_values = muem
    expression = muem
  []

  [muion_mat]
    type = ParsedFunction
    symbol_names = muion
    symbol_values = muion
    value = 'muion / (1.6e-19 * 6.02e23)'
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
    value = 0.05
  []

  #Manufactured Solutions
  #The manufactured electron density solution
  [em_fun]
    type = ParsedFunction
    symbol_names = 'N_A'
    symbol_values = 'N_A'
    expression = 'log((sin(pi*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 2.0 + sin(pi*x)) / N_A)'
  []
  #The manufactured ion density solution
  [ion_fun]
    type = ParsedFunction
    symbol_names = 'N_A'
    symbol_values = 'N_A'
    expression = 'log((sin(pi*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 2.0 + sin(pi*x)) / N_A)'
  []
  #The manufactured electron energy solution
  [mean_en_fun]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = 'log(((3*massem*pi*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))^2)/(16*ee*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))) / N_A)'
  []
  #The manufactured eff. Efield solution
  [Ex_fun]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '-pi*cos(pi*x)*(sin(pi*t) + 1)'
  []
  [Ey_fun]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '-pi*cos(pi*y)*(sin(pi*t) + 1)'
  []
  #The manufactured potential solution
  [potential_fun]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '0.25*(sin(pi*t)/pi + 1.0)*(sin(pi*y) + sin(pi*x)) - t'
  []

  #Source Terms in moles
  #The electron source term.
  [em_source]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '(diffem*pi^2*sin(pi*x) + (diffem*pi^2*(5*sin(pi*y) + cos(pi*y)*sin(2*pi*t)))/5 + (2*pi*cos(2*pi*t)*cos(pi*y))/5 - (muem*pi*(pi + sin(pi*t))*(10*sin(pi*x) + 10*sin(pi*y) + 10*sin(pi*x)*sin(pi*y) - 10*cos(pi*x)^2 - 10*cos(pi*y)^2 + cos(pi*y)*sin(2*pi*t)*sin(pi*x) + 2*cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 10))/20) / N_A'
  []
  #The ion source term.
  [ion_source]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '(diffion*pi^2*sin(pi*x) + (diffion*pi^2*(5*sin(pi*y) + cos(pi*y)*sin(2*pi*t)))/5 + (2*pi*cos(2*pi*t)*cos(pi*y))/5 + (muion*pi^2*(sin(pi*t) + 1)*(10*sin(pi*x) + 10*sin(pi*y) + 10*sin(pi*x)*sin(pi*y) - 10*cos(pi*x)^2 - 10*cos(pi*y)^2 + cos(pi*y)*sin(2*pi*t)*sin(pi*x) + 2*cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 10))/5) / N_A'
  []
  [energy_source]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '((3*massem*pi*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))*(8*muion*pi^2*cos(pi*t)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2) - (diffpotential*pi^2*sin(pi*t) - pi*sin(pi*t)*(sin(pi*x) + sin(pi*y)))/ee + (16*muion*pi^2*cos(2*pi*t)*cos(pi*y)*(sin(pi*t) + 1))/5))/(8*ee*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2)) - diffmean_en*((3*massem*pi*((pi*cos(pi*t)*cos(pi*y))/ee - 8*muion*pi*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5)*(sin(pi*t) + 1))^2)/(8*ee*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2)) + (3*massem*pi*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))^2*(pi^2*sin(pi*y) + (pi^2*cos(pi*y)*sin(2*pi*t))/5))/(16*ee*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 2)^2) - (3*massem*pi*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))*(8*muion*pi*(pi^2*sin(pi*y) + (pi^2*cos(pi*y)*sin(2*pi*t))/5)*(sin(pi*t) + 1) - (pi^2*cos(pi*t)*sin(pi*y))/ee))/(8*ee*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2)) + (3*massem*pi*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))^2*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5)^2)/(8*ee*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 2)^3) + (3*massem*pi*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))*((pi*cos(pi*t)*cos(pi*y))/ee - 8*muion*pi*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5)*(sin(pi*t) + 1))*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5))/(4*ee*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 2)^2)) - diffmean_en*((3*massem*pi*((pi*cos(pi*t)*cos(pi*x))/ee - 8*muion*pi^2*cos(pi*x)*(sin(pi*t) + 1))^2)/(8*ee*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2)) + (3*massem*pi^3*cos(pi*x)^2*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))^2)/(8*ee*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 2)^3) + (3*massem*pi^3*sin(pi*x)*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))^2)/(16*ee*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 2)^2) - (3*massem*pi*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))*(8*muion*pi^3*sin(pi*x)*(sin(pi*t) + 1) - (pi^2*cos(pi*t)*sin(pi*x))/ee))/(8*ee*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2)) + (3*massem*pi^2*cos(pi*x)*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))*((pi*cos(pi*t)*cos(pi*x))/ee - 8*muion*pi^2*cos(pi*x)*(sin(pi*t) + 1)))/(4*ee*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 2)^2)) - (3*massem*pi^2*cos(2*pi*t)*cos(pi*y)*((diffpotential*pi*cos(pi*t) - cos(pi*t)*(sin(pi*x) + sin(pi*y)) + 4)/ee + 8*muion*pi*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 2))^2)/(40*ee*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 2)^2)) / N_A'
  []

  #The Ex source term.
  [Ex_source]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '-pi^2*cos(pi*t)*cos(pi*x) - diffpotential*pi^3*cos(pi*x)*(sin(pi*t) + 1)'
  []
  [Ey_source]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '-pi^2*cos(pi*t)*cos(pi*y) - diffpotential*pi^3*cos(pi*y)*(sin(pi*t) + 1)'
  []

  [potential_source]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '(cos(pi*t)*(sin(pi*x) + sin(pi*y)))/4 + diffpotential*pi^2*sin(pi*x)*(sin(pi*t)/(4*pi) + 1/4) + diffpotential*pi^2*sin(pi*y)*(sin(pi*t)/(4*pi) + 1/4) - 1'
  []

  [em_ICs]
    type = ParsedFunction
    symbol_names = 'N_A'
    symbol_values = 'N_A'
    expression = 'log((3.0 + sin(pi/2*x)) / N_A)'
  []
  [ion_ICs]
    type = ParsedFunction
    symbol_names = 'N_A'
    symbol_values = 'N_A'
    expression = 'log((3.0 + sin(pi/2*x)) / N_A)'
  []
  [mean_en_ICs]
    type = ParsedFunction
    symbol_names = 'em_ICs'
    symbol_values = 'em_ICs'
    expression = 'log(1.0)'
  []

  [V_func_left_BC]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '-diffpotential*pi*cos(pi*x)*(sin(pi*t)/(4*pi) + 1/4)'
  []
  [V_func_down_BC]
    type = ParsedFunction
    symbol_names = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    symbol_values = 'ee N_A diffpotential diffem muem massem diffmean_en diffion muion'
    expression = '-diffpotential*pi*cos(pi*y)*(sin(pi*t)/(4*pi) + 1/4)'
  []
[]

[BCs]
  [em_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_fun'
    boundary = '0 1 2 3'
    preset = true
  []

  [ion_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_fun'
    boundary = '0 1 2 3'
    preset = true
  []

  [energy_BC]
    type = FunctionDirichletBC
    variable = mean_en
    function = 'mean_en_fun'
    boundary = '0 1 2 3'
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

  [potential_left_BC]
    type = DielectricBCWithEffEfield
    variable = potential
    electrons = em
    electron_energy = mean_en
    ions = 'ion'
    electric_field_x = Ex
    electric_field_y = Ey
    dielectric_constant = 1.0
    thickness = 1.0
    emission_coeffs = 'users_gamma'
    potential_units = V
    position_units = 1.0
    boundary = 3
  []

  [potential_Dirichlet_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_fun'
    boundary = '0 1 2'
    preset = true
  []
[]

[Materials]
  [field_solver]
    type = FieldSolverMaterial
    potential = potential
  []
  [Material_Coeff]
    type = GenericFunctionMaterial
    prop_names = 'e  N_A  massem  NonAD_diffpotential  diffEx         diffEy'
    prop_values = 'ee N_A  massem_mat        diffpotential        diffpotential  diffpotential '
  []
  [ADMaterial_Coeff_Set1]
    type = ADGenericFunctionMaterial
    prop_names = 'diffion diffem muion  muem  diffmean_en  diffpotential'
    prop_values = 'diffion  diffem muion_mat  muem  diffmean_en  diffpotential'
  []
  [Charge_Signs]
    type = GenericConstantMaterial
    prop_names = 'sgnem  sgnion  sgnmean_en'
    prop_values = '-1.0   1.0     -1.0'
  []
  [emission_coeffs]
    type = ADGenericConstantMaterial
    prop_names = 'users_gamma'
    prop_values = '1.0'
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
  [mean_en_l2Error]
    type = ElementL2Error
    variable = mean_en
    function = mean_en_fun
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

  [potential_l2Error]
    type = ElementL2Error
    variable = potential
    function = potential_fun
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
  # end_time = 50
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
  [out]
    type = Exodus
    time_step_interval = 10
  []
[]
