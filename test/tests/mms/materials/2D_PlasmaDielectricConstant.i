[Mesh]
  [geo]
    type = FileMeshGenerator
    file = '2D_PlasmaDielectricConstant_IC_out.e'
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
[]

# [ICs]
#   [em_IC]
#     type = FunctionIC
#     function = em_ICs
#     variable = em
#   []
# []

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
[]

[AuxVariables]
  [potential]
  []

  [em_sol]
  []

  [dielectric_real]
    family = MONOMIAL
    order = FIRST
  []
  [dielectric_image]
    family = MONOMIAL
    order = FIRST
  []

  [dielectric_real_grad]
    family = MONOMIAL_VEC
    order = FIRST
  []
  [dielectric_image_grad]
    family = MONOMIAL_VEC
    order = FIRST
  []

  [d_dielectric_real_dt]
    family = MONOMIAL
    order = FIRST
  []
  [d_dielectric_image_dt]
    family = MONOMIAL
    order = FIRST
  []
[]

[AuxKernels]
  [potential_sol]
    type = FunctionAux
    variable = potential
    function = potential_fun
  []

  [em_sol]
    type = FunctionAux
    variable = em_sol
    function = em_fun
  []


  [dielectric_real]
    type = ADMaterialRealAux
    variable = dielectric_real
    property = plasma_dielectric_constant_real
  []
  [dielectric_image]
    type = ADMaterialRealAux
    variable = dielectric_image
    property = plasma_dielectric_constant_imag
  []

  [dielectric_real_grad]
    type = ADVectorMaterialRealVectorValueAux
    variable = dielectric_real_grad
    property = plasma_dielectric_constant_real_grad
  []
  [dielectric_image_grad]
    type = ADVectorMaterialRealVectorValueAux
    variable = dielectric_image_grad
    property = plasma_dielectric_constant_imag_grad
  []

  [d_dielectric_real_dt]
    type = ADMaterialRealAux
    variable = d_dielectric_real_dt
    property = plasma_dielectric_constant_real_dot
  []
  [d_dielectric_image_dt]
    type = ADMaterialRealAux
    variable = d_dielectric_image_dt
    property = plasma_dielectric_constant_imag_dot
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


