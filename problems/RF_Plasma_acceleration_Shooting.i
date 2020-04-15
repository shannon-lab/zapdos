#This file performs the accelerated by Shooting Method
#Desciption: Value are transferred from the main app to this file and then
#passed to an other sub app. In that sub app, the simulation runs for one
#RF cycle and the results are transfer back to this file. Along with the
#metastable from the sub app (Ar*T), sub app also calculates the
#sensitivity values as defined in the Shooting Method.
#With the metastable values from the main app (Ar*S), the sub app (Ar*T)
#and the sensitivity values, then Ar* is accelerated by the difference between
#Ar*S and Ar*T time a growth factor determined by the sensitivity values
#That resulting value is then passed up to the main app

dom0Scale=25.4e-3

[Mesh]
  type = FileMesh
  file = 'Lymberopoulos_paper.msh'
[]

[GlobalParams]
  potential_units = kV
  use_moles = true
[]

[MeshModifiers]
  [./left]
    type = SideSetsFromNormals
    normals = '-1 0 0'
    new_boundary = 'left'
  [../]
  [./right]
    type = SideSetsFromNormals
    normals = '1 0 0'
    new_boundary = 'right'
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

[MultiApps]
  [./SensitivityMatrix]
    type = FullSolveMultiApp
    input_files = 'RF_Plasma_acceleration_SensitivityMatrix.i'
  [../]
[]

[Transfers]
  [./em_to_sub]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = SensitivityMatrix
    source_variable = em
    variable = em
  [../]
  [./Ar+_to_sub]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = SensitivityMatrix
    source_variable = Ar+
    variable = Ar+
  [../]
  [./mean_en_to_sub]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = SensitivityMatrix
    source_variable = mean_en
    variable = mean_en
  [../]
  [./potential_to_sub]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = SensitivityMatrix
    source_variable = potential
    variable = potential
  [../]
  [./Ar*_to_sub]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = SensitivityMatrix
    source_variable = Ar*
    variable = Ar*
  [../]
  [./Deriv_to_sub]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = SensitivityMatrix
    source_variable = SMDerivReset
    variable = SMDeriv
  [../]

  [./Ar*T_from_sub]
    type = MultiAppCopyTransfer
    direction = from_multiapp
    multi_app = SensitivityMatrix
    source_variable = Ar*
    variable = Ar*T
  [../]
  [./Deriv_from_sub]
    type = MultiAppCopyTransfer
    direction = from_multiapp
    multi_app = SensitivityMatrix
    source_variable = SMDeriv
    variable = SMDeriv
  [../]
[]

[Postprocessors]
  [./Meta_Relative_Diff]
    type = RelativeElementL2Difference
    variable = Ar*
    other_variable = Ar*S
    execute_on = 'TIMESTEP_END'
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
  print_perf_log = true
  [./out]
    type = Exodus
  [../]
[]
