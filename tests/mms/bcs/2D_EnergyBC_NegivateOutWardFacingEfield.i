#This MMS test was designed to test the log version of Zapdos'
#kernels with coupling between electrons, ions, potential, and
#the mean electron energy density.

#The mean electron energy density has a "correction" term that assumes
#an thermal conductivity coefficient of K=3/2*D_e*n_e (this is based on
#using the assumption of Einstein Relation)

#Note: The electron/mean energy's diffusion and mobility coefficients are
#directly proportional to the energy function.


[Mesh]
  [./geo]
    type = FileMeshGenerator
    file = '2D_EnergyBC_NegivateOutWardFacingEfield_IC_out.e'
    use_for_exodus_restart = true
  [../]
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [./em]
    initial_from_file_var = em
  [../]
  [./ion]
    initial_from_file_var = ion
  [../]
  [./mean_en]
    initial_from_file_var = mean_en
  [../]

  [./Ex]
    initial_from_file_var = Ex
  [../]
  [./Ey]
    initial_from_file_var = Ey
  [../]

  [./potential]
    initial_from_file_var = potential
  [../]
[]

[Kernels]
#Electron Equations
  [./em_time_derivative]
    type = TimeDerivativeLog
    variable = em
  [../]
  [./em_diffusion]
    type = CoeffDiffusion
    variable = em
    position_units = 1.0
  [../]
  [./em_source]
    type = BodyForce
    variable = em
    function = 'em_source'
  [../]

#Ion Equations
  [./ion_time_derivative]
    type = TimeDerivativeLog
    variable = ion
  [../]
  [./ion_diffusion]
    type = CoeffDiffusion
    variable = ion
    position_units = 1.0
  [../]
  [./ion_advection]
    type = EffectiveEFieldAdvection
    variable = ion
    u = Ex
    v = Ey
    position_units = 1.0
  [../]
  [./ion_source]
    type = BodyForce
    variable = ion
    function = 'ion_source'
  [../]


#Eff. Efield
  [./EffEfield_X_time_deriv]
    type = TimeDerivative
    variable = Ex
  [../]
  [./EffEfield_X_diffusion]
    type = MatDiffusion
    diffusivity = diffEx
    variable = Ex
  [../]
  [./EffEfield_X_source]
    type = BodyForce
    variable = Ex
    function = 'Ex_source'
  [../]
  [./EffEfield_Y_time_deriv]
    type = TimeDerivative
    variable = Ey
  [../]
  [./EffEfield_Y_diffusion]
    type = MatDiffusion
    diffusivity = diffEy
    variable = Ey
  [../]
  [./EffEfield_Y_source]
    type = BodyForce
    variable = Ey
    function = 'Ey_source'
  [../]

  #Potential
  [./Potential_time_deriv]
    type = TimeDerivative
    variable = potential
  [../]
  [./Potential_diffusion]
    type = MatDiffusion
    diffusivity = diffpotential
    variable = potential
  [../]
  [./Potential_source]
    type = BodyForce
    variable = potential
    function = 'potential_source'
  [../]

#Electron Energy Equations
  [./mean_en_time_deriv]
    type = TimeDerivativeLog
    variable = mean_en
  [../]
  [./mean_en_diffusion]
    type = CoeffDiffusion
    variable = mean_en
    position_units = 1.0
  [../]
  [./mean_en_advection]
    type = EFieldAdvection
    variable = mean_en
    potential = 'potential'
    position_units = 1.0
  [../]
  [./mean_en_source]
    type = BodyForce
    variable = mean_en
    function = 'energy_source'
  [../]
[]

[AuxVariables]
  [./mean_en_sol]
  [../]

  [./em_sol]
  [../]

  [./ion_sol]
  [../]

  [./Ex_sol]
  [../]
  [./Ey_sol]
  [../]

  [./potential_sol]
  [../]
[]

[AuxKernels]
  [./mean_en_sol]
    type = FunctionAux
    variable = mean_en_sol
    function = mean_en_fun
  [../]

  [./em_sol]
    type = FunctionAux
    variable = em_sol
    function = em_fun
  [../]

  [./ion_sol]
    type = FunctionAux
    variable = ion_sol
    function = ion_fun
  [../]

  [./Ex_sol]
    type = FunctionAux
    variable = Ex_sol
    function = Ex_fun
  [../]
  [./Ey_sol]
    type = FunctionAux
    variable = Ey_sol
    function = Ey_fun
  [../]

  [./potential_sol]
    type = FunctionAux
    variable = potential_sol
    function = potential_fun
  [../]
[]