#Manufactured Solutions
  #The manufactured electron density solution
  [em_fun]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((sin(pi*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 1.0 + cos(pi/2*x)) / N_A)'
  []
  #The manufactured electron density solution
  [potential_fun]
    type = ParsedFunction
    vars = 'ee diffpotential'
    vals = 'ee diffpotential'
    value = '-(ee*(2*cos((pi*x)/2) + cos(pi*y)*sin(2*pi*t)))/(5*diffpotential*pi^2)'
  []

#Source Terms in moles
  #The electron source term.
  [em_source]
    type = ParsedFunction
    vars = 'ee diffem_coeff muem_coeff diffpotential N_A'
    vals = 'ee diffem_coeff muem_coeff diffpotential N_A'
    value = '(diffem_coeff*(pi^2*sin(pi*y) + (pi^2*cos(pi*y)*sin(2*pi*t))/5) +
              (2*pi*cos(2*pi*t)*cos(pi*y))/5 + (diffem_coeff*pi^2*cos((pi*x)/2))/4 +
              (ee*muem_coeff*(5*cos((pi*x)/2) - 4*cos(2*pi*t)^2*cos(pi*y)^2 +
              10*cos(pi*y)*sin(2*pi*t) + 5*cos((pi*x)/2)*sin(pi*y) + 2*cos(2*pi*t)^2 +
              10*cos((pi*x)/2)^2 + 4*cos(pi*y)^2 + 11*cos((pi*x)/2)*cos(pi*y)*sin(2*pi*t) +
              20*cos(pi*y)*sin(2*pi*t)*sin(pi*y) - 7))/(50*diffpotential)) / N_A'
  []

  [em_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((3.0 + cos(pi/2*x)) / N_A)'
  []

  [omega]
    type = ParsedFunction
    expression = '2*pi*6.207'
  []
  [nu]
    type = ParsedFunction
    expression = '2*pi*6.525'
  []
  [epsilon_0]
    type = ParsedFunction
    expression = '8.8542e-12'
  []
  [ec]
    type = ParsedFunction
    expression = '1.6022e-19'
  []
  [m_e]
    type = ParsedFunction
    expression = '9.1095e-31'
  []

  [dielectric_real_fun]
    type = ParsedFunction
    expression = '-ec^2*(sin(y*pi) + 0.2*sin(2*pi*t)*cos(y*pi) + cos((1/2)*x*pi) + 1.0)/(epsilon_0*m_e*(nu^2 + omega^2)) + 1'
    symbol_names =  'omega m_e ec nu epsilon_0'
    symbol_values = 'omega m_e ec nu epsilon_0'
  []
  [dielectric_image_fun]
    type = ParsedFunction
    expression = '-1.0*ec^2*nu*(sin(y*pi) + 0.2*sin(2*pi*t)*cos(y*pi) + cos((1/2)*x*pi) + 1.0)/(epsilon_0*m_e*(nu^2*omega + omega^3))'
    symbol_names =  'omega m_e ec nu epsilon_0'
    symbol_values = 'omega m_e ec nu epsilon_0'
  []

  [dielectric_real_grad_fun]
    type = ParsedVectorFunction
    symbol_names =  'omega m_e ec nu epsilon_0'
    symbol_values = 'omega m_e ec nu epsilon_0'
    expression_x = '(1/2)*pi*ec^2*sin((1/2)*x*pi)/(epsilon_0*m_e*(nu^2 + omega^2))'
    expression_y = '-ec^2*(-0.2*pi*sin(y*pi)*sin(2*pi*t) + pi*cos(y*pi))/(epsilon_0*m_e*(nu^2 + omega^2))'
  []
  [dielectric_image_grad_fun]
    type = ParsedVectorFunction
    symbol_names =  'omega m_e ec nu epsilon_0'
    symbol_values = 'omega m_e ec nu epsilon_0'
    expression_x = '0.5*pi*ec^2*nu*sin((1/2)*x*pi)/(epsilon_0*m_e*(nu^2*omega + omega^3))'
    expression_y = '-1.0*ec^2*nu*(-0.2*pi*sin(y*pi)*sin(2*pi*t) + pi*cos(y*pi))/(epsilon_0*m_e*(nu^2*omega + omega^3))'
  []

  [d_dielectric_real_dt_fun]
    type = ParsedFunction
    symbol_names =  'omega m_e ec nu epsilon_0'
    symbol_values = 'omega m_e ec nu epsilon_0'
    expression = '-0.4*pi*ec^2*cos(y*pi)*cos(2*pi*t)/(epsilon_0*m_e*(nu^2 + omega^2))'
  []
  [d_dielectric_image_dt_fun]
    type = ParsedFunction
    symbol_names =  'omega m_e ec nu epsilon_0'
    symbol_values = 'omega m_e ec nu epsilon_0'
    expression = '-0.4*pi*ec^2*nu*cos(y*pi)*cos(2*pi*t)/(epsilon_0*m_e*(nu^2*omega + omega^3))'
  []

  [d2_dielectric_real_dt2_fun]
    type = ParsedFunction
    symbol_names =  'omega m_e ec nu epsilon_0'
    symbol_values = 'omega m_e ec nu epsilon_0'
    expression = '0.8*pi^2*ec^2*sin(2*pi*t)*cos(y*pi)/(epsilon_0*m_e*(nu^2 + omega^2))'
  []
  [d2_dielectric_image_dt2_fun]
    type = ParsedFunction
    symbol_names =  'omega m_e ec nu epsilon_0'
    symbol_values = 'omega m_e ec nu epsilon_0'
    expression = '0.8*pi^2*ec^2*nu*sin(2*pi*t)*cos(y*pi)/(epsilon_0*m_e*(nu^2*omega + omega^3))'
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
[]

[Materials]
  [Plasma_dielectric]
    type = PlasmaDielectricConstant
    driving_frequency = 6.207
    electron_neutral_collision_frequency = 6.525
    em = em
  []
  [field_solver]
    type = FieldSolverMaterial
    potential = potential
  []
  [Material_Coeff]
    type = GenericFunctionMaterial
    prop_names =  'e N_A'
    prop_values = 'ee N_A'
  []
  [ADMaterial_Coeff]
    type = ADGenericFunctionMaterial
    prop_names =  'diffem        muem        diffpotential'
    prop_values = 'diffem_coeff  muem_coeff  diffpotential'
  []
  [Charge_Signs]
    type = GenericConstantMaterial
    prop_names =  'sgnem'
    prop_values = '-1.0'
  []
[]

[Postprocessors]
  [em_l2Error]
    type = ElementL2Error
    variable = em
    function = em_fun
  []

  [dielectric_real_Error]
    type = ElementL2Error
    variable = dielectric_real
    function = dielectric_real_fun
  []
  [dielectric_image_Error]
    type = ElementL2Error
    variable = dielectric_image
    function = dielectric_image_fun
  []

  [dielectric_real_grad_Error]
    type = ElementVectorL2Error
    variable = dielectric_real_grad
    function = dielectric_real_grad_fun
  []
  [dielectric_image_grad_Error]
    type = ElementVectorL2Error
    variable = dielectric_image_grad
    function = dielectric_image_grad_fun
  []

  [d_dielectric_real_dt_Error]
    type = ElementL2Error
    variable = d_dielectric_real_dt
    function = d_dielectric_real_dt_fun
  []
  [d_dielectric_image_dt_Error]
    type = ElementL2Error
    variable = d_dielectric_image_dt
    function = d_dielectric_image_dt_fun
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
  # start_time = 0
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
    interval = 10
  []
[]
