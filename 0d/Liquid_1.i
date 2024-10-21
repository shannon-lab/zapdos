[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 1
[]

[Variables]
  [ONOOH]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [ONOOn]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [N2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [N2g]
    family = SCALAR
    order = FIRST
    initial_condition = 1.93e19
  []

  [N2O]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [N2Og]
    family = SCALAR
    order = FIRST
    initial_condition = 8.23e14
  []

  [N2O3]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [N2O3g]
    family = SCALAR
    order = FIRST
    initial_condition = 5.81e9
  []

  [N2O4]
    family = SCALAR
    order = FIRST
    initial_condition = 1.8e9
  []

  [N2O4g]
    family = SCALAR
    order = FIRST
    initial_condition = 2.53e14
  []

  [N2O5]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [N2O5g]
    family = SCALAR
    order = FIRST
    initial_condition = 2.53e14
  []

  [NO]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [NOg]
    family = SCALAR
    order = FIRST
    initial_condition = 3.69e11
  []

  [HNO]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [NO2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [NO2g]
    family = SCALAR
    order = FIRST
    initial_condition = 3e15
  []

  [NO2n]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [NO2ng]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [HNO2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [NO3]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [NO3g]
    family = SCALAR
    order = FIRST
    initial_condition = 5.57e14
  []

  [NO3n]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [HNO3]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [HNO3g]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [H2O]
    family = SCALAR
    order = FIRST
    initial_condition = 3.337e19
  []

  [H2Op]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  []

  [H2On]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  []

  [H3Op]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [OH]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [OHn]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [H]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [Hp]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [H2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [H2O2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [HO2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [O]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [Og]
    family = SCALAR
    order = FIRST
    initial_condition = 5.75e10
  []

  [On]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [Op]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [O2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [O2g]
    family = SCALAR
    order = FIRST
    initial_condition = 5.5e18
  []

  [O2n]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [O3]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []

  [O3g]
    family = SCALAR
    order = FIRST
    initial_condition = 3.96e16
  []

  [O3n]
    family = SCALAR
    order = FIRST
    initial_condition = 1e3
  []
[]

[ScalarKernels]
  [dONOOH_dt]
    type = ODETimeDerivative
    variable = ONOOH
  []
  [dONOOn_dt]
    type = ODETimeDerivative
    variable = ONOOn
  []

  [dN2_dt]
    type = ODETimeDerivative
    variable = N2
  []

  [dN2g_dt]
    type = ODETimeDerivative
    variable = N2g
  []

  [dN2O_dt]
    type = ODETimeDerivative
    variable = N2O
  []

  [dN2Og_dt]
    type = ODETimeDerivative
    variable = N2Og
  []

  [dN2O3_dt]
    type = ODETimeDerivative
    variable = N2O3
  []

  [dN2O3g_dt]
    type = ODETimeDerivative
    variable = N2O3g
  []

  [dN2O4_dt]
    type = ODETimeDerivative
    variable = N2O4
  []

  [dN2O4g_dt]
    type = ODETimeDerivative
    variable = N2O4g
  []

  [dN2O5_dt]
    type = ODETimeDerivative
    variable = N2O5
  []

  [dN2O5g_dt]
    type = ODETimeDerivative
    variable = N2O5g
  []

  [dNO_dt]
    type = ODETimeDerivative
    variable = NO
  []

  [dNOg_dt]
    type = ODETimeDerivative
    variable = NOg
  []

  [dHNO_dt]
    type = ODETimeDerivative
    variable = HNO
  []

  [dNO2_dt]
    type = ODETimeDerivative
    variable = NO2
  []

  [dNO2g_dt]
    type = ODETimeDerivative
    variable = NO2g
  []

  [dNO2n_dt]
    type = ODETimeDerivative
    variable = NO2n
  []

  [dNO2ng_dt]
    type = ODETimeDerivative
    variable = NO2ng
  []

  [dHNO2_dt]
    type = ODETimeDerivative
    variable = HNO2
  []

  [dNO3_dt]
    type = ODETimeDerivative
    variable = NO3
  []

  [dNO3g_dt]
    type = ODETimeDerivative
    variable = NO3g
  []

  [dNO3n_dt]
    type = ODETimeDerivative
    variable = NO3n
  []

  [dHNO3_dt]
    type = ODETimeDerivative
    variable = HNO3
  []

  [dHNO3g_dt]
    type = ODETimeDerivative
    variable = HNO3g
  []

  [dH2O_dt]
    type = ODETimeDerivative
    variable = H2O
  []

  [dH2Op_dt]
    type = ODETimeDerivative
    variable = H2Op
  []

  [dH2On_dt]
    type = ODETimeDerivative
    variable = H2On
  []

  [dH3Op_dt]
    type = ODETimeDerivative
    variable = H3Op
  []

  [dOH_dt]
    type = ODETimeDerivative
    variable = OH
  []

  [dOHn_dt]
    type = ODETimeDerivative
    variable = OHn
  []

  [dH_dt]
    type = ODETimeDerivative
    variable = H
  []

  [dHp_dt]
    type = ODETimeDerivative
    variable = Hp
  []

  [dH2_dt]
    type = ODETimeDerivative
    variable = H2
  []

  [dH2O2_dt]
    type = ODETimeDerivative
    variable = H2O2
  []

  [dHO2_dt]
    type = ODETimeDerivative
    variable = HO2
  []

  [dO_dt]
    type = ODETimeDerivative
    variable = O
  []

  [dOg_dt]
    type = ODETimeDerivative
    variable = Og
  []

  [dOn_dt]
    type = ODETimeDerivative
    variable = On
  []

  [dOp_dt]
    type = ODETimeDerivative
    variable = Op
  []

  [dO2_dt]
    type = ODETimeDerivative
    variable = O2
  []

  [dO3_dt]
    type = ODETimeDerivative
    variable = O3
  []

  [dO2g_dt]
    type = ODETimeDerivative
    variable = O2g
  []

  [dO3g_dt]
    type = ODETimeDerivative
    variable = O3g
  []

  [dO2n_dt]
    type = ODETimeDerivative
    variable = O2n
  []

  [dO3n_dt]
    type = ODETimeDerivative
    variable = O3n
  []
[]

[GlobalReactions]
  [Air]
    species = 'ONOOH ONOOn N2 N2g N2O N2Og N2O5 N2O5g N2O3 N2O3g N2O4 N2O4g NO NOg HNO NO2 NO2g NO2n NO2ng HNO2 NO3 NO3g NO3n HNO3 HNO3g H2O H2Op H2On H3Op
    OH OHn H Hp H2O2 HO2 H2 O Og Op On O2 O2g O2n O3 O3n O3g'
    num_particles = '2 4'
    file_location = 'data'
    aux_species = 'M'

    # These are parameters required equation-based rate coefficients
    equation_constants = 'Tg pi kb d'
    equation_values = '300 3.141 8.6173e-5 0.25'
    equation_variables = 't N2h N2rev N2 N2g N2Oh N2Orev N2O N2Og N2O3h N2O3rev N2O3 N2O3g N2O4h N2O4rev N2O4 N2O4g N2O5h N2O5rev N2O5 N2O5g NOh NOrev NO NOg NO2h NO2rev NO2 NO2g
    NO2nh NO2nrev NO2n NO2ng NO3h NO3rev NO3g NO3 HNO3g HNO3 HNO3h HNO3rev Oh Orev O Og O2h O2rev O2 O2g O3h O3rev O3 O3g'
    include_electrons = false
    track_rates = true

    reactions = '
    N2g -> N2                                                   : {if(N2/N2g<0.016,(N2h*1.9e-5)/((d/pi)^2*200),0)}
    N2g ->                                                      : {if(N2/N2g<0.016,(N2h*1.9e-5)/((d/pi)^2),0)}
    N2 -> N2g                                                   : {if(N2/N2g>0.016,(N2rev*1.9e-5)/((d/pi)^2),0)}
    N2 ->                                                       : {if(N2/N2g>0.016,(N2rev*1.9e-5)/((d/pi)^2*200),0)}
    N2Og -> N2O                                                 : {if(N2O/N2Og<0.6,(N2Oh*1.9e-5)/((d/pi)^2*200),0)}
    N2Og ->                                                     : {if(N2O/N2Og<0.6,(N2Oh*1.9e-5)/((d/pi)^2),0)}
    N2O -> N2Og                                                 : {if(N2O/N2Og>0.6,(N2Orev*1.9e-5)/((d/pi)^2),0)}
    N2O ->                                                      : {if(N2O/N2Og>0.6,(N2Orev*1.9e-5)/((d/pi)^2*200),0)}
    N2O3g -> N2O3                                               : {if(N2O3/N2O3g<600,(N2O3h*1.9e-5)/((d/pi)^2*200),0)}
    N2O3g ->                                                    : {if(N2O3/N2O3g<600,(N2O3h*1.9e-5)/((d/pi)^2),0)}
    N2O3 -> N2O3g                                               : {if(N2O3/N2O3g>600,(N2O3rev*1.9e-5)/((d/pi)^2),0)}
    N2O3 ->                                                     : {if(N2O3/N2O3g>600,(N2O3rev*1.9e-5)/((d/pi)^2*200),0)}
    N2O4g -> N2O4                                               : {if(N2O4/N2O4g<36.9,(N2O4h*1.9e-5)/((d/pi)^2*200),0)}
    N2O4g ->                                                    : {if(N2O4/N2O4g<36.9,(N2O4h*1.9e-5)/((d/pi)^2),0)}
    N2O4 -> N2O4g                                               : {if(N2O4/N2O4g>36.9,(N2O4rev*1.9e-5)/((d/pi)^2),0)}
    N2O4 ->                                                     : {if(N2O4/N2O4g>36.9,(N2O4rev*1.9e-5)/((d/pi)^2*200),0)}
    N2O5g -> N2O5                                               : {if(N2O5/N2O5g<48.5,(N2O5h*1.9e-5)/((d/pi)^2*200),0)}
    N2O5g ->                                                    : {if(N2O5/N2O5g<48.5,(N2O5h*1.9e-5)/((d/pi)^2),0)}
    N2O5 -> N2O5g                                               : {if(N2O5/N2O5g>48.5,(N2O5rev*1.9e-5)/((d/pi)^2),0)}
    N2O5 ->                                                     : {if(N2O5/N2O5g>48.5,(N2O5rev*1.9e-5)/((d/pi)^2*200),0)}
    Og -> O                                                     : {if(O/Og<1,(Oh*1.9e-5)/((d/pi)^2*200),0)}
    Og ->                                                       : {if(O/Og<1,(Oh*1.9e-5)/((d/pi)^2),0)}
    O -> Og                                                     : {if(O/Og>1,(Orev*1.9e-5)/((d/pi)^2),0)}
    O ->                                                        : {if(O/Og>1,(Orev*1.9e-5)/((d/pi)^2*200),0)}
    O2g -> O2                                                   : {if(O2/O2g<0.0324,(O2h*1.9e-5)/((d/pi)^2*200),0)}
    O2g ->                                                      : {if(O2/O2g<0.0324,(O2h*1.9e-5)/((d/pi)^2),0)}
    O2 -> O2g                                                   : {if(O2/O2g>0.0324,(O2rev*1.9e-5)/((d/pi)^2),0)}
    O2 ->                                                       : {if(O2/O2g>0.0324,(O2rev*1.9e-5)/((d/pi)^2*200),0)}
    O3g -> O3                                                   : {if(O3/O3g<0.3,(O3h*1.9e-5)/((d/pi)^2*200),0)}
    O3g ->                                                      : {if(O3/O3g<0.3,(O3h*1.9e-5)/((d/pi)^2),0)}
    O3 -> O3g                                                   : {if(O3/O3g>0.3,(O3rev*1.9e-5)/((d/pi)^2),0)}
    O3 ->                                                       : {if(O3/O3g>0.3,(O3rev*1.9e-5)/((d/pi)^2*200),0)}
    NOg -> NO                                                   : {if(NO/NOg<0.044,(NOh*1.9e-5)/((d/pi)^2*200),0)}
    NOg ->                                                      : {if(NO/NOg<0.044,(NOh*1.9e-5)/((d/pi)^2),0)}
    NO -> NOg                                                   : {if(NO/NOg>0.044,(NOrev*1.9e-5)/((d/pi)^2),0)}
    NO ->                                                       : {if(NO/NOg>0.044,(NOrev*1.9e-5)/((d/pi)^2*200),0)}
    NO2g -> NO2                                                 : {if(NO2/NO2g<0.28,(NO2h*1.9e-5)/((d/pi)^2*200),0)}
    NO2g ->                                                     : {if(NO2/NO2g<0.28,(NO2h*1.9e-5)/((d/pi)^2),0)}
    NO2 -> NO2g                                                 : {if(NO2/NO2g>0.28,(NO2rev*1.9e-5)/((d/pi)^2),0)}
    NO2 ->                                                      : {if(NO2/NO2g>0.28,(NO2rev*1.9e-5)/((d/pi)^2*200),0)}
    NO2ng -> NO2n                                               : {if(NO2n/NO2ng<0.28,(NO2nh*1.9e-5)/((d/pi)^2*200),0)}
    NO2ng ->                                                    : {if(NO2n/NO2ng<0.28,(NO2nh*1.9e-5)/((d/pi)^2),0)}
    NO2n -> NO2ng                                               : {if(NO2n/NO2ng>0.28,(NO2nrev*1.9e-5)/((d/pi)^2),0)}
    NO2n ->                                                     : {if(NO2n/NO2ng>0.28,(NO2nrev*1.9e-5)/((d/pi)^2*200),0)}
    NO3g -> NO3                                                 : {if(NO3/NO3g<41.5,(NO3h*1.9e-5)/((d/pi)^2*200),0)}
    NO3g ->                                                     : {if(NO3/NO3g<41.5,(NO3h*1.9e-5)/((d/pi)^2),0)}
    NO3 -> NO3g                                                 : {if(NO3/NO3g>41.5,(NO3rev*1.9e-5)/((d/pi)^2),0)}
    NO3 ->                                                      : {if(NO3/NO3g>41.5,(NO3rev*1.9e-5)/((d/pi)^2*200),0)}
    HNO3g -> HNO3                                               : {if(HNO3/HNO3g<4.8e6,(HNO3h*1.9e-5)/((d/pi)^2*200),0)}
    HNO3g ->                                                    : {if(HNO3/HNO3g<4.8e6,(HNO3h*1.9e-5)/((d/pi)^2),0)}
    HNO3 -> HNO3g                                               : {if(HNO3/HNO3g>4.8e6,(HNO3rev*1.9e-5)/((d/pi)^2),0)}
    HNO3 ->                                                     : {if(HNO3/HNO3g>4.8e6,(HNO3rev*1.9e-5)/((d/pi)^2*200),0)}
    H2O -> OH + H                                               : 1e-20
    OH + OH -> H2O2                                             : 1.7e-11
    OH + H -> H2O                                               : 3e-11
    H + H -> H2                                                 : 1.5e-11
    NO3 + H2O -> HNO3 + OH                                      : 4.8e-14
    HNO3 + OH -> NO3 + H2O                                      : 2.17e-13
    OH + NO2 -> HNO3                                            : 2e-11
    N2O5 + H2O -> HNO3 + HNO3                                   : 2e-21
    HNO3 + H2O -> H3Op + NO3n                                   : 3e-18
    H3Op + NO3n -> HNO3 + H2O                                   : 7e-16
    NO2 + H -> HNO2                                             : 1.67e-11
    NO + NO2 + H2O -> HNO2 + HNO2                               : 5.5e-34
    OH + NO -> HNO2                                             : 3.3e-11
    H + HNO2 -> NO + H2O                                        : 7.5e-13
    O + H2O -> OH + OH                                          : 2.2e-17
    O + O2 -> O3                                                : 5e-12
    O3 -> O + O2                                                : 3e-6
    NO + NO + O2 -> NO2 + NO2                                   : 6.28e-36
    O2g + NO3g -> NO2g + O3g                                    : 1e-17
    O3g + NO2g -> NO3g + O2g                                    : {1e-13 * exp(-2470/Tg)}
    NOg + NO3g -> NO2g + NO2g                                   : {1.8e-11 * exp(110/Tg)}
    NO2g + NO3g + O2g -> N2O5g + O2g                            : {2.8e-30 * (300/Tg)^3.5}
    NO2g + NO3g + O3g -> N2O5g + O3g                            : {6e-30 * (300/Tg)^3.5}
    NO3g + NO3g -> NO2g + NO2g + O2g                            : {5e-12 * exp(-3000/Tg)}
    O3g + NO3g -> NO2g + O2g + O2g                              : 1e-17
    NOg + NO3g -> NOg + NOg + O2g                               : {7.3e-12 * (300/Tg)^0.23 * exp(-947/Tg)}
    NO2g + NO3g -> NO2g + NOg + O2g                             : {4.5e-14 * exp(-1260/Tg)}
    O3g + O3g -> O2g + O2g + O2g                                : {7.47e-12 * exp(-9310/Tg)}
    N2O5g + M -> NO2g + NO3g + M                                : {1.33e-3 * (300/Tg)^3.5 * exp(-11000/Tg)}
    NO2n + N2O -> NO3n + N2                                     : 5e-13
    NO2g + NO3g + N2g -> N2O5g + N2g                            : {2.8e-30 * (300/Tg)^3.5}
    Hp + H2O -> H3Op                                            : 5e-15
    ONOOH + H2O -> H3Op + ONOOn                                 : 5e-15
    ONOOn + H3Op -> H2O + ONOOH                                 : 1.75e-6
    N2O5 + H2O -> ONOOH + ONOOH                                 : 2e-21
    NO2 + OH -> ONOOH                                           : 2e-11
    H2O2 + NO2n + H3Op -> ONOOH + H2O + H2O                     : 3.04e-39
    ONOOH + H2O -> OH + NO2 + H2O                               : 1.24e-23
    H2Op + H2O -> H3Op + OH                                     : 1e-17
    HNO + OH -> H2O + NO                                        : 8e-11
    OH + N2O -> HNO + NO                                        : 3.8e-17
    H2On + H2Op -> H + OH + H2O                                 : 1e-9
    H + H2O -> H2 + OH                                          : 1.5e-21
    H + H2O2 -> OH + H2O                                        : 1.5e-13
    H + H2O2 -> H + OH + H2O                                    : 1e-14
    Og + Og + Og -> O2g + Og                                    : {4.0e-33 * (300/Tg)^0.41 * 3.6}
    Og + O3g -> O2g + O2g                                       : {8e-12 * exp(-2060/Tg)}
    Og + O2g + NOg -> O2g + NO2g                                : {1e-31 * (300/Tg)^1.6}
    Og + N2O5g -> N2g + O2g + O2g + O2g                         : {3e-16 * (300/Tg)^-0.5}
    Og + O3g + NOg -> O3g + NO2g                                : {2e-31 * (300/Tg)^1.6}
    Og + O3g + NO2g -> O3g + NO3g                               : {2e-31 * (300/Tg)^2}
    Og + NO2g -> NOg + O2g                                      : {6.5e-12*exp(120/Tg)}
    Og + NO3g -> O2g + NO2g                                     : 1.7e-11
    O3g + N2g -> Og + O2g + N2g                                 : {7.3e-10 * exp(-11400/Tg)}
    O2g + O3g -> Og + O2g + O2g                                 : {7.3e-10 * exp(-11400/Tg)}
    O3g + O3g -> Og + O2g + O3g                                 : {1.4e-9 * exp(-11400/Tg)}
    Og + Og + M -> O2g + M                                      : {3.2e-35 * exp(900/Tg)}
    Og + O2g + M -> O3g + M                                     : {3.4e-34 * (300/Tg)^1.2}
    Og + NOg + M -> NO2g + M                                    : {1e-31 * (300/Tg)^1.6}
    Og + NO2g + M -> NO3g + M                                   : {9e-32 * (300/Tg)^2}
    On + H2O -> OHn + OH                                        : 3e-15
    HO2 + H2O -> H3Op + O2n                                     : 1.43e-17
    H3Op + O2n -> HO2 + H2O                                     : 5e-11
    H3Op + NO2n -> H + HO2 + H2O                                : 6.81e-10
    H2On + H -> H2 + OHn                                        : 4e-11
    H2On + O -> On + H2O                                        : 3e-11
    H2On + O2 -> O2n + H2O                                      : 3e-11
    H2On + OH -> OHn + H2O                                      : 5e-11
    H2On + H2O2 -> OH + OHn + H2O                               : 2e-11
    H2On + On -> OHn + OHn                                      : 2e-11
    H2On + H2On -> H2 + OHn + OHn                               : 1e-11
    H3Op + OHn -> H + OH + H2O                                  : 1e-10
    OH + HO2 -> O2 + H2O                                        : 2e-11
    OH + H2O2 -> HO2 + H2O                                      : 1e-13
    OH + OHn -> On + H2O                                        : 8e-12
    OH + O2n -> O2 + OHn                                        : 1.5e-11
    NO + O2n -> ONOOn                                           : 7.14e-12
    HNO + O2 -> OH2 + NO                                        : 8.01e-21
    NO + HO2 -> ONOOH                                           : 5.33e-12
    NO + HO2 -> HNO3                                            : 5.33e-12
    H + HO2 -> H2O2                                             : 3e-11
    O2 + H -> HO2                                               : 5e-11
    O3n + OH -> O2n + HO2                                       : 1.41e-11
    O2n + HO2 + H2O -> O2 + H2O2 + OHn                          : 2.68e-34
    O3 + OHn -> O2n + HO2                                       : 1.16e-19
    HNO2 + H2O -> H3Op + NO2                                    : 5e-15
    NOg + NO2g -> N2O3g                                         : {7.9e-12 * (300/Tg)^-1.4}
    N2O3g + M -> NOg + NO2g + M                                 : {1.91e-7 * (300/Tg)^8.7 * exp(-4882/Tg)}
    NOg + NO2g + N2g -> N2O3g + N2g                             : {3.1e-34 *(300/Tg)^7.7}
    NOg + NO2g + O2g -> N2O3g + O2g                             : {3.1e-34 *(300/Tg)^7.7}
    NOg + NO2g + O3g -> N2O3g + O3g                             : {6.1e-34 *(300/Tg)^7.7}
    NO2g + NO2g + N2g -> N2O4g + N2g                            : {1.4e-33 * (300/Tg)^3.8}
    NO2g + NO2g + O2g -> N2O4g + O2g                            : {1.4e-33 * (300/Tg)^3.8}
    N2O4g + M -> NO2g + NO2g + M                                : {1.3e-5 * (300/Tg)^3.5 * exp(-6403/Tg)}
    NO2g + NO2g + O3g -> N2O4g + O3g                            : {3e-33 * (300/Tg)^3.8}
    N2O3 + H2O -> HNO2 + HNO2                                   : 1.93e-17
    N2O4 + H2O -> HNO2 + HNO3                                   : 1.33e-18
    '
    
    #NO2 + NO2 + H2O + H2O + H2O -> H3Op + H3Op + NO3n + NO2n    : 1.3e-79
    #NO2 + NO2 + H2O + H2O -> H3Op + NO3n + HNO2                 : 1.2e-56
    #
  []
[]

[AuxVariables]
  [Tg]
    order = FIRST
    family = SCALAR
    initial_condition = 300
  []
  
  [t]
    order = FIRST
    family = SCALAR
  []

  [N2h]
    order = FIRST
    family = SCALAR
  []

  [N2rev]
    order = FIRST
    family = SCALAR
  []

  [N2Oh]
    order = FIRST
    family = SCALAR
  []

  [N2Orev]
    order = FIRST
    family = SCALAR
  []

  [N2O3h]
    order = FIRST
    family = SCALAR
  []

  [N2O3rev]
    order = FIRST
    family = SCALAR
  []

  [N2O4h]
    order = FIRST
    family = SCALAR
  []

  [N2O4rev]
    order = FIRST
    family = SCALAR
  []

  [N2O5h]
    order = FIRST
    family = SCALAR
  []

  [N2O5rev]
    order = FIRST
    family = SCALAR
  []

  [NOh]
    order = FIRST
    family = SCALAR
  []

  [NOrev]
    order = FIRST
    family = SCALAR
  []

  [NO2h]
    order = FIRST
    family = SCALAR
  []

  [NO2rev]
    order = FIRST
    family = SCALAR
  []

  [NO2nh]
    order = FIRST
    family = SCALAR
  []

  [NO2nrev]
    order = FIRST
    family = SCALAR
  []

  [NO3h]
    order = FIRST
    family = SCALAR
  []

  [NO3rev]
    order = FIRST
    family = SCALAR
  []

  [HNO3h]
    order = FIRST
    family = SCALAR
  []

  [HNO3rev]
    order = FIRST
    family = SCALAR
  []

  [Oh]
    order = FIRST
    family = SCALAR
  []

  [Orev]
    order = FIRST
    family = SCALAR
  []

  [O2h]
    order = FIRST
    family = SCALAR
  []

  [O2rev]
    order = FIRST
    family = SCALAR
  []

  [O3h]
    order = FIRST
    family = SCALAR
  []

  [O3rev]
    order = FIRST
    family = SCALAR
  []
  
  [M]
    order = FIRST
    family = SCALAR
  []
[]

[Functions]
  [tf]
    type = ParsedFunction
    expression = 't'
  []

  [N2h_func]
    type = ParsedFunction
    symbol_names = 'N2g N2'
    symbol_values = 'N2g N2'
    expression = '(((0.016*N2g)-N2)/(0.016*N2g))'
  []

  [N2h_rev_func]
    type = ParsedFunction
    symbol_names = 'N2g N2'
    symbol_values = 'N2g N2'
    expression = '(N2-0.016*N2g)'
  []

  [N2Oh_func]
    type = ParsedFunction
    symbol_names = 'N2Og N2O'
    symbol_values = 'N2Og N2O'
    expression = '(((0.6*N2Og)-N2O)/(0.6*N2Og))'
  []

  [N2Oh_rev_func]
    type = ParsedFunction
    symbol_names = 'N2Og N2O'
    symbol_values = 'N2Og N2O'
    expression = '(N2O-0.6*N2Og)'
  []

  [N2O3h_func]
    type = ParsedFunction
    symbol_names = 'N2O3g N2O3'
    symbol_values = 'N2O3g N2O3'
    expression = '(((600*N2O3g)-N2O3)/(600*N2O3g))'
  []

  [N2O3h_rev_func]
    type = ParsedFunction
    symbol_names = 'N2O3g N2O3'
    symbol_values = 'N2O3g N2O3'
    expression = '(N2O3-600*N2O3g)'
  []

  [N2O4h_func]
    type = ParsedFunction
    symbol_names = 'N2O4g N2O4'
    symbol_values = 'N2O4g N2O4'
    expression = '(((36.9*N2O4g)-N2O4)/(36.9*N2O4g))'
  []

  [N2O4h_rev_func]
    type = ParsedFunction
    symbol_names = 'N2O4g N2O4'
    symbol_values = 'N2O4g N2O4'
    expression = '(N2O4-36.9*N2O4g)'
  []

  [N2O5h_func]
    type = ParsedFunction
    symbol_names = 'N2O5g N2O5'
    symbol_values = 'N2O5g N2O5'
    expression = '(((48.5*N2O5g)-N2O5)/(48.5*N2O5g))'
  []

  [N2O5h_rev_func]
    type = ParsedFunction
    symbol_names = 'N2O5g N2O5'
    symbol_values = 'N2O5g N2O5'
    expression = '(N2O5-48.5*N2O5g)'
  []

  [NOh_func]
    type = ParsedFunction
    symbol_names = 'NOg NO'
    symbol_values = 'NOg NO'
    expression = '(((0.044*NOg)-NO)/(0.044*NOg))'
  []

  [NOh_rev_func]
    type = ParsedFunction
    symbol_names = 'NOg NO'
    symbol_values = 'NOg NO'
    expression = '(NO-0.044*NOg)'
  []

  [NO2h_func]
    type = ParsedFunction
    symbol_names = 'NO2g NO2'
    symbol_values = 'NO2g NO2'
    expression = '(((0.28*NO2g)-NO2)/(0.28*NO2g))'
  []

  [NO2h_rev_func]
    type = ParsedFunction
    symbol_names = 'NO2g NO2'
    symbol_values = 'NO2g NO2'
    expression = '(NO2-0.28*NO2g)'
  []

  [NO2nh_func]
    type = ParsedFunction
    symbol_names = 'NO2ng NO2n'
    symbol_values = 'NO2ng NO2n'
    expression = '(((0.28 *-NO2ng) - NO2n)/(0.28 * NO2ng))'
  []

  [NO2nh_rev_func]
    type = ParsedFunction
    symbol_names = 'NO2ng NO2n'
    symbol_values = 'NO2ng NO2n'
    expression = '(NO2n - 0.28 * NO2ng)'
  []

  [NO3h_func]
    type = ParsedFunction
    symbol_names = 'NO3g NO3'
    symbol_values = 'NO3g NO3'
    expression = '(((41.5*NO3g)-NO3)/(41.5*NO3g))'
  []

  [NO3h_rev_func]
    type = ParsedFunction
    symbol_names = 'NO3g NO3'
    symbol_values = 'NO3g NO3'
    expression = '(NO3-41.5*NO3g)'
  []

  [HNO3h_func]
    type = ParsedFunction
    symbol_names = 'HNO3g HNO3'
    symbol_values = 'HNO3g HNO3'
    expression = '(((4.8e6*HNO3g)-HNO3)/(4.8e6*HNO3g))'
  []

  [HNO3h_rev_func]
    type = ParsedFunction
    symbol_names = 'HNO3g HNO3'
    symbol_values = 'HNO3g HNO3'
    expression = '(HNO3-4.8e6*HNO3g)'
  []

  [Oh_func]
    type = ParsedFunction
    symbol_names = 'Og O'
    symbol_values = 'Og O'
    expression = '(((1*Og)-O)/(1*Og))'
  []

  [Oh_rev_func]
    type = ParsedFunction
    symbol_names = 'Og O'
    symbol_values = 'Og O'
    expression = '(O-1*Og)'
  []

  [O2h_func]
    type = ParsedFunction
    symbol_names = 'O2g O2'
    symbol_values = 'O2g O2'
    expression = '(((0.0324*O2g)-O2)/(0.0324*O2g))'
  []

  [O2h_rev_func]
    type = ParsedFunction
    symbol_names = 'O2g O2'
    symbol_values = 'O2g O2'
    expression = '(O2-0.0324*O2g)'
  []

  [O3h_func]
    type = ParsedFunction
    symbol_names = 'O3g O3'
    symbol_values = 'O3g O3'
    expression = '(((0.3*O3g)-O3)/(0.3*O3g))'
  []

  [O3h_rev_func]
    type = ParsedFunction
    symbol_names = 'O3g O3'
    symbol_values = 'O3g O3'
    expression = '(O3-0.3*O3g)'
  []
[]

[AuxScalarKernels]
  [neutral_sum]
    type = VariableSum
    variable = M
    args = 'Og O2g N2g O3g NOg NO2g NO3g N2O3g N2O4g N2O5g'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [tcheck]
    type = FunctionScalarAux
    variable = t
    function = tf
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [N2h]
    type = FunctionScalarAux
    variable = N2h
    function = N2h_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [N2rev]
    type = FunctionScalarAux
    variable = N2rev
    function = N2h_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [N2Oh]
    type = FunctionScalarAux
    variable = N2Oh
    function = N2Oh_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [N2Orev]
    type = FunctionScalarAux
    variable = N2Orev
    function = N2Oh_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [N2O3h]
    type = FunctionScalarAux
    variable = N2O3h
    function = N2O3h_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [N2O3rev]
    type = FunctionScalarAux
    variable = N2O3rev
    function = N2O3h_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [N2O4h]
    type = FunctionScalarAux
    variable = N2O4h
    function = N2O4h_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [N2O4rev]
    type = FunctionScalarAux
    variable = N2O4rev
    function = N2O4h_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [N2O5h]
    type = FunctionScalarAux
    variable = N2O5h
    function = N2O5h_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [N2O5rev]
    type = FunctionScalarAux
    variable = N2O5rev
    function = N2O5h_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [NOh]
    type = FunctionScalarAux
    variable = NOh
    function = NOh_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [NOrev]
    type = FunctionScalarAux
    variable = NOrev
    function = NOh_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [NO2h]
    type = FunctionScalarAux
    variable = NO2h
    function = NO2h_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [NO2rev]
    type = FunctionScalarAux
    variable = NO2rev
    function = NO2h_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [NO2nh]
    type = FunctionScalarAux
    variable = NO2nh
    function = NO2nh_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [NO2nrev]
    type = FunctionScalarAux
    variable = NO2nrev
    function = NO2nh_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [NO3h]
    type = FunctionScalarAux
    variable = NO3h
    function = NO3h_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [NO3rev]
    type = FunctionScalarAux
    variable = NO3rev
    function = NO3h_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [HNO3h]
    type = FunctionScalarAux
    variable = HNO3h
    function = HNO3h_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [HNO3rev]
    type = FunctionScalarAux
    variable = HNO3rev
    function = HNO3h_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [Oh]
    type = FunctionScalarAux
    variable = Oh
    function = Oh_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [Orev]
    type = FunctionScalarAux
    variable = Orev
    function = Oh_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [O2h]
    type = FunctionScalarAux
    variable = O2h
    function = O2h_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [O2rev]
    type = FunctionScalarAux
    variable = O2rev
    function = O2h_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [O3h]
    type = FunctionScalarAux
    variable = O3h
    function = O3h_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [O3rev]
    type = FunctionScalarAux
    variable = O3rev
    function = O3h_rev_func
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Debug]
  show_var_residual_norms = false
[]

[Executioner]
  type = Transient
  automatic_scaling = true
  compute_scaling_once = false
  end_time = 1
  solve_type = NEWTON
  dtmin = 1e-15
  dtmax = 1e-1
  line_search = 'none'
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda'
  petsc_options_value = 'NONZERO 1.e-10 1e-3'
  steady_state_detection = false
  l_max_its = 20
  nl_max_its = 30
  [TimeSteppers]
    [adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.925
      dt = 5e-6
      growth_factor = 1.005
    []
  []
[]

[Outputs]
  [out1]
    type = Exodus
    interval = 1
  []
  [out2]
    type = CSV
    interval = 10
  []

  [console]
    type = Console
    execute_scalars_on = 'none'
  []
[]
