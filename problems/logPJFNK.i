
Framework Information:
MOOSE version:           git commit e91e6c9 on 2016-04-06
PETSc Version:           3.6.0
Current Time:            Tue Apr 26 14:33:30 2016
Executable Timestamp:    Tue Apr 26 14:24:30 2016

Parallelism:
  Num Processors:          1
  Num Threads:             1

Mesh:
  Distribution:            serial
  Mesh Dimension:          1
  Spatial Dimension:       3
  Nodes:
    Total:                 275
    Local:                 275
  Elems:
    Total:                 274
    Local:                 274
  Num Subdomains:          2
  Num Partitions:          1

Nonlinear System:
  Num DOFs:                1039
  Num Local DOFs:          1039
  Variables:               "potential" "em" "emliq" { "Arp" "mean_en" } "OHm"
  Finite Element Types:    "LAGRANGE" "LAGRANGE" "LAGRANGE" "LAGRANGE" "LAGRANGE"
  Approximation Orders:    "FIRST" "FIRST" "FIRST" "FIRST" "FIRST"

Auxiliary System:
  Num DOFs:                4344
  Num Local DOFs:          4344
  Variables:               "e_temp" "x" "x_node" "rho" "rholiq" "em_lin" "emliq_lin" "Arp_lin" "OHm_lin"
                             "Efield" "Current_em" "Current_emliq" "Current_Arp" "Current_OHm" "tot_gas_current"
                             { "tot_liq_current" "tot_flux_OHm" } { "EFieldAdvAux_em" "DiffusiveFlux_em"
                             } { "EFieldAdvAux_emliq" "DiffusiveFlux_emliq" } { "PowerDep_em" "PowerDep_Arp"
                             "ProcRate_el" "ProcRate_ex" "ProcRate_iz" }
  Finite Element Types:    "MONOMIAL" "MONOMIAL" "LAGRANGE" "MONOMIAL" "MONOMIAL" "MONOMIAL" "MONOMIAL"
                             "MONOMIAL" "MONOMIAL" "MONOMIAL" "MONOMIAL" "MONOMIAL" "MONOMIAL" "MONOMIAL"
                             "MONOMIAL" "MONOMIAL" "MONOMIAL" "MONOMIAL" "MONOMIAL"
  Approximation Orders:    "CONSTANT" "CONSTANT" "FIRST" "CONSTANT" "CONSTANT" "CONSTANT" "CONSTANT"
                             "CONSTANT" "CONSTANT" "CONSTANT" "CONSTANT" "CONSTANT" "CONSTANT" "CONSTANT"
                             "CONSTANT" "CONSTANT" "CONSTANT" "CONSTANT" "CONSTANT"

Execution Information:
  Executioner:             Transient
  TimeStepper:             IterationAdaptiveDT
  Solver Mode:             Preconditioned JFNK




Time Step  0, time = 0
                dt = 0

Postprocessor Values:
+----------------+----------------+
| time           | cathode_flux   |
+----------------+----------------+
|   0.000000e+00 |   0.000000e+00 |
+----------------+----------------+