[Functions]
#Material Variables
  [./massem]
    type = ConstantFunction
    value = 1.0
  [../]
  #Electron diffusion coeff.
  [./diffem]
    type = ConstantFunction
    value = 0.05
  [../]
  [./muem]
    type = ConstantFunction
    value = 0.01
  [../]
  #Electron energy mobility coeff.
  [./diffmean_en]
    type = ConstantFunction
    value = 0.05
  [../]
  [./mumean_en]
    type = ConstantFunction
    value = 0.01
  [../]
  #Ion diffusion coeff.
  [./diffion]
    type = ParsedFunction
    vars = diffmean_en
    vals = diffmean_en
    value = diffmean_en
  [../]
  [./muion]
    type = ParsedFunction
    vars = mumean_en
    vals = mumean_en
    value = mumean_en
  [../]
  [./N_A]
    type = ConstantFunction
    value = 1.0
  [../]
  [./ee]
    type = ConstantFunction
    value = 1.0
  [../]
  [./diffpotential]
    type = ConstantFunction
    value = 0.25
  [../]


#Manufactured Solutions
  #The manufactured electron density solution
  [./em_fun]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log(((16*ee*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)^3)/(3*massem*pi*((12*diffmean_en*pi)/5 +
                 (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^2)) / N_A)'
  [../]
  #The manufactured ion density solution
  [./ion_fun]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((sin(pi*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 1.0 + sin(pi*x)) / N_A)'
  [../]
  #The manufactured electron energy solution
  [./mean_en_fun]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log((sin(pi*y) + 0.2*sin(2*pi*t)*cos(pi*y) + 1.0 + sin(pi*x)) / N_A)'
  [../]
  #The manufactured eff. Efield solution
  [./Ex_fun]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'pi*cos(pi*x)*(sin(pi*t) + 1)'
  [../]
  [./Ey_fun]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'pi*cos(pi*y)*(sin(pi*t) + 1)'
  [../]
  #The manufactured potential solution
  [./potential_fun]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '-(sin(pi*t) + 1.0)*(sin(pi*y) + sin(pi*x))'
  [../]

#Source Terms in moles
  #The electron source term.
  [./em_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '((32*ee*cos(2*pi*t)*cos(pi*y)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 +
              1)^2)/(5*massem*((12*diffmean_en*pi)/5 + (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(x*pi) +
              sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^2) - diffem*((32*ee*(pi*cos(pi*y) -
              (pi*sin(2*pi*t)*sin(pi*y))/5)^2*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 +
              1))/(massem*pi*((12*diffmean_en*pi)/5 + (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(x*pi) +
              sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^2) - (16*ee*(pi^2*sin(pi*y) +
              (pi^2*cos(pi*y)*sin(2*pi*t))/5)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 +
              1)^2)/(massem*pi*((12*diffmean_en*pi)/5 + (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(x*pi) +
              sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^2) - (768*ee*mumean_en*(pi*cos(pi*y) -
              (pi*sin(2*pi*t)*sin(pi*y))/5)^2*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) +
              (cos(pi*y)*sin(2*pi*t))/5 + 1)^2)/(5*massem*((12*diffmean_en*pi)/5 + (12*mumean_en*pi*(sin(t*pi) +
              1)*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^3) + (128*ee*mumean_en*(pi^2*sin(pi*y) +
              (pi^2*cos(pi*y)*sin(2*pi*t))/5)*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 +
              1)^3)/(5*massem*((12*diffmean_en*pi)/5 + (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(x*pi) + sin(y*pi) +
              (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^3) + (4608*ee*mumean_en^2*pi*(pi*cos(pi*y) -
              (pi*sin(2*pi*t)*sin(pi*y))/5)^2*(sin(pi*t) + 1)^2*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 +
              1)^3)/(25*massem*((12*diffmean_en*pi)/5 + (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(x*pi) + sin(y*pi) +
              (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^4)) - diffem*((32*ee*pi*cos(pi*x)^2*(sin(pi*x) + sin(pi*y) +
              (cos(pi*y)*sin(2*pi*t))/5 + 1))/(massem*((12*diffmean_en*pi)/5 + (12*mumean_en*pi*(sin(t*pi) +
              1)*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^2) - (16*ee*pi*sin(pi*x)*(sin(pi*x) +
              sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)^2)/(massem*((12*diffmean_en*pi)/5 + (12*mumean_en*pi*(sin(t*pi) +
              1)*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^2) - (768*ee*mumean_en*pi^2*cos(pi*x)^2*(sin(pi*t) +
              1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)^2)/(5*massem*((12*diffmean_en*pi)/5 +
              (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^3) +
              (128*ee*mumean_en*pi^2*sin(pi*x)*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 +
              1)^3)/(5*massem*((12*diffmean_en*pi)/5 + (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(x*pi) + sin(y*pi) +
              (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^3) + (4608*ee*mumean_en^2*pi^3*cos(pi*x)^2*(sin(pi*t) + 1)^2*(sin(pi*x) +
              sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)^3)/(25*massem*((12*diffmean_en*pi)/5 +
              (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^4)) -
              (32*ee*((12*mumean_en*pi^2*cos(pi*t)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1))/5 +
              (24*mumean_en*pi^2*cos(2*pi*t)*cos(pi*y)*(sin(pi*t) + 1))/25)*(sin(pi*x) + sin(pi*y) +
              (cos(pi*y)*sin(2*pi*t))/5 + 1)^3)/(3*massem*pi*((12*diffmean_en*pi)/5 + (12*mumean_en*pi*(sin(t*pi) +
              1)*(sin(x*pi) + sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^3)) / N_A'
  [../]
  #The ion source term.
  [./ion_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '(diffion*pi^2*sin(pi*x) + (diffion*pi^2*(5*sin(pi*y) + cos(pi*y)*sin(2*pi*t)))/5 +
             (2*pi*cos(2*pi*t)*cos(pi*y))/5 - (muion*pi^2*(sin(pi*t) + 1)*(5*sin(pi*x) + 5*sin(pi*y) +
             10*sin(pi*x)*sin(pi*y) - 10*cos(pi*x)^2 - 10*cos(pi*y)^2 + cos(pi*y)*sin(2*pi*t)*sin(pi*x) +
             2*cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 10))/5) / N_A'
  [../]
  [./energy_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '(diffmean_en*pi^2*sin(pi*x) + (diffmean_en*pi^2*(5*sin(pi*y) + cos(pi*y)*sin(2*pi*t)))/5 +
             (2*pi*cos(2*pi*t)*cos(pi*y))/5 + (mumean_en*pi^2*(sin(pi*t) + 1)*(5*sin(pi*x) + 5*sin(pi*y) +
             10*sin(pi*x)*sin(pi*y) - 10*cos(pi*x)^2 - 10*cos(pi*y)^2 + cos(pi*y)*sin(2*pi*t)*sin(pi*x) +
             2*cos(pi*y)*sin(2*pi*t)*sin(pi*y) + 10))/5) / N_A'
  [../]

  #The Ex source term.
  [./Ex_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'pi^2*cos(pi*t)*cos(pi*x) + diffpotential*pi^3*cos(pi*x)*(sin(pi*t) + 1)'
  [../]
  [./Ey_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'pi^2*cos(pi*t)*cos(pi*y) + diffpotential*pi^3*cos(pi*y)*(sin(pi*t) + 1)'
  [../]

  [./potential_source]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '-pi*cos(pi*t)*(sin(pi*x) + sin(pi*y)) - diffpotential*pi^2*sin(pi*x)*(sin(pi*t) + 1) -
             diffpotential*pi^2*sin(pi*y)*(sin(pi*t) + 1)'
  [../]

  #The left BC dirichlet function
  [./em_left_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log(((16*ee*(sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)^3)/(3*massem*pi*((12*diffmean_en*pi)/5 +
                 (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^2)) / N_A)'
  [../]
  [./energy_left_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log((sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1) / N_A)'
  [../]
  [./ion_left_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log((sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1) / N_A)'
  [../]
  [./Ex_left_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'pi*(sin(pi*t) + 1)'
  [../]
  [./Ey_left_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'pi*cos(pi*y)*(sin(pi*t) + 1)'
  [../]
  [./potential_left_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '-sin(pi*y)*(sin(pi*t) + 1)'
  [../]

  #The right BC dirichlet function
  [./em_right_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log(((16*ee*(sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)^3)/(3*massem*pi*((12*diffmean_en*pi)/5 +
                 (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(y*pi) + (cos(y*pi)*sin(2*t*pi))/5 + 1))/5)^2)) / N_A)'
  [../]
  [./energy_right_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log((sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1) / N_A)'
  [../]
  [./ion_right_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log((sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1) / N_A)'
  [../]
  [./Ex_right_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '-pi*(sin(pi*t) + 1)'
  [../]
  [./Ey_right_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'pi*cos(pi*y)*(sin(pi*t) + 1)'
  [../]
  [./potential_right_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '-sin(pi*y)*(sin(pi*t) + 1)'
  [../]

  #The Down BC dirichlet function
  [./em_down_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log(((16*ee*(sin(2*pi*t)/5 + sin(pi*x) + 1)^3)/(3*massem*pi*((12*diffmean_en*pi)/5 +
                 (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(2*t*pi)/5 + sin(x*pi) + 1))/5)^2)) / N_A)'
  [../]
  [./energy_down_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log((sin(2*pi*t)/5 + sin(pi*x) + 1) / N_A)'
  [../]
  [./ion_down_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log((sin(2*pi*t)/5 + sin(pi*x) + 1) / N_A)'
  [../]
  [./Ex_down_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'pi*cos(pi*x)*(sin(pi*t) + 1)'
  [../]
  [./Ey_down_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'pi*(sin(pi*t) + 1)'
  [../]
  [./potential_down_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '-sin(pi*x)*(sin(pi*t) + 1)'
  [../]

  #The up BC dirichlet function
  [./em_up_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log(((16*ee*(sin(pi*x) - sin(2*pi*t)/5 + 1)^3)/(3*massem*pi*((12*diffmean_en*pi)/5 +
                 (12*mumean_en*pi*(sin(t*pi) + 1)*(sin(x*pi) - sin(2*t*pi)/5 + 1))/5)^2)) / N_A)'
  [../]
  [./energy_up_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log((sin(pi*x) - sin(2*pi*t)/5 + 1) / N_A)'
  [../]
  [./ion_up_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'log((sin(pi*x) - sin(2*pi*t)/5 + 1) / N_A)'
  [../]
  [./Ex_up_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = 'pi*cos(pi*x)*(sin(pi*t) + 1)'
  [../]
  [./Ey_up_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '-pi*(sin(pi*t) + 1)'
  [../]
  [./potential_up_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '-sin(pi*x)*(sin(pi*t) + 1)'
  [../]

  [./em_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = '4.0'
  [../]
  [./ion_ICs]
    type = ParsedFunction
    vars = 'N_A'
    vals = 'N_A'
    value = 'log((3.0 + sin(pi/2*x)) / N_A)'
  [../]
  [./mean_en_ICs]
    type = ParsedFunction
    vars = 'em_ICs'
    vals = 'em_ICs'
    value = '1.0'
  [../]

  [./em_left_Flux_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '(-diffmean_en*pi*cos(pi*x) - mumean_en*pi*cos(pi*x)*(sin(pi*t) + 1)*(sin(pi*x) +
              sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)) / N_A'
  [../]
  [./em_down_Flux_BC]
    type = ParsedFunction
    vars = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    vals = 'ee N_A diffpotential diffem muem massem diffmean_en mumean_en diffion muion'
    value = '(-(diffmean_en*pi*(5*cos(pi*y) - sin(2*pi*t)*sin(pi*y)))/5 -
              mumean_en*pi*cos(pi*y)*(sin(pi*t) + 1)*(sin(pi*x) + sin(pi*y) + (cos(pi*y)*sin(2*pi*t))/5 + 1)) / N_A'
  [../]
[]

[BCs]
  [./em_left_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_left_BC'
    boundary = 3
    preset = true
  [../]
  [./em_right_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_right_BC'
    boundary = 1
    preset = true
  [../]
  [./em_down_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_down_BC'
    boundary = 0
    preset = true
  [../]
  [./em_up_BC]
    type = FunctionDirichletBC
    variable = em
    function = 'em_up_BC'
    boundary = 2
    preset = true
  [../]

  [./ion_left_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_left_BC'
    boundary = 3
    preset = true
  [../]
  [./ion_right_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_right_BC'
    boundary = 1
    preset = true
  [../]
  [./ion_down_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_down_BC'
    boundary = 0
    preset = true
  [../]
  [./ion_up_BC]
    type = FunctionDirichletBC
    variable = ion
    function = 'ion_up_BC'
    boundary = 2
    preset = true
  [../]

  #[./energy_left_BC]
  #  type = FunctionDirichletBC
  #  variable = mean_en
  #  function = 'energy_left_BC'
  #  boundary = 3
  #  preset = true
  #[../]
  [./energy_left_physical_diffusion]
    type = SakiyamaEnergyDiffusionBC
    variable = mean_en
    em = em
    boundary = 3
    position_units = 1.0
  [../]
  [./energy_left_second_emissions]
    type = SakiyamaEnergySecondaryElectronWithEffEfieldBC
    variable = mean_en
    em = em
    ip = ion
    Ex = Ex
    Ey = Ey
    potential = potential
    Tse_equal_Te = false
    user_se_energy = 1.0
    se_coeff = 1.0
    boundary = 3
    position_units = 1.0
  [../]

  [./energy_right_BC]
    type = FunctionDirichletBC
    variable = mean_en
    function = 'energy_right_BC'
    boundary = 1
    preset = true
  [../]

  #[./energy_down_BC]
  #  type = FunctionDirichletBC
  #  variable = mean_en
  #  function = 'energy_down_BC'
  #  boundary = 0
  #  preset = true
  #[../]
  [./energy_down_physical_diffusion]
    type = SakiyamaEnergyDiffusionBC
    variable = mean_en
    em = em
    boundary = 0
    position_units = 1.0
  [../]
  [./energy_down_second_emissions]
    type = SakiyamaEnergySecondaryElectronWithEffEfieldBC
    variable = mean_en
    em = em
    ip = ion
    Ex = Ex
    Ey = Ey
    potential = potential
    Tse_equal_Te = false
    user_se_energy = 1.0
    se_coeff = 1.0
    boundary = 0
    position_units = 1.0
  [../]

  [./energy_up_BC]
    type = FunctionDirichletBC
    variable = mean_en
    function = 'energy_up_BC'
    boundary = 2
    preset = true
  [../]

  [./Ex_left_BC]
    type = FunctionDirichletBC
    variable = Ex
    function = 'Ex_left_BC'
    boundary = 3
    preset = true
  [../]
  [./Ex_right_BC]
    type = FunctionDirichletBC
    variable = Ex
    function = 'Ex_right_BC'
    boundary = 1
    preset = true
  [../]
  [./Ex_down_BC]
    type = FunctionDirichletBC
    variable = Ex
    function = 'Ex_down_BC'
    boundary = 0
    preset = true
  [../]
  [./Ex_up_BC]
    type = FunctionDirichletBC
    variable = Ex
    function = 'Ex_up_BC'
    boundary = 2
    preset = true
  [../]

  [./Ey_left_BC]
    type = FunctionDirichletBC
    variable = Ey
    function = 'Ey_left_BC'
    boundary = 3
    preset = true
  [../]
  [./Ey_right_BC]
    type = FunctionDirichletBC
    variable = Ey
    function = 'Ey_right_BC'
    boundary = 1
    preset = true
  [../]
  [./Ey_down_BC]
    type = FunctionDirichletBC
    variable = Ey
    function = 'Ey_down_BC'
    boundary = 0
    preset = true
  [../]
  [./Ey_up_BC]
    type = FunctionDirichletBC
    variable = Ey
    function = 'Ey_up_BC'
    boundary = 2
    preset = true
  [../]

  [./potential_left_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_left_BC'
    boundary = 3
    preset = true
  [../]
  [./potential_right_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_right_BC'
    boundary = 1
    preset = true
  [../]
  [./potential_down_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_down_BC'
    boundary = 0
    preset = true
  [../]
  [./potential_up_BC]
    type = FunctionDirichletBC
    variable = potential
    function = 'potential_up_BC'
    boundary = 2
    preset = true
  [../]
[]

[Materials]
  [./Material_Coeff]
    type = GenericFunctionMaterial
    prop_names =  'e  N_A  massem diffpotential  diffEx         diffEy'
    prop_values = 'ee N_A  massem diffpotential  diffpotential  diffpotential '
  [../]
  [./ADMaterial_Coeff_Set1]
    type = ADGenericFunctionMaterial
    prop_names =  'diffion  muion  diffem  muem  diffmean_en mumean_en'
    prop_values = 'diffion  muion  diffem  muem  diffmean_en mumean_en'
  [../]
  [./Charge_Signs]
    type = GenericConstantMaterial
    prop_names =  'sgnem  sgnion  sgnmean_en'
    prop_values = '-1.0   1.0     -1.0'
  [../]
[]

[Postprocessors]
  [./em_l2Error]
    type = ElementL2Error
    variable = em
    function = em_fun
  [../]
  [./ion_l2Error]
    type = ElementL2Error
    variable = ion
    function = ion_fun
  [../]
  [./mean_en_l2Error]
    type = ElementL2Error
    variable = mean_en
    function = mean_en_fun
  [../]

  [./Ex_l2Error]
    type = ElementL2Error
    variable = Ex
    function = Ex_fun
  [../]
  [./Ey_l2Error]
    type = ElementL2Error
    variable = Ey
    function = Ey_fun
  [../]

  [./potential_l2Error]
    type = ElementL2Error
    variable = potential
    function = potential_fun
  [../]

  [./h]
    type = AverageElementSize
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
  [./out]
    type = Exodus
    interval = 10
  []
[]
