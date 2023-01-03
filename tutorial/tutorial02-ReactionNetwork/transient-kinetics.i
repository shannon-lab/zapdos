#This tutorial is a sample reaction case based on
#Lieberman’s Figure 9.1, page 291.

[Mesh]
  #Sets up a 0D mesh with 1 element
  [geo]
    type = GeneratedMeshGenerator
    nx = 1
    dim = 1
  []
[]

#Defines the problem type, such as FE, eigen value problem, etc.
[Problem]
  type = FEProblem
[]

#User defined name for the variables.
#Other variable properties are defined here,
# such as family of shape function and variable order
# (the default family/order is Lagrange/First)
[Variables]
  [nA]
  []
  [nB]
  []
  [nC]
  []
[]

[Kernels]
  #Adds the time derivative for the variables
  [nA_time_derv]
    type = TimeDerivative
    variable = nA
  []
  [nB_time_derv]
    type = TimeDerivative
    variable = nB
  []
  [nC_time_derv]
    type = TimeDerivative
    variable = nC
  []
[]

#CRANE's Reactions Action that inputs the reactions as source terms for the variables
[Reactions]
  [Gas]
    #Name of each variable on the reactant side
    species = 'nA nB nC'
    #Define type of coefficient (rate or townsend)
    reaction_coefficient_format = 'rate'
    #Define if using log form
    use_log = false
    #Define if using automatic differentiation
    use_ad = true
    #Define which material block the reactions take place.
    # For undefine blocks, naming starts at 0
    block = 0
    #Define reactions and coefficients
    reactions = 'nA -> nB  : 1
                 nB -> nC  : 5'
  []
[]

#User defined name for the auxvariables.
#Other variable properties are defined here,
# such as family of shape function and variable order
[AuxVariables]
  #The auxvariable for the known solution for this diffusion problem
  [Solution_nA]
  []
  [Solution_nB]
  []
  [Solution_nC]
  []
[]

[AuxKernels]
  #The know solution for this diffusion problem
  [Solution_nA]
    type = FunctionAux
    variable = Solution_nA
    function = '1.0 * exp(-1.0*t)'
  []
  [Solution_nB]
    type = FunctionAux
    variable = Solution_nB
    function = '1.0 * 1.0 / (5. - 1.) * (exp(-1.0*t) - exp(-5.0*t))'
  []
  [Solution_nC]
    type = FunctionAux
    variable = Solution_nC
    function = '1.0 * (1.0 + 1.0 / (1. - 5.) * (5.*exp(-1.0*t) - 1.*exp(-5.0*t)))'
  []
[]

#Initial conditions for variables.
#If left undefine, the IC is zero
[ICs]
  [nA_ic]
    type = FunctionIC
    variable = nA
    function = '1.0'
  []
[]

#Preconditioning options
#Learn more at: https://mooseframework.inl.gov/syntax/Preconditioning/index.html
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

#How to execute the problem.
#Defines type of solve (such as steady or transient),
# solve type (Newton, PJFNK, etc.) and tolerances
[Executioner]
  type = Transient
  end_time = 3
  dt = 0.01
  dtmin = 1e-14
  scheme = bdf2
  solve_type = NEWTON

  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 1e-3'

  nl_rel_tol = 1e-08
  l_max_its = 20
[]

#Defines the output type of the file (multiple output files can be define per run)
[Outputs]
  perf_graph = true
  [out]
    type = Exodus
  []
[]