Time Step  1, time = 1e-09
                dt = 1e-09
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 0 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 6.520488e+04
      2 Linear |R| = 6.519646e+04
      3 Linear |R| = 6.466150e+04
      4 Linear |R| = 6.460228e+04
      5 Linear |R| = 6.412240e+04
      6 Linear |R| = 6.412184e+04
      7 Linear |R| = 6.411897e+04
      8 Linear |R| = 6.407155e+04
      9 Linear |R| = 6.407025e+04
     10 Linear |R| = 6.406323e+04
     11 Linear |R| = 6.406323e+04
     12 Linear |R| = 6.337865e+04
     13 Linear |R| = 6.337116e+04
     14 Linear |R| = 6.337003e+04
     15 Linear |R| = 6.336998e+04
     16 Linear |R| = 6.336982e+04
     17 Linear |R| = 6.336969e+04
     18 Linear |R| = 5.117932e+04
     19 Linear |R| = 5.117931e+04
     20 Linear |R| = 5.117923e+04
     21 Linear |R| = 5.116860e+04
     22 Linear |R| = 5.116660e+04
     23 Linear |R| = 5.116657e+04
     24 Linear |R| = 5.116187e+04
     25 Linear |R| = 5.115764e+04
      Line search: gnorm after quadratic fit 8.861546357422e+04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860874565712e+04 lambda=5.0000000000000003e-02
      Line search: Cubically determined step, current gnorm 8.860803601518e+04 lambda=2.5000000000000001e-02
    |residual|_2 of individual variables:
                  potential: 88499.2
                  em:        0.979376
                  emliq:     1003.31
                  Arp:       0.427595
                  mean_en:   43.0656
                  OHm:       4274.08

 1 Nonlinear |R| = 8.860804e+04
      0 Linear |R| = 8.860804e+04
      1 Linear |R| = 8.860804e+04
      2 Linear |R| = 8.860804e+04
      3 Linear |R| = 8.860804e+04
      4 Linear |R| = 8.860803e+04
      5 Linear |R| = 8.860803e+04
      6 Linear |R| = 8.860803e+04
      7 Linear |R| = 8.860803e+04
      8 Linear |R| = 8.860802e+04
      9 Linear |R| = 8.860802e+04
     10 Linear |R| = 8.860802e+04
     11 Linear |R| = 8.860801e+04
     12 Linear |R| = 8.860801e+04
     13 Linear |R| = 2.816479e+04
     14 Linear |R| = 2.751141e+04
     15 Linear |R| = 2.649848e+04
     16 Linear |R| = 2.649785e+04
     17 Linear |R| = 2.639025e+04
     18 Linear |R| = 2.638106e+04
     19 Linear |R| = 2.595511e+04
     20 Linear |R| = 2.593297e+04
     21 Linear |R| = 2.592336e+04
     22 Linear |R| = 2.579716e+04
     23 Linear |R| = 2.579706e+04
     24 Linear |R| = 2.573295e+04
     25 Linear |R| = 2.573271e+04
Nonlinear solve did not converge due to DIVERGED_LINE_SEARCH iterations 1
 Solve Did NOT Converge!

Solve failed, cutting timestep.

Time Step  1, time = 4e-10
                dt = 4e-10
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 0 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 8.860872e+04
      2 Linear |R| = 8.860872e+04
      3 Linear |R| = 8.860872e+04
      4 Linear |R| = 8.860868e+04
      5 Linear |R| = 8.860317e+04
      6 Linear |R| = 8.860317e+04
      7 Linear |R| = 8.860317e+04
      8 Linear |R| = 8.860317e+04
      9 Linear |R| = 8.860317e+04
     10 Linear |R| = 8.860317e+04
     11 Linear |R| = 8.860317e+04
     12 Linear |R| = 8.860317e+04
     13 Linear |R| = 8.860317e+04
     14 Linear |R| = 8.860317e+04
     15 Linear |R| = 8.860317e+04
     16 Linear |R| = 5.116948e+04
     17 Linear |R| = 5.116837e+04
     18 Linear |R| = 5.116823e+04
     19 Linear |R| = 5.116821e+04
     20 Linear |R| = 5.116641e+04
     21 Linear |R| = 4.434942e+04
     22 Linear |R| = 4.431754e+04
     23 Linear |R| = 4.431376e+04
     24 Linear |R| = 4.431150e+04
     25 Linear |R| = 4.430519e+04
      Line search: gnorm after quadratic fit 3.443983846623e+05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.861061993580e+04 lambda=5.0000000000000003e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860932188488e+04 lambda=2.5000000000000001e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860893223776e+04 lambda=1.0559945127314709e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860880794790e+04 lambda=4.6052081067382827e-03
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860876155642e+04 lambda=1.9974677801945619e-03
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860874309091e+04 lambda=8.6722695058235786e-04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873540591e+04 lambda=3.7645826381688477e-04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873211918e+04 lambda=1.6342352473734990e-04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873070628e+04 lambda=7.0943222608525622e-05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873009282e+04 lambda=3.0796942151967541e-05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872982296e+04 lambda=1.3369178903774414e-05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872969783e+04 lambda=5.8037192085906533e-06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872967716e+04 lambda=2.5196210577299980e-06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872964236e+04 lambda=1.0935793790935231e-06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962507e+04 lambda=4.7473759671524070e-07
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872964124e+04 lambda=2.0617232856703792e-07
      Line search: Cubically determined step, current gnorm 8.860872960808e+04 lambda=8.9316155417434999e-08
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698396
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 1 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 5.938372e+04
      2 Linear |R| = 5.337067e+04
      3 Linear |R| = 5.334165e+04
      4 Linear |R| = 5.295590e+04
      5 Linear |R| = 4.974257e+04
      6 Linear |R| = 4.813796e+04
      7 Linear |R| = 4.800164e+04
      8 Linear |R| = 4.639952e+04
      9 Linear |R| = 4.497854e+04
     10 Linear |R| = 4.489976e+04
     11 Linear |R| = 4.455648e+04
     12 Linear |R| = 4.441809e+04
     13 Linear |R| = 4.441503e+04
     14 Linear |R| = 4.441480e+04
     15 Linear |R| = 4.440510e+04
     16 Linear |R| = 4.438993e+04
     17 Linear |R| = 4.437971e+04
     18 Linear |R| = 4.434317e+04
     19 Linear |R| = 4.432591e+04
     20 Linear |R| = 4.432361e+04
     21 Linear |R| = 4.431610e+04
     22 Linear |R| = 4.431489e+04
     23 Linear |R| = 4.431472e+04
     24 Linear |R| = 4.431457e+04
     25 Linear |R| = 4.431452e+04
