[Mesh]
  [./gmg]
    type = GeneratedMeshGenerator
    nx = 10
    ny = 10
    dim = 2
  [../]
[]

[Variables]
  [./u]
  [../]
[]

[Kernels]
  [./time_derivative]
    type = ADTimeDerivative
    variable = u
  [../]
  [./diff]
    type = ADDiffusion
    variable = u
  [../]
  [./ffn]
    type = ADBodyForce
    variable = u
    function = ffn_u
  [../]
[]

[BCs]
  [./u_left]
    type = ADDirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./u_right]
    type = ADFunctionDirichletBC
    variable = u
    boundary = right
    function = '5*t'
  [../]
[]

[Functions]
  [./ffn_u]
    type = ParsedFunction
    value = '5*x*x - 10*t'
  [../]
  [./eps_r_real_func]
    type = ParsedFunction
    vars = 'eps charge mass freq nu'
    vals = '8.8542e-12 1.6022e-19 9.1095e-31 40e6 0.5e9'
    value = '1 - (charge*charge/eps/mass)*(exp(5*x*x*t)/((2*pi*freq)^2 + nu^2))'
  [../]
  [./eps_r_imag_func]
    type = ParsedFunction
    vars = 'eps charge mass freq nu'
    vals = '8.8542e-12 1.6022e-19 9.1095e-31 40e6 0.5e9'
    value = '-(charge*charge/eps/mass)*(nu*exp(5*x*x*t)/((2*pi*freq)^3 + (2*pi*freq)*nu^2))'
  [../]
  [./eps_r_real_dotdot_func]
    type = ParsedFunction
    vars = 'eps charge mass freq nu'
    vals = '8.8542e-12 1.6022e-19 9.1095e-31 40e6 0.5e9'
    value = '-(charge*charge/eps/mass)*(25*(x^4)*exp(5*x*x*t)/((2*pi*freq)^2 + nu^2))'
  [../]
  [./eps_r_imag_dotdot_func]
    type = ParsedFunction
    vars = 'eps charge mass freq nu'
    vals = '8.8542e-12 1.6022e-19 9.1095e-31 40e6 0.5e9'
    value = '-(charge*charge/eps/mass)*(25*(x^4)*nu*exp(5*x*x*t)/((2*pi*freq)^3 + (2*pi*freq)*nu^2))'
  [../]
[]

[Materials]
  [./plasma_dielectric]
    type = PlasmaDielectricConstant
    drive_frequency = 40e6
    electron_neutral_collision_frequency = 0.5e9
    em = u
    output_properties = 'plasma_dielectric_constant_real plasma_dielectric_constant_imag plasma_dielectric_constant_real_dot_dot plasma_dielectric_constant_imag_dot_dot'
  [../]
[]

# Uses automatic output auxvars from material
[Postprocessors]
  [./eps_r_real_L2Error]
    type = ElementL2Error
    variable = plasma_dielectric_constant_real
    function = eps_r_real_func
  [../]
  [./eps_r_imag_L2Error]
    type = ElementL2Error
    variable = plasma_dielectric_constant_imag
    function = eps_r_imag_func
  [../]
  [./eps_r_real_dotdot_L2Error]
    type = ElementL2Error
    variable = plasma_dielectric_constant_real_dot_dot
    function = eps_r_real_dotdot_func
  [../]
  [./eps_r_imag_dotdot_L2Error]
    type = ElementL2Error
    variable = plasma_dielectric_constant_imag_dot_dot
    function = eps_r_imag_dotdot_func
  [../]
[]

[Executioner]
  type = Transient
  solve_type = NEWTON
  dt = 4e-10
  scheme = newmark-beta
  num_steps = 5
[]

[Outputs]
  [./out]
    type = Exodus
    output_material_properties = true
  [../]
[]
