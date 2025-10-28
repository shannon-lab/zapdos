# Test for ElectrostaticPermittivity to provide non-default values of
# the electrostatic permittivity (the default value being the permittivity of free space)
#
# The equations being tested is:
#   \nabla \cdot \nabla (\varepsilon potential) = F
#
# Where:
#   - \varepsilon is the electrostatic permittivity (set to a value of unity for this test)
#   - potential is the electrostatic potential
#   - F is the forcing term
#
# Manufactured solution: potential = sin(2*pi*x)*sin(2*pi*y)

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 8
  ny = 8
[]

[GlobalParams]
  position_units = 1.0
[]

[Variables]
  [potential]
  []
[]

[Kernels]
  [diff]
    type = CoeffDiffusionLin
    variable = potential
  []
  [force]
    type = BodyForce
    variable = potential
    function = force
  []
[]

[Functions]
  [exact]
    type = ParsedFunction
    expression = 'sin(2*pi*x)*sin(2*pi*y)'
  []
  [force]
    type = ParsedFunction
    expression = '8*pi^2*sin(2*x*pi)*sin(2*y*pi)'
  []
[]

[BCs]
  [all]
    type = FunctionDirichletBC
    variable = potential
    function = exact
    boundary = 'left right top bottom'
  []
[]

[Materials]
  [permittivity_of_unity]
    type = ElectrostaticPermittivity
    potential = potential
    permittivity = 1.0
  []
[]

[Postprocessors]
  [error]
    type = ElementL2Error
    function = exact
    variable = potential
  []
  [h]
    type = AverageElementSize
  []
[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
  csv = true
[]