Nonlinear solve did not converge due to DIVERGED_LINE_SEARCH iterations 1
 Solve Did NOT Converge!

Solve failed, cutting timestep.

Time Step  1, time = 1.6e-10
                dt = 1.6e-10
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 0 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 8.860873e+04
      2 Linear |R| = 6.673943e+04
      3 Linear |R| = 6.611222e+04
      4 Linear |R| = 6.339042e+04
      5 Linear |R| = 6.338860e+04
      6 Linear |R| = 6.315313e+04
      7 Linear |R| = 6.273668e+04
      8 Linear |R| = 5.155050e+04
      9 Linear |R| = 5.154779e+04
     10 Linear |R| = 4.530668e+04
     11 Linear |R| = 4.530019e+04
     12 Linear |R| = 4.519509e+04
     13 Linear |R| = 4.512694e+04
     14 Linear |R| = 4.495854e+04
     15 Linear |R| = 4.477157e+04
     16 Linear |R| = 4.445287e+04
     17 Linear |R| = 4.442955e+04
     18 Linear |R| = 4.442695e+04
     19 Linear |R| = 4.435604e+04
     20 Linear |R| = 4.435585e+04
     21 Linear |R| = 4.434487e+04
     22 Linear |R| = 4.431010e+04
     23 Linear |R| = 4.430876e+04
     24 Linear |R| = 4.430837e+04
     25 Linear |R| = 4.430833e+04
      Line search: gnorm after quadratic fit 7.534168966326e+13
      Line search: Cubic step no good, shrinking lambda, current gnorm 3.376604669344e+06 lambda=5.0000000000000003e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.862208346308e+04 lambda=2.5000000000000001e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.861093866961e+04 lambda=1.2500000000000001e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860995564633e+04 lambda=5.2753114852141089e-03
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860889368264e+04 lambda=2.2956464347736456e-03
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860875862544e+04 lambda=9.9588976868874310e-04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873607631e+04 lambda=4.3242303035430612e-04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873137067e+04 lambda=1.8775722995151707e-04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873021409e+04 lambda=8.1528727747423544e-05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872984224e+04 lambda=3.5402089917250482e-05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872971647e+04 lambda=1.5372745728675942e-05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872966042e+04 lambda=6.6753435456545542e-06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872964203e+04 lambda=2.8986726326267397e-06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872964139e+04 lambda=1.2586935714745297e-06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962465e+04 lambda=5.4651265279925312e-07
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962455e+04 lambda=2.3733711322015068e-07
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962450e+04 lambda=1.0306459296049308e-07
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962449e+04 lambda=4.4756604954994775e-08
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962448e+04 lambda=1.9435881720085527e-08
      Line search: Cubically determined step, current gnorm 8.860872960797e+04 lambda=8.4401710499874191e-09
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 1 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 8.860873e+04
      2 Linear |R| = 8.860873e+04
      3 Linear |R| = 6.578026e+04
      4 Linear |R| = 6.570669e+04
      5 Linear |R| = 5.001341e+04
      6 Linear |R| = 4.678102e+04
      7 Linear |R| = 4.670015e+04
      8 Linear |R| = 4.586631e+04
      9 Linear |R| = 4.574197e+04
     10 Linear |R| = 4.448865e+04
     11 Linear |R| = 4.448310e+04
     12 Linear |R| = 4.444001e+04
     13 Linear |R| = 4.444000e+04
     14 Linear |R| = 4.440425e+04
     15 Linear |R| = 4.433525e+04
     16 Linear |R| = 4.432809e+04
     17 Linear |R| = 4.432780e+04
     18 Linear |R| = 4.432678e+04
     19 Linear |R| = 4.431429e+04
     20 Linear |R| = 4.430561e+04
     21 Linear |R| = 4.430541e+04
     22 Linear |R| = 4.430379e+04
     23 Linear |R| = 4.430338e+04
     24 Linear |R| = 4.430306e+04
     25 Linear |R| = 4.430304e+04
