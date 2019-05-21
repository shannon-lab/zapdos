[GlobalParams]
  f = 10e9
[]

[Mesh]
  type = FileMesh
  file = 'TM_dieletric.msh'
  # construct_side_list_from_node_list = 1
[]

[MeshModifiers]
  [./interface_dielectric]
    type = SideSetsBetweenSubdomains
    master_block = '1'
    paired_block = '0'
    new_boundary = 'interface_dielectric'
  [../]
[]


[Problem]
  type = FEProblem
  coord_type = RZ
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON

  petsc_options_iname = '-pc_type'
  petsc_options_value = 'lu'
[]

[Outputs]
  perf_graph = true
  print_linear_residuals = true
  [./out]
    type = Exodus
  [../]
  [./csv]
    type = CSV
  [../]
[]

[Variables]
  [./Hphi_dielectric]
    block = 1
    order = SECOND
  [../]
  [./Hphi_vacuum]
    block = 0
    order = SECOND
  [../]
  [./Ez_dielectric]
    block = 1
    order = SECOND
  [../]
  [./Ez_vacuum]
    block = 0
    order = SECOND
  [../]
  [./Er_dielectric]
    block = 1
    order = SECOND
  [../]
  [./Er_vacuum]
    block = 0
    order = SECOND
  [../]
[]

[Kernels]
  [./Hphi_dielectric]
    type = TM0Cylindrical
    variable = Hphi_dielectric
    block = 1
  [../]
  [./Hphi_vacuum]
    type = TM0Cylindrical
    variable = Hphi_vacuum
    block = 0
  [../]
  [./Ez_dielectric_kern]
    type = TM0CylindricalEz
    variable = Ez_dielectric
    block = 1
    Hphi = Hphi_dielectric
  [../]
  [./Ez_vacuum_kern]
    type = TM0CylindricalEz
    variable = Ez_vacuum
    block = 0
    Hphi = Hphi_vacuum
  [../]
  [./Er_dielectric]
    type = TM0CylindricalEr
    variable = Er_dielectric
    Hphi = Hphi_dielectric
    block = 1
  [../]
  [./Er_vacuum]
    type = TM0CylindricalEr
    variable = Er_vacuum
    Hphi = Hphi_vacuum
    block = 0
  [../]
[]

[BCs]
  [./launcher]
    type = TM0AntennaVertBC
    boundary = Antenna
    variable = Hphi_vacuum
  [../]
  [./vert_wall]
    type = TM0PECVertBC
    variable = Hphi_vacuum
    boundary = vert_pec
  [../]
  [./axis]
    type = DirichletBC
    variable = Hphi_dielectric
    boundary = Axis
    value = 0
  [../]
  [./H_phi_interface]
    type = MatchedValueBC
    variable = Hphi_vacuum
    v = Hphi_dielectric
    boundary = interface
  [../]
  # [./Ez_interface]
  #   type = MatchedValueBC
  #   variable = Ez_dielectric
  #   v = Ez_vacuum
  #   boundary = interface
  # [../]
[]

[InterfaceKernels]
  [./Ez_continuous]
    type = HphiRadialInterface
    variable = Hphi_dielectric
    neighbor_var = Hphi_vacuum
    boundary = interface_dielectric
  [../]
[]


[Materials]
   [./dielectric]
     type = GenericConstantMaterial
     prop_names = 'eps_r'
     prop_values = '3.8'
     block = 1
   [../]
   [./vacuum]
     type = GenericConstantMaterial
     prop_names = 'eps_r'
     prop_values = '1'
     block = 0
   [../]
[]


# [AuxVariables]
#   [./Hphi_mag]
#   [../]
#   [./Er]
#     order = FIRST
#     family = MONOMIAL
#   [../]
#   # [./Electric_z]
#   #   order = FIRST
#   #   family = MONOMIAL
#   # [../]
# []

# [AuxKernels]
#   [./Hphi_mag]
#     type = AbsValueAux
#     u = Hphi
#     variable = Hphi_mag
#   [../]
#   [./Er_dielectric]
#     type = TM0CylindricalEr
#     Hphi = Hphi
#     variable = Er
#     block = 1
#     eps_r = 16
#   [../]
#   [./Er_vacuum]
#     type = TM0CylindricalEr
#     Hphi = Hphi
#     block = 0
#     eps_r = 1
#     variable = Er
#   [../]
#   # [./Electric_z_dielectric]
#   #   type = TM0CylindricalEz
#   #   Hphi = Hphi
#   #   variable = Electric_z
#   #   block = 1
#   #   eps_r = 16
#   # [../]
#   # [./Electric_z_vacuum]
#   #   type = TM0CylindricalEz
#   #   Hphi = Hphi
#   #   variable = Electric_z
#   #   block = 0
#   #   eps_r = 1
#   # [../]
# []

# [VectorPostprocessors]
#   [./line0]
#     type = LineValueSampler
#     start_point = '0 .045 0'
#     end_point = '.015 .045 0'
#     num_points = 1000
#     sort_by = x
#     variable = Hphi
#     outputs = csv
#   [../]
#   [./line1]
#     type = LineValueSampler
#     start_point = '0 .045 0'
#     end_point = '.015 .045 0'
#     num_points = 1000
#     sort_by = x
#     variable = Elec_z
#     outputs = csv
#   [../]
#   [./line2]
#     type = LineValueSampler
#     start_point = '0 .045 0'
#     end_point = '.015 .045 0'
#     num_points = 1000
#     sort_by = x
#     variable = Er
#     outputs = csv
#   [../]
# []
