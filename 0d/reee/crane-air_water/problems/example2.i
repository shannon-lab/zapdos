[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 1
[]

[Variables]
  # ODE variables
  [./y01]
    family = SCALAR
    order = FIRST
    initial_condition = 0.4
  [../]

  [./y02]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6
  [../]

  [./y03]
    family = SCALAR
    order = FIRST
    initial_condition = 0.0
  [../]

  [./y11]
    family = SCALAR
    order = FIRST
    initial_condition = 1.0
  [../]

  [./y12]
    family = SCALAR
    order = FIRST
    initial_condition = 0.0
  [../]

  [./y13]
    family = SCALAR
    order = FIRST
    initial_condition = 0.0
  [../]

  [./y21]
    family = SCALAR
    order = FIRST
    initial_condition = 0.2
  [../]

  [./y22]
    family = SCALAR
    order = FIRST
    initial_condition = 0.05
  [../]

  [./y23]
    family = SCALAR
    order = FIRST
    initial_condition = 0.75
  [../]

  # [./y31]
  #   family = SCALAR
  #   order = FIRST
  #   initial_condition = 0.5
  # [../]
  #
  # [./y32]
  #   family = SCALAR
  #   order = FIRST
  #   initial_condition = 0.2
  # [../]
  #
  # [./y33]
  #   family = SCALAR
  #   order = FIRST
  #   initial_condition = 0.3
  # [../]

  [./y31]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
  [../]

  [./y32]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6
  [../]

  [./y33]
    family = SCALAR
    order = FIRST
    initial_condition = 0.39
  [../]

  [./y41]
    family = SCALAR
    order = FIRST
    initial_condition = 0.4
  [../]

  [./y42]
    family = SCALAR
    order = FIRST
    initial_condition = 0.4
  [../]

  [./y43]
    family = SCALAR
    order = FIRST
    initial_condition = 0.2
  [../]
[]

[ScalarKernels]
  [./dy01_dt]
    type = ODETimeDerivative
    variable = y01
  [../]

  [./dy02_dt]
    type = ODETimeDerivative
    variable = y02
  [../]

  [./dy03_dt]
    type = ODETimeDerivative
    variable = y03
  [../]

  [./dy11_dt]
    type = ODETimeDerivative
    variable = y11
  [../]

  [./dy12_dt]
    type = ODETimeDerivative
    variable = y12
  [../]

  [./dy13_dt]
    type = ODETimeDerivative
    variable = y13
  [../]

  [./dy21_dt]
    type = ODETimeDerivative
    variable = y21
  [../]

  [./dy22_dt]
    type = ODETimeDerivative
    variable = y22
  [../]

  [./dy23_dt]
    type = ODETimeDerivative
    variable = y23
  [../]

  [./dy31_dt]
    type = ODETimeDerivative
    variable = y31
  [../]

  [./dy32_dt]
    type = ODETimeDerivative
    variable = y32
  [../]

  [./dy33_dt]
    type = ODETimeDerivative
    variable = y33
  [../]

  [./dy41_dt]
    type = ODETimeDerivative
    variable = y41
  [../]

  [./dy42_dt]
    type = ODETimeDerivative
    variable = y42
  [../]

  [./dy43_dt]
    type = ODETimeDerivative
    variable = y43
  [../]
[]

# Stiff
[ChemicalReactions]
  [./ScalarNetwork]
    species = 'y01 y02 y03 y11 y12 y13 y21 y22 y23 y31 y32 y33 y41 y42 y43'
    # reaction_coefficient_format = 'rate'

    reactions = 'y01 -> y02          : 2.7e10
                 y01 -> y03          : 9.0e8
                 y02 -> y01          : 3.8e1
                 y03 -> y01          : 1.7e1
                 y02 -> y03          : 1.0e6
                 y03 -> y02          : 7.5e4
                 y11 -> y12          : 2.7e10
                y11 -> y13          : 9.0e8
                y12 -> y11          : 3.8e1
                y13 -> y11          : 1.7e1
                y12 -> y13          : 1.0e6
                y13 -> y12          : 7.5e4
                y21 -> y22          : 2.7e10
                y21 -> y23          : 9.0e8
                y22 -> y21          : 3.8e1
                y23 -> y21          : 1.7e1
                y22 -> y23          : 1.0e6
                y23 -> y22          : 7.5e4
                y31 -> y32          : 2.7e10
                y31 -> y33          : 9.0e8
                y32 -> y31          : 3.8e1
                y33 -> y31          : 1.7e1
                y32 -> y33          : 1.0e6
                y33 -> y32          : 7.5e4
                y41 -> y42          : 2.7e10
                y41 -> y43          : 9.0e8
                y42 -> y41          : 3.8e1
                y43 -> y41          : 1.7e1
                y42 -> y43          : 1.0e6
                y43 -> y42          : 7.5e4'
  [../]
[]

# [ChemicalReactions]
#   [./ScalarNetwork]
#     species = 'y01 y02 y03 y11 y12 y13 y21 y22 y23 y31 y32 y33 y41 y42 y43'
#     # reaction_coefficient_format = 'rate'
#
#     reactions = 'y01 -> y02          : 9e1
#                  y01 -> y03          : 1e2
#                  y02 -> y01          : 1e1
#                  y03 -> y01          : 2e1
#                  y02 -> y03          : 5e1
#                  y03 -> y02          : 3e1
#                  y11 -> y12          : 9e1
#                 y11 -> y13          : 1e2
#                 y12 -> y11          : 1e1
#                 y13 -> y11          : 2e1
#                 y12 -> y13          : 5e1
#                 y13 -> y12          : 3e1
#                 y21 -> y22          : 9e1
#                 y21 -> y23          : 1e2
#                 y22 -> y21          : 1e1
#                 y23 -> y21          : 2e1
#                 y22 -> y23          : 5e1
#                 y23 -> y22          : 3e1
#                 y31 -> y32          : 9e1
#                 y31 -> y33          : 1e2
#                 y32 -> y31          : 1e1
#                 y33 -> y31          : 2e1
#                 y32 -> y33          : 5e1
#                 y33 -> y32          : 3e1
#                 y41 -> y42          : 9e1
#                 y41 -> y43          : 1e2
#                 y42 -> y41          : 1e1
#                 y43 -> y41          : 2e1
#                 y42 -> y43          : 5e1
#                 y43 -> y42          : 3e1'
#   [../]
# []

# Nonstiff
# [ChemicalReactions]
#   [./ScalarNetwork]
#     species = 'y1 y2 y3'
#     reaction_coefficient_format = 'rate'
#
#     reactions = 'y1 -> y2          : 9e1
#                  y1 -> y3          : 1e2
#                  y2 -> y1          : 1e1
#                  y3 -> y1          : 2e1
#                  y2 -> y3          : 5e1
#                  y3 -> y2          : 3e1'
#   [../]
# []


[Executioner]
  type = Transient
  end_time = 1e-1
  solve_type = NEWTON
  dtmin = 1e-20

  steady_state_detection = true
  steady_state_tolerance = 1e-06
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.9
    dt = 1e-8
    growth_factor = 1.01
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  csv = true
  interval = 10
[]