Nonlinear solve did not converge due to DIVERGED_LINE_SEARCH iterations 1
 Solve Did NOT Converge!

Solve failed, cutting timestep.

Time Step  1, time = 6.4e-11
                dt = 6.4e-11
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 0 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 8.860873e+04
      2 Linear |R| = 8.860873e+04
      3 Linear |R| = 8.860873e+04
      4 Linear |R| = 6.578560e+04
      5 Linear |R| = 6.578341e+04
      6 Linear |R| = 6.578297e+04
      7 Linear |R| = 6.577765e+04
      8 Linear |R| = 6.577338e+04
      9 Linear |R| = 6.276242e+04
     10 Linear |R| = 6.274562e+04
     11 Linear |R| = 6.267159e+04
     12 Linear |R| = 6.267114e+04
     13 Linear |R| = 6.266730e+04
     14 Linear |R| = 6.266725e+04
     15 Linear |R| = 6.266301e+04
     16 Linear |R| = 6.266025e+04
     17 Linear |R| = 6.266022e+04
     18 Linear |R| = 4.434100e+04
     19 Linear |R| = 4.432101e+04
     20 Linear |R| = 4.432053e+04
     21 Linear |R| = 4.431843e+04
     22 Linear |R| = 4.431181e+04
     23 Linear |R| = 4.431173e+04
     24 Linear |R| = 4.430748e+04
     25 Linear |R| = 4.430748e+04
Nonlinear solve did not converge due to DIVERGED_LINE_SEARCH iterations 0
 Solve Did NOT Converge!

Solve failed, cutting timestep.

