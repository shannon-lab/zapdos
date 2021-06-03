### Townsend Coefficients with Crane

* Townsend coefficients are ideal in situations where electron flux is field-driven. 
* They follow the same formulation given in Equation 67 of Hagelaar's paper, "Solving the Boltzmann Equation to obtain electron transport coefficietns and rate coefficients for fluid models". (Plasma Sources Sci. Technol. 14 (2005) 722-733)
* \alpha = k * N / ( \mu * E )
* k = rate coefficient; N = target gas density; \mu = electron mobility; E = electric field
* To tabulate your rate coefficients in terms of townsend coefficients, leave out the target density. (e.g. your tabulated data will be k/(\mu * E) * 6.022e23, where k is in units of m^3/s, mu is [m^2 s^-1], E is [V m^-1]
* We multiply by 6.022e23 to put the resulting townsend coefficient into units of m^2 mol^-1. 
* Note that this is necessary because species densities in Zapdos are treated as molar log densities, so exp(_em[_qp]) is a MOLAR density, not a number density. 
* **It is up to the user to ensure that the units of all species, rate coefficients, and townsend coefficients are consistent**. If the simulation fails to run, the most likely culprit is inconsistent reaction units.
