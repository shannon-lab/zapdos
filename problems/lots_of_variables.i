[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
  print_perf_log = true
[]

[LotsOfCoeffDiffusion]
  variables = 'spec1 spec2 spec3'
  diffusion_coeffs = 'Dunity Dunity Dunity'
[]

[LotsOfVariables]
  variables = 'spec1 spec2 spec3'
[]

[Materials]
  [./water]
    block = 0
    type = Water
    user_potential_mult = 1.0
    user_electron_mult = 1.0e20
  [../]
[]