Time Step  1, time = 2.56e-11
                dt = 2.56e-11
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 0 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 8.860873e+04
      2 Linear |R| = 8.860873e+04
      3 Linear |R| = 8.860872e+04
      4 Linear |R| = 8.860868e+04
      5 Linear |R| = 8.860861e+04
      6 Linear |R| = 8.860853e+04
      7 Linear |R| = 8.860849e+04
      8 Linear |R| = 8.860849e+04
      9 Linear |R| = 8.860848e+04
     10 Linear |R| = 7.689111e+04
     11 Linear |R| = 7.687992e+04
     12 Linear |R| = 4.929486e+04
     13 Linear |R| = 4.899263e+04
     14 Linear |R| = 4.452322e+04
     15 Linear |R| = 4.452318e+04
     16 Linear |R| = 4.446527e+04
     17 Linear |R| = 4.440697e+04
     18 Linear |R| = 4.439816e+04
     19 Linear |R| = 4.436430e+04
     20 Linear |R| = 4.434505e+04
     21 Linear |R| = 4.434025e+04
     22 Linear |R| = 4.433350e+04
     23 Linear |R| = 4.430691e+04
     24 Linear |R| = 4.430689e+04
     25 Linear |R| = 4.430574e+04
      Line search: gnorm after quadratic fit 8.997241991920e+04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.869780883261e+04 lambda=5.0000000000000003e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.861999267124e+04 lambda=2.1654783256740810e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860930011549e+04 lambda=2.1654783256740812e-03
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860878250834e+04 lambda=2.1654783256740812e-04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873485775e+04 lambda=2.1654783256740814e-05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873014075e+04 lambda=2.1654783256740814e-06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872967115e+04 lambda=2.1654783256740814e-07
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872964069e+04 lambda=2.1654783256740816e-08
      Line search: Cubically determined step, current gnorm 8.860872962444e+04 lambda=2.1654783256740816e-09
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 1 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 8.860873e+04
      2 Linear |R| = 8.860865e+04
      3 Linear |R| = 8.860865e+04
      4 Linear |R| = 8.860865e+04
      5 Linear |R| = 8.860865e+04
      6 Linear |R| = 8.860865e+04
      7 Linear |R| = 8.860849e+04
      8 Linear |R| = 8.860848e+04
      9 Linear |R| = 8.860831e+04
     10 Linear |R| = 8.860725e+04
     11 Linear |R| = 8.860680e+04
     12 Linear |R| = 8.860673e+04
     13 Linear |R| = 8.860671e+04
     14 Linear |R| = 8.860662e+04
     15 Linear |R| = 8.860662e+04
     16 Linear |R| = 8.860648e+04
     17 Linear |R| = 4.435455e+04
     18 Linear |R| = 4.433165e+04
     19 Linear |R| = 4.432761e+04
     20 Linear |R| = 4.432673e+04
     21 Linear |R| = 4.432486e+04
     22 Linear |R| = 4.431595e+04
     23 Linear |R| = 4.430935e+04
     24 Linear |R| = 4.430463e+04
     25 Linear |R| = 4.430397e+04
      Line search: gnorm after quadratic fit 8.904863805275e+04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.870180288407e+04 lambda=5.0000000000000003e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860987532255e+04 lambda=5.0000000000000010e-03
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860876713068e+04 lambda=5.0000000000000012e-04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873285963e+04 lambda=5.4420949854000444e-05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873002262e+04 lambda=6.9347408499369244e-06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872966015e+04 lambda=8.9254087326148687e-07
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872964413e+04 lambda=1.4806058576864317e-07
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962476e+04 lambda=1.4806058576864317e-08
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962452e+04 lambda=3.6458190098569375e-09
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962446e+04 lambda=8.1139521492527115e-10
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962445e+04 lambda=1.8633647110487741e-10
      Line search: Cubically determined step, current gnorm 8.860872962444e+04 lambda=4.0123817725984557e-11
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 2 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 8.860873e+04
      2 Linear |R| = 8.860873e+04
      3 Linear |R| = 6.526488e+04
      4 Linear |R| = 5.275172e+04
      5 Linear |R| = 5.226286e+04
      6 Linear |R| = 5.068485e+04
      7 Linear |R| = 5.063323e+04
      8 Linear |R| = 4.685863e+04
      9 Linear |R| = 4.601796e+04
     10 Linear |R| = 4.599653e+04
     11 Linear |R| = 4.550763e+04
     12 Linear |R| = 4.542051e+04
     13 Linear |R| = 4.536575e+04
     14 Linear |R| = 4.508882e+04
     15 Linear |R| = 4.506433e+04
     16 Linear |R| = 4.488038e+04
     17 Linear |R| = 4.473527e+04
     18 Linear |R| = 4.454660e+04
     19 Linear |R| = 4.449949e+04
     20 Linear |R| = 4.446789e+04
     21 Linear |R| = 4.445721e+04
     22 Linear |R| = 4.434607e+04
     23 Linear |R| = 4.434288e+04
     24 Linear |R| = 4.432896e+04
     25 Linear |R| = 4.432750e+04
      Line search: gnorm after quadratic fit 2.474568748272e+06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.867912038296e+04 lambda=5.0000000000000003e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.862448813894e+04 lambda=2.5000000000000001e-02
      Line search: Cubically determined step, current gnorm 8.860867198242e+04 lambda=2.5000000000000005e-03
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.838269
                  emliq:     992.522
                  Arp:       0.427592
                  mean_en:   42.9667
                  OHm:       4274.11

 3 Nonlinear |R| = 8.860867e+04
      0 Linear |R| = 8.860867e+04
      1 Linear |R| = 8.860867e+04
      2 Linear |R| = 6.523770e+04
      3 Linear |R| = 6.254121e+04
      4 Linear |R| = 6.178652e+04
      5 Linear |R| = 5.423373e+04
      6 Linear |R| = 4.054199e+04
      7 Linear |R| = 4.039504e+04
      8 Linear |R| = 3.991355e+04
      9 Linear |R| = 3.977026e+04
     10 Linear |R| = 3.976772e+04
     11 Linear |R| = 3.973840e+04
     12 Linear |R| = 3.972139e+04
     13 Linear |R| = 3.971691e+04
     14 Linear |R| = 3.970819e+04
     15 Linear |R| = 3.970815e+04
     16 Linear |R| = 3.969710e+04
     17 Linear |R| = 3.966792e+04
     18 Linear |R| = 3.966758e+04
     19 Linear |R| = 3.966455e+04
     20 Linear |R| = 3.966451e+04
     21 Linear |R| = 3.966407e+04
     22 Linear |R| = 3.965405e+04
     23 Linear |R| = 3.964435e+04
     24 Linear |R| = 3.964093e+04
     25 Linear |R| = 3.963509e+04
