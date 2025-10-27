[Mesh]
  [geo]
    type = FileMeshGenerator
    file = '2D_Coupling_Electons_Potential_Ions_MeanEnergy_Einstein_Relation_IC_out.e'
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
  [potential]
    initial_from_file_var = potential
  []
  [ion]
    initial_from_file_var = ion
  []
  [mean_en]
    initial_from_file_var = mean_en
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
  [potential_diffusion]
    type = CoeffDiffusionLin
    variable = potential
    position_units = 1.0
  []
  [ion_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = ion
    potential_units = V
  []
  [em_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = em
    potential_units = V
  []

  #Electron Energy Equations
  [mean_en_time_deriv]
    type = TimeDerivativeLog
    variable = mean_en
  []
  [mean_en_advection]
    type = EFieldAdvection
    variable = mean_en
    position_units = 1.0
  []
  [mean_en_diffusion]
    type = CoeffDiffusion
    variable = mean_en
    position_units = 1.0
  []
  [mean_en_diffusion_correction]
    type = ThermalConductivityDiffusion
    variable = mean_en
    electrons = em
    position_units = 1.0
  []
  [mean_en_joule_heating]
    type = JouleHeating
    variable = mean_en
    electrons = em
    position_units = 1.0
    potential_units = V
  []
  [mean_en_source]
    type = BodyForce
    variable = mean_en
    function = 'energy_source'
  []
[]

[AuxVariables]
  [potential_sol]
  []

  [mean_en_sol]
  []

  [em_sol]
  []

  [ion_sol]
  []
[]

[AuxKernels]
  [potential_sol]
    type = FunctionAux
    variable = potential_sol
    function = potential_fun
  []

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
[]

[Functions]
  #Material Variables
  #Electron diffusion coeff.
  [diffem_coeff]
    type = ConstantFunction
    value = 0.05
  []
  #Electron mobility coeff.
  [muem_coeff]
    type = ConstantFunction
    value = 0.01
  []
  #Electron energy diffusion coeff.
  [diffmean_en_coeff]
    type = ParsedFunction
    vars = 'diffem_coeff'
    vals = 'diffem_coeff'
    expression = '5.0 / 3.0 * diffem_coeff'
  []
  #Electron energy mobility coeff.
  [mumean_en_coeff]
    type = ParsedFunction
    vars = 'muem_coeff'
    vals = 'muem_coeff'
    expression = '5.0 / 3.0 * muem_coeff'
  []
  #Ion diffusion coeff.
  [diffion]
    type = ConstantFunction
    value = 0.1
  []
  #Ion mobility coeff.
  [muion]
    type = ConstantFunction
    value = 0.025
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
    value = 0.01
  []
  [diffpotential_mat]
    type = ParsedFunction
    symbol_names = 'diffpotential'
    symbol_values = 'diffpotential'
    expression = 'diffpotential * (1.6e-19 * 6.02e23)'
  []

  #Manufactured Solutions
  #The manufactured electron density solution
  [em_fun]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((sin(pi*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 1.0 + cos(pi/2*x)) / N_A)'
  []
  #The manufactured ion density solution
  [ion_fun]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((sin(pi*y) + 1.0 + 0.9*cos(pi/2*x)) / N_A)'
  []
  #The manufactured electron density solution
  [potential_fun]
    type = ParsedFunction
    vars = 'ee diffpotential'
    vals = 'ee diffpotential'
    expression = '-(ee*(2*cos((pi*x)/2) + cos(pi*y)*sin(2*pi*t)))/(5*diffpotential*pi^2)'
  []
  #The manufactured electron energy solution
  [energy_fun]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'sin(pi*y) + sin(2*pi*t)*cos(pi*y)*sin(pi*y) + 0.75 + cos(pi/2*x)'
  []
  [mean_en_fun]
    type = ParsedFunction
    vars = 'energy_fun em_fun'
    vals = 'energy_fun em_fun'
    expression = 'log(energy_fun) + em_fun'
  []

  #Electron diffusion coeff.
  [diffem]
    type = ParsedFunction
    vars = 'diffem_coeff energy_fun'
    vals = 'diffem_coeff energy_fun'
    expression = 'diffem_coeff * energy_fun'
  []
  #Electron mobility coeff.
  [muem]
    type = ParsedFunction
    vars = 'muem_coeff energy_fun'
    vals = 'muem_coeff energy_fun'
    expression = 'muem_coeff * energy_fun'
  []
  #Electron energy diffusion coeff.
  [diffmean_en]
    type = ParsedFunction
    vars = 'diffmean_en_coeff energy_fun'
    vals = 'diffmean_en_coeff energy_fun'
    expression = 'diffmean_en_coeff * energy_fun'
  []
  #Electron energy mobility coeff.
  [mumean_en]
    type = ParsedFunction
    vars = 'mumean_en_coeff energy_fun'
    vals = 'mumean_en_coeff energy_fun'
    expression = 'mumean_en_coeff * energy_fun'
  []

  #Source Terms in moles
  #The electron source term.
  [em_source]
    type = ParsedFunction
    vars = 'ee diffpotential diffem_coeff muem_coeff N_A'
    vals = 'ee diffpotential diffem_coeff muem_coeff N_A'
    expression = '((2*pi*cos(2*pi*t)*cos(pi*y))/5 - (diffem_coeff*pi^2*sin((pi*x)/2)^2)/4 -
                   diffem_coeff*pi*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5)*(cos(pi*y) -
                   sin(2*pi*t) + 2*cos(pi*y)^2*sin(2*pi*t)) +
                   (diffem_coeff*pi^2*cos((pi*x)/2)*(cos((pi*x)/2) + sin(pi*y) +
                   cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4))/4 + (diffem_coeff*pi^2*(5*sin(pi*y) +
                   cos(pi*y)*sin(2*pi*t))*(cos((pi*x)/2) + sin(pi*y) + cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4))/5 -
                   (ee*muem_coeff*sin((pi*x)/2)^2*(cos((pi*x)/2) + sin(pi*y) +
                   cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4))/(10*diffpotential) - (ee*muem_coeff*sin((pi*x)/2)^2*(cos((pi*x)/2) +
                   sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1))/(10*diffpotential) + (ee*muem_coeff*cos((pi*x)/2)*(cos((pi*x)/2) +
                   sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)*(cos((pi*x)/2) + sin(pi*y) +
                   cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4))/(10*diffpotential) +
                   (ee*muem_coeff*cos(pi*y)*sin(2*pi*t)*(cos((pi*x)/2) + sin(pi*y) +
                   (cos(pi*y)*sin(2*pi*t))/5 + 1)*(cos((pi*x)/2) + sin(pi*y) + cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4))/(5*diffpotential) +
                   (ee*muem_coeff*sin(2*pi*t)*sin(pi*y)*(cos(pi*y) - sin(2*pi*t) + 2*cos(pi*y)^2*sin(2*pi*t))*(cos((pi*x)/2) +
                   sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1))/(5*diffpotential) + (ee*muem_coeff*sin(2*pi*t)*sin(pi*y)*(pi*cos(pi*y) -
                   (pi*sin(2*pi*t)*sin(pi*y))/5)*(cos((pi*x)/2) + sin(pi*y) +
                   cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4))/(5*diffpotential*pi)) / N_A'
  []
  #The ion source term.
  [ion_source]
    type = ParsedFunction
    vars = 'ee diffpotential diffion muion N_A'
    vals = 'ee diffpotential diffion muion N_A'
    expression = '((diffion*pi^2*(9*cos((pi*x)/2) + 40*sin(pi*y)))/40 +
                   (9*ee*muion*sin((pi*x)/2)^2)/(100*diffpotential) -
                   (ee*muion*cos((pi*x)/2)*((9*cos((pi*x)/2))/10 + sin(pi*y) + 1))/(10*diffpotential) -
                   (ee*muion*cos(pi*y)*sin(2*pi*t)*sin(pi*y))/(5*diffpotential) -
                   (ee*muion*cos(pi*y)*sin(2*pi*t)*((9*cos((pi*x)/2))/10 + sin(pi*y) + 1))/(5*diffpotential)) / N_A'
  []
  [energy_source]
    type = ParsedFunction
    vars = 'ee diffpotential diffem_coeff muem_coeff N_A'
    vals = 'ee diffpotential diffem_coeff muem_coeff N_A'
    expression = '(((4*cos((pi*x)/2) + 4*sin(pi*y) + 4*cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3)*(172*ee*muem_coeff*cos(2*pi*t)^2 -
                   282*ee*muem_coeff + 180*ee*muem_coeff*cos((pi*x)/2)^2 + 160*ee*muem_coeff*cos((pi*x)/2)^3 +
                   664*ee*muem_coeff*cos(pi*y)^2 - 480*ee*muem_coeff*cos(pi*y)^4 - 66*ee*muem_coeff*cos((pi*x)/2) -
                   296*ee*muem_coeff*sin(pi*y) + 200*diffem_coeff*diffpotential*pi^2 -
                   664*ee*muem_coeff*cos(2*pi*t)^2*cos(pi*y)^2 + 480*ee*muem_coeff*cos(2*pi*t)^2*cos(pi*y)^4 +
                   364*ee*muem_coeff*cos(pi*y)*sin(2*pi*t) - 90*ee*muem_coeff*cos((pi*x)/2)*sin(pi*y) +
                   75*diffem_coeff*diffpotential*pi^2*cos((pi*x)/2) + 140*diffem_coeff*diffpotential*pi^2*sin(pi*y) +
                   16*ee*muem_coeff*cos(2*pi*t)^2*cos((pi*x)/2) - 8*ee*muem_coeff*cos((pi*x)/2)*cos(pi*y)^2 +
                   176*ee*muem_coeff*cos(2*pi*t)^2*sin(pi*y) - 320*ee*muem_coeff*cos(pi*y)^3*sin(2*pi*t) +
                   200*ee*muem_coeff*cos((pi*x)/2)^2*sin(pi*y) + 464*ee*muem_coeff*cos(pi*y)^2*sin(pi*y) +
                   300*diffem_coeff*diffpotential*pi^2*cos((pi*x)/2)^2 - 1200*diffem_coeff*diffpotential*pi^2*cos(pi*y)^2 +
                   160*ee*muem_coeff*cos(2*pi*t)^2*cos((pi*x)/2)*sin(pi*y) +
                   104*ee*muem_coeff*cos((pi*x)/2)^2*cos(pi*y)*sin(2*pi*t) -
                   40*ee*muem_coeff*cos((pi*x)/2)*cos(pi*y)^3*sin(2*pi*t) +
                   408*ee*muem_coeff*cos((pi*x)/2)*cos(pi*y)^2*sin(pi*y) + 96*ee*muem_coeff*cos(pi*y)^3*sin(2*pi*t)*sin(pi*y) +
                   160*diffem_coeff*diffpotential*pi^2*cos(2*pi*t)^2*sin(pi*y) -
                   2000*diffem_coeff*diffpotential*pi^2*cos(pi*y)^3*sin(2*pi*t) +
                   400*diffem_coeff*diffpotential*pi^2*cos(pi*y)^2*sin(pi*y) -
                   32*ee*muem_coeff*cos(2*pi*t)^2*cos((pi*x)/2)*cos(pi*y)^2 -
                   464*ee*muem_coeff*cos(2*pi*t)^2*cos(pi*y)^2*sin(pi*y) +
                   186*ee*muem_coeff*cos((pi*x)/2)*cos(pi*y)*sin(2*pi*t) + 272*ee*muem_coeff*cos(pi*y)*sin(2*pi*t)*sin(pi*y) +
                   1260*diffem_coeff*diffpotential*pi^2*cos(pi*y)*sin(2*pi*t) +
                   500*diffem_coeff*diffpotential*pi^2*cos((pi*x)/2)*sin(pi*y) -
                   408*ee*muem_coeff*cos(2*pi*t)^2*cos((pi*x)/2)*cos(pi*y)^2*sin(pi*y) -
                   96*ee*muem_coeff*cos(2*pi*t)^2*cos(pi*y)^3*sin(2*pi*t)*sin(pi*y) -
                   400*diffem_coeff*diffpotential*pi^2*cos(2*pi*t)^2*cos(pi*y)^2*sin(pi*y) +
                   448*ee*muem_coeff*cos((pi*x)/2)*cos(pi*y)*sin(2*pi*t)*sin(pi*y) +
                   80*diffem_coeff*diffpotential*pi^2*cos((pi*x)/2)*cos(pi*y)*sin(2*pi*t) +
                   240*diffem_coeff*diffpotential*pi^2*cos(pi*y)*sin(2*pi*t)*sin(pi*y) +
                   48*ee*muem_coeff*cos(2*pi*t)^2*cos(pi*y)*sin(2*pi*t)*sin(pi*y) +
                   80*ee*muem_coeff*cos((pi*x)/2)^2*cos(pi*y)*sin(2*pi*t)*sin(pi*y) +
                   100*diffem_coeff*diffpotential*pi^2*cos((pi*x)/2)*cos(pi*y)*sin(2*pi*t)*sin(pi*y)))/(960*diffpotential) +
                   (pi*cos(2*pi*t)*cos(pi*y)*(4*cos((pi*x)/2) + 24*sin(pi*y) + 20*cos((pi*x)/2)*sin(pi*y) + 20*sin(pi*y)^2 +
                   8*cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3))/10 - (diffem_coeff*pi^2*sin((pi*x)/2)^2*(cos((pi*x)/2) +
                   sin(pi*y) + cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4))/4 - (diffem_coeff*pi^2*sin((pi*x)/2)^2*(cos((pi*x)/2) +
                   sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1))/4 - diffem_coeff*pi^2*(cos(pi*y) - sin(2*pi*t) +
                   2*cos(pi*y)^2*sin(2*pi*t))^2*(cos((pi*x)/2) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1) +
                   (diffem_coeff*pi^2*cos((pi*x)/2)*(cos((pi*x)/2) + sin(pi*y) +
                   (cos(pi*y)*sin(2*pi*t))/5 + 1)*(cos((pi*x)/2) + sin(pi*y) + cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4))/4 -
                   diffem_coeff*pi*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5)*(cos(pi*y) - sin(2*pi*t) +
                   2*cos(pi*y)^2*sin(2*pi*t))*(cos((pi*x)/2) + sin(pi*y) + cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4) +
                   (ee*sin(2*pi*t)*sin(pi*y)*(diffem_coeff*(pi*cos(pi*y) - (pi*sin(2*pi*t)*sin(pi*y))/5)*(cos((pi*x)/2) +
                   sin(pi*y) + cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4) - (ee*muem_coeff*sin(2*pi*t)*sin(pi*y)*(cos((pi*x)/2) +
                   sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)*(cos((pi*x)/2) + sin(pi*y) +
                   cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4))/(5*diffpotential*pi)))/(5*diffpotential*pi) +
                   diffem_coeff*pi^2*sin(pi*y)*(4*cos(pi*y)*sin(2*pi*t) + 1)*(cos((pi*x)/2) + sin(pi*y) +
                   (cos(pi*y)*sin(2*pi*t))/5 + 1)*(cos((pi*x)/2) + sin(pi*y) + cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3/4) -
                   (ee*sin((pi*x)/2)^2*(4*cos((pi*x)/2) + 4*sin(pi*y) +
                   4*cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 3)*(10*ee*muem_coeff + 10*ee*muem_coeff*cos((pi*x)/2) +
                   10*ee*muem_coeff*sin(pi*y) + 25*diffem_coeff*diffpotential*pi^2 +
                   2*ee*muem_coeff*cos(pi*y)*sin(2*pi*t)))/(1000*diffpotential^2*pi^2)) / N_A'
  []

  [em_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((3.0 + cos(pi/2*x)) / N_A)'
  []
  [ion_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    expression = 'log((3.0 + 0.9*cos(pi/2*x)) / N_A)'
  []
  [mean_en_ICs]
    type = ParsedFunction
    vars = 'em_ICs'
    vals = 'em_ICs'
    expression = 'log(32. + cos(pi/2*x)) + em_ICs'
  []
[]

[BCs]
  [potential_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_fun'
    boundary = '0 1 2 3'
    preset = true
  []

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
[]

[Materials]
  [field_solver]
    type = FieldSolverMaterial
    potential = potential
  []
  [Material_Coeff]
    type = GenericFunctionMaterial
    prop_names = 'e N_A'
    prop_values = 'ee N_A'
  []
  [ADMaterial_Coeff_Set1]
    type = ADGenericFunctionMaterial
    prop_names = 'diffpotential     diffion muion'
    prop_values = 'diffpotential_mat diffion muion'
  []
  [Material_Coeff_Set2]
    type = ADMMSEEDFRates
    electrons = em
    electron_energy = mean_en
    prop_names = 'diffem        muem        diffmean_en        mumean_en'
    prop_values = 'diffem        muem        diffmean_en        mumean_en'
    d_prop_d_actual_mean_en = 'diffem_coeff  muem_coeff  diffmean_en_coeff  mumean_en_coeff'
  []
  [Charge_Signs]
    type = GenericConstantMaterial
    prop_names = 'sgnem  sgnion  sgnmean_en'
    prop_values = '-1.0   1.0     -1.0'
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
  [mean_en_l2Error]
    type = ElementL2Error
    variable = mean_en
    function = mean_en_fun
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
    time_step_interval = 10
  []
[]
