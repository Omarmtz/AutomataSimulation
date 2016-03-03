/**
 * @file Particle.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of the Particle class.
 */


#ifndef PARTICLE_HPP
#define PARTICLE_HPP


#include "fluidInitParams.hpp"
#include "spacePointType.hpp"


/**
 * @ingroup Simulator
 * @{
 */


/**
 * @brief Representation of a particle.
 *
 * @todo Should mass and type be constant?
 */
class Particle
{
    public:
        // Constructors
        /**
         * @brief Nullary constructor.
         */
        Particle();

        /**
         * @brief Copy constructor - default.
         */
        Particle(const Particle&) = default;

        /**
         * @brief Move constructor - default.
         */
        Particle(Particle&&) = default;

        /**
         * @brief Initialization constructor.
         *
         * @param mass - particle's mass
         * @param velocity - particle's initial velocity
         * @param type - the type of this particle
         */
        Particle(spacePointType_t type, mass_t mass, velocity_t velocity);


        // Destructor
        /**
          * @brief Destructor - default.
          */
        ~Particle() = default;


        // Operators
        /**
         * @brief Copy operator - default.
         *
         * @return reference to object copied
         */
        Particle& operator =(const Particle&) = default;

        /**
         * @brief Move operator - default.
         *
         * @return reference to object moved
         */
        Particle& operator =(Particle&&) = default;


        // Setters
        /**
         * @brief Simple setter.
         *
         * @param type
         */
        void setType(spacePointType_t type);

        /**
         * @brief Simple setter.
         *
         * @param mass
         */
        void setMass(mass_t mass);

        /**
         * @brief Simple setter.
         *
         * @param velocity
         */
        void setVelocity(velocity_t velocity);


        // Getters
        /**
         * @brief Simple getter.
         *
         * @return type
         */
        spacePointType_t getType();

        /**
         * @brief Simple getter.
         *
         * @return mass
         */
        mass_t getMass();

        /**
         * @brief Simple getter.
         *
         * @return velocity
         */
        velocity_t getVelocity();



    private:
        // Attributes
        spacePointType_t type; ///< The particle's type.
        mass_t mass; ///< The mass this particle has.
        velocity_t velocity; ///< The current velocity this particle has.
        idParticle_t id; ///< The current id this particle has.
        static int s_nIDGenerator;///< The id control of all particles.
};


/**
  * @}
  */


#endif // PARTICLE_HPP