Nonlinear solve did not converge due to DIVERGED_LINE_SEARCH iterations 3
 Solve Did NOT Converge!

Solve failed, cutting timestep.

Time Step  1, time = 1.024e-11
                dt = 1.024e-11
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 0 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 6.756549e+04
      2 Linear |R| = 6.721053e+04
      3 Linear |R| = 6.689341e+04
      4 Linear |R| = 6.677726e+04
      5 Linear |R| = 6.677712e+04
      6 Linear |R| = 6.676145e+04
      7 Linear |R| = 6.673410e+04
      8 Linear |R| = 6.665575e+04
      9 Linear |R| = 6.446750e+04
     10 Linear |R| = 6.321501e+04
     11 Linear |R| = 6.319121e+04
     12 Linear |R| = 6.277461e+04
     13 Linear |R| = 6.268721e+04
     14 Linear |R| = 6.268596e+04
     15 Linear |R| = 6.267816e+04
     16 Linear |R| = 6.265885e+04
     17 Linear |R| = 4.439877e+04
     18 Linear |R| = 4.438610e+04
     19 Linear |R| = 4.436045e+04
     20 Linear |R| = 4.432641e+04
     21 Linear |R| = 4.431784e+04
     22 Linear |R| = 4.431782e+04
     23 Linear |R| = 4.431721e+04
     24 Linear |R| = 4.431721e+04
     25 Linear |R| = 4.431646e+04
Nonlinear solve did not converge due to DIVERGED_LINE_SEARCH iterations 0
 Solve Did NOT Converge!

Solve failed, cutting timestep.

Time Step  1, time = 4.096e-12
                dt = 4.096e-12
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 0 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 6.674587e+04
      2 Linear |R| = 6.531334e+04
      3 Linear |R| = 6.487408e+04
      4 Linear |R| = 6.356712e+04
      5 Linear |R| = 6.304427e+04
      6 Linear |R| = 6.293844e+04
      7 Linear |R| = 6.290428e+04
      8 Linear |R| = 6.285190e+04
      9 Linear |R| = 4.541681e+04
     10 Linear |R| = 4.539076e+04
     11 Linear |R| = 4.536466e+04
     12 Linear |R| = 4.509318e+04
     13 Linear |R| = 4.509269e+04
     14 Linear |R| = 4.475905e+04
     15 Linear |R| = 4.475438e+04
     16 Linear |R| = 4.457413e+04
     17 Linear |R| = 4.457132e+04
     18 Linear |R| = 4.451868e+04
     19 Linear |R| = 4.449860e+04
     20 Linear |R| = 4.449314e+04
     21 Linear |R| = 4.445675e+04
     22 Linear |R| = 4.445606e+04
     23 Linear |R| = 4.434554e+04
     24 Linear |R| = 4.432935e+04
     25 Linear |R| = 4.432848e+04
