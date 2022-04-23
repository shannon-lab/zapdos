dom0Scale=25.4e-3

[GlobalParams]
  potential_units = kV
  use_moles = true
[]

[Mesh]
  [./file]
    type = FileMeshGenerator
    file = 'Lymberopoulos_paper.msh'
  [../]
  [./left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = file
  [../]
  [./right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  [../]
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [./Ar*]
  [../]
[]

[AuxVariables]
  [./em]
  [../]
  [./Ar+]
  [../]
  [./mean_en]
  [../]
  [./potential]
  [../]
  [./Ar*S]
  [../]

  [./Ar*T]
  [../]
  [./SMDeriv]
  [../]

  [./SMDerivReset]
    initial_condition = 1.0
  [../]
[]

[Kernels]
  [./Shoot_Method]
    type = ShootMethodLog
    variable = Ar*
    density_at_start_cycle = Ar*S
    density_at_end_cycle = Ar*T
    sensitivity_variable = SMDeriv
    growth_limit = 100.0
  [../]
[]

[BCs]
  [./Ar*_physical_right_diffusion]
    type = LogDensityDirichletBC
    variable = Ar*
    boundary = 'right'
    value = 1e-5
  [../]
  [./Ar*_physical_left_diffusion]
    type = LogDensityDirichletBC
    variable = Ar*
    boundary = 'left'
    value = 1e-5
  [../]
[]

#MultiApp used to calculate the non-accelerated density for 1RF cycle.
#This is used to get A*T (density at end of cycle) and
##the sensitivity variable needed for the shoot method.
[MultiApps]
  [./SensitivityMatrix]
    type = FullSolveMultiApp
    input_files = 'Acceleration_By_Shooting_Method_SensitivityMatrix.i'
  [../]
[]

[Transfers]
  [./em_to_sub]
    type = MultiAppCopyTransfer
    to_multi_app = SensitivityMatrix
    source_variable = em
    variable = em
  [../]
  [./Ar+_to_sub]
    type = MultiAppCopyTransfer
    to_multi_app = SensitivityMatrix
    source_variable = Ar+
    variable = Ar+
  [../]
  [./mean_en_to_sub]
    type = MultiAppCopyTransfer
    to_multi_app = SensitivityMatrix
    source_variable = mean_en
    variable = mean_en
  [../]
  [./potential_to_sub]
    type = MultiAppCopyTransfer
    to_multi_app = SensitivityMatrix
    source_variable = potential
    variable = potential
  [../]
  [./Ar*_to_sub]
    type = MultiAppCopyTransfer
    to_multi_app = SensitivityMatrix
    source_variable = Ar*
    variable = Ar*
  [../]
  [./Deriv_to_sub]
    type = MultiAppCopyTransfer
    to_multi_app = SensitivityMatrix
    source_variable = SMDerivReset
    variable = SMDeriv
  [../]

  [./Ar*T_from_sub]
    type = MultiAppCopyTransfer
    from_multi_app = SensitivityMatrix
    source_variable = Ar*
    variable = Ar*T
  [../]
  [./Deriv_from_sub]
    type = MultiAppCopyTransfer
    from_multi_app = SensitivityMatrix
    source_variable = SMDeriv
    variable = SMDeriv
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
  type = Steady

  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type'
  petsc_options_value = 'lu NONZERO 1.e-10 fgmres'
[]

[Outputs]
  perf_graph = true
  [./out]
    type = Exodus
  [../]
[]
