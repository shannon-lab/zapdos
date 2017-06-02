#ifndef DRIFTDIFFUSIONENERGY_H
#define DRIFTDIFFUSIONENERGY_H

#include "Kernel.h"

class DriftDiffusionEnergy;

template<>
InputParameters validParams<DriftDiffusionEnergy>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class DriftDiffusionEnergy : public Kernel
{
public:
        DriftDiffusionEnergy(const InputParameters & parameters);
        virtual ~DriftDiffusionEnergy();

protected:

        virtual Real computeQpResidual();
        virtual Real computeQpJacobian();
        virtual Real computeQpOffDiagJacobian(unsigned int jvar);

        Real _r_units;

        const MaterialProperty<Real> & _muel;
        const MaterialProperty<Real> & _d_muel_d_actual_mean_en;
        const MaterialProperty<Real> & _sign;
        const MaterialProperty<Real> & _diffel;
        const MaterialProperty<Real> & _d_diffel_d_actual_mean_en;

        // Coupled variables
        unsigned int _potential_id;
        const VariableGradient & _grad_potential;
        const VariableValue & _em;
        unsigned int _em_id;

        Real _d_actual_mean_en_d_em;
        Real _d_muel_d_em;
        Real _d_actual_mean_en_d_u;
        Real _d_muel_d_u;
        Real _d_diffel_d_u;
        Real _d_diffel_d_em;
};

#endif /* DRIFTDIFFUSIONENERGY_H */