Nonlinear solve did not converge due to DIVERGED_LINE_SEARCH iterations 0
 Solve Did NOT Converge!

Solve failed, cutting timestep.

Time Step  1, time = 1.6384e-12
                dt = 1.6384e-12
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 0 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 8.860873e+04
      2 Linear |R| = 6.461852e+04
      3 Linear |R| = 6.461183e+04
      4 Linear |R| = 6.332364e+04
      5 Linear |R| = 6.317982e+04
      6 Linear |R| = 6.300910e+04
      7 Linear |R| = 6.288303e+04
      8 Linear |R| = 6.287974e+04
      9 Linear |R| = 6.270278e+04
     10 Linear |R| = 6.267723e+04
     11 Linear |R| = 6.267094e+04
     12 Linear |R| = 6.266835e+04
     13 Linear |R| = 6.266804e+04
     14 Linear |R| = 6.266650e+04
     15 Linear |R| = 6.266649e+04
     16 Linear |R| = 6.266556e+04
     17 Linear |R| = 6.266546e+04
     18 Linear |R| = 6.266433e+04
     19 Linear |R| = 6.266422e+04
     20 Linear |R| = 6.266203e+04
     21 Linear |R| = 6.266203e+04
     22 Linear |R| = 6.265687e+04
     23 Linear |R| = 6.265562e+04
     24 Linear |R| = 6.265296e+04
     25 Linear |R| = 4.430748e+04
Nonlinear solve did not converge due to DIVERGED_LINE_SEARCH iterations 0
 Solve Did NOT Converge!

Solve failed, cutting timestep.

