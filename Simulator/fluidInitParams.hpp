/**
 * @file fluidInitParams.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of the fluidInitParams_t structure.
 */


#ifndef FLUIDINITPARAMS_HPP
#define FLUIDINITPARAMS_HPP


/**
 * @ingroup Simulator
 * @{
 */


/**
 * @brief The percentage of concentration of a fluid in the mixture.
 */
typedef double concentration_t;

/**
 * @brief The mass of the particles of a fluid.
 */
typedef double mass_t;

/**
 * @brief The velocity of a particle in the fluid.
 */
typedef double velocity_t;

/**
 * @brief The id of a particle in the fluid.
 */
typedef int idParticle_t;

/**
 * @brief Encapsulates the initialization parameters for a given fluid.
 *
 * @details This struct contains the physical properties of each fluid
 *          to be simulated.
 */
struct fluidInitParams_t
{
    concentration_t concentration; ///< The percentage of this constituent in the volume of the mixture.
    mass_t mass; ///< The particle's mass of this constituent.
    velocity_t velocity; ///< The velocity of the constituent at injection time.

    /**
     * @brief Default constructor.
     */
    fluidInitParams_t() : fluidInitParams_t(0, 0, 0) {}

    /**
     * @brief fluidInitParams_t
     *
     * @param concentration - percentage of this fluid in the mixture
     * @param mass - mass of the particles of this fluid
     * @param velocity - the constant velocity at which the fluid is continuously injected into the static mixer
     */
    fluidInitParams_t(const concentration_t concentration, const mass_t mass, const velocity_t velocity)
                      : concentration(concentration), mass(mass), velocity(velocity) {}
};


/**
  * @}
  */


#endif // FLUIDINITPARAMS_HPP