Time Step  1, time = 1e-12
                dt = 1e-12
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 0 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 6.820462e+04
      2 Linear |R| = 6.749486e+04
      3 Linear |R| = 6.403597e+04
      4 Linear |R| = 6.371256e+04
      5 Linear |R| = 6.304963e+04
      6 Linear |R| = 6.279135e+04
      7 Linear |R| = 6.278584e+04
      8 Linear |R| = 6.277657e+04
      9 Linear |R| = 6.277472e+04
     10 Linear |R| = 6.275325e+04
     11 Linear |R| = 5.128693e+04
     12 Linear |R| = 5.128686e+04
     13 Linear |R| = 5.126835e+04
     14 Linear |R| = 5.126263e+04
     15 Linear |R| = 5.123213e+04
     16 Linear |R| = 5.123085e+04
     17 Linear |R| = 4.449449e+04
     18 Linear |R| = 4.448303e+04
     19 Linear |R| = 4.446161e+04
     20 Linear |R| = 4.439076e+04
     21 Linear |R| = 4.437270e+04
     22 Linear |R| = 4.436962e+04
     23 Linear |R| = 4.436272e+04
     24 Linear |R| = 4.435192e+04
     25 Linear |R| = 4.435192e+04
      Line search: gnorm after quadratic fit 8.879012429231e+04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.863029645642e+04 lambda=5.0000000000000003e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.861090981451e+04 lambda=5.6743142998394829e-03
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860894454821e+04 lambda=5.6743142998394826e-04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860875108760e+04 lambda=5.6743142998394832e-05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873176553e+04 lambda=5.6743142998394837e-06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872982537e+04 lambda=5.6743142998394835e-07
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872964126e+04 lambda=5.6743142998394836e-08
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962450e+04 lambda=5.6743142998394841e-09
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962448e+04 lambda=2.0960817573441713e-09
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962448e+04 lambda=6.7790426022339766e-10
      Line search: Cubically determined step, current gnorm 8.860872960797e+04 lambda=1.8887660555149542e-10
    |residual|_2 of individual variables:
                  potential: 88500
                  em:        0.698397
                  emliq:     993.502
                  Arp:       0.427591
                  mean_en:   42.917
                  OHm:       4274.12

 1 Nonlinear |R| = 8.860873e+04
      0 Linear |R| = 8.860873e+04
      1 Linear |R| = 6.471589e+04
      2 Linear |R| = 6.461930e+04
      3 Linear |R| = 6.437866e+04
      4 Linear |R| = 6.381879e+04
      5 Linear |R| = 6.373047e+04
      6 Linear |R| = 6.367118e+04
      7 Linear |R| = 6.288504e+04
      8 Linear |R| = 6.288503e+04
      9 Linear |R| = 6.281804e+04
     10 Linear |R| = 6.281694e+04
     11 Linear |R| = 6.281569e+04
     12 Linear |R| = 6.280016e+04
     13 Linear |R| = 6.277446e+04
     14 Linear |R| = 6.277396e+04
     15 Linear |R| = 6.274830e+04
     16 Linear |R| = 6.272465e+04
     17 Linear |R| = 6.268860e+04
     18 Linear |R| = 6.266933e+04
     19 Linear |R| = 6.266859e+04
     20 Linear |R| = 6.266160e+04
     21 Linear |R| = 6.266151e+04
     22 Linear |R| = 4.442764e+04
     23 Linear |R| = 4.441960e+04
     24 Linear |R| = 4.440896e+04
     25 Linear |R| = 4.439124e+04
      Line search: gnorm after quadratic fit 4.346316197065e+07
      Line search: Cubic step no good, shrinking lambda, current gnorm 2.338854778275e+05 lambda=5.0000000000000003e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 1.397794372936e+05 lambda=2.5000000000000001e-02
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.931212205962e+04 lambda=2.5000000000000005e-03
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.862046349247e+04 lambda=2.5000000000000006e-04
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860931423919e+04 lambda=2.5000000000000008e-05
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860878221094e+04 lambda=2.5000000000000011e-06
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873481764e+04 lambda=2.5000000000000009e-07
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860873013660e+04 lambda=2.5000000000000012e-08
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872967568e+04 lambda=2.5000000000000013e-09
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872964115e+04 lambda=2.5000000000000012e-10
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872960799e+04 lambda=2.5000000000000014e-11
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962448e+04 lambda=1.0016649545453952e-11
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962447e+04 lambda=1.0016649545453953e-12
      Line search: Cubic step no good, shrinking lambda, current gnorm 8.860872962447e+04 lambda=1.0016649545453953e-13
      Line search: unable to find good step length! After 14 tries
      Line search: fnorm=8.8608729607969261e+04, gnorm=8.8608729624473926e+04, ynorm=7.3593662937614295e+02, minlambda=9.9999999999999998e-13, lambda=1.0016649545453953e-13, initial slope=-6.0117319030321047e+07
Nonlinear solve did not converge due to DIVERGED_LINE_SEARCH iterations 1
 Solve Did NOT Converge!




*** ERROR ***
Solve failed and timestep already at dtmin, cannot continue!

Stack frames: 9
0: libMesh::print_trace(std::ostream&)
1: IterationAdaptiveDT::computeFailedDT()
2: TimeStepper::computeStep()
3: Transient::execute()
4: MooseApp::executeExecutioner()
5: MooseApp::run()
6: ../zapdos-opt() [0x40c842]
7: __libc_start_main
8: ../zapdos-opt() [0x40c8d9]
[0] /home/lindsayad/moose/framework/src/timesteppers/IterationAdaptiveDT.C, line 225, compiled nodate at notime
--------------------------------------------------------------------------
MPI_ABORT was invoked on rank 0 in communicator MPI_COMM_WORLD
with errorcode 1.

NOTE: invoking MPI_ABORT causes Open MPI to kill all MPI processes.
You may or may not see output from other processes, depending on
exactly when Open MPI kills them.
--------------------------------------------------------------------------
