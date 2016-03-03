/**
 * @file SpacePoint.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of the SpacePoint abstract class.
 */


#ifndef SPACEPOINT_HPP
#define SPACEPOINT_HPP


#include <memory>
#include "Particle.hpp"
#include "spacePointType.hpp"


/**
 * @ingroup Simulator
 * @{
 */


// Forward declaration.
class SpacePoint;


/**
 * @brief A smart pointer to a SpacePoint implementation.
 */
typedef std::shared_ptr<SpacePoint> SpacePointPtr_t;


/**
 * @brief The representantion of a point in space.
 *
 * @details This class is abstract and should be implemented by a specialization.
 */
class SpacePoint
{
    public:
        // Setters
        /**
         * @brief Sets a Particle in the specified position.
         *
         * @param particle - the Particle to be set
         * @param position - the position of the particle to be replaced
         */
        virtual void setParticle(Particle* particle, const unsigned int position) = 0;

        // Getters
        /**
         * @brief Simple getter.
         *
         * @return number of particle slots
         */
        virtual unsigned int getNumParticleSlots() = 0;

        /**
         * @brief Gets the particle specified.
         *
         * @param particleNum - number of particle slot
         * @return a Particle
         *
         * @see getNumParticles()
         */
        virtual Particle* getParticle(const unsigned int particleNum) = 0;

        /**
         * @brief Simple getter.
         *
         * @return the particle type of this space point
         */
        virtual spacePointType_t getType() = 0;



    protected:
        // Attributes
        unsigned int numParticleSlots; ///< Number of particles in this space point.
        Particle** particleSlots; ///< Particles in this space point.
        spacePointType_t type; ///< Particle type of this space point.



        // Constructors
        /**
         * @brief Nullary constructor.
         */
        SpacePoint();

        /**
         * @brief Copy constructor.
         *
         * @param that - the SpacePoint to copy
         */
        SpacePoint(const SpacePoint& that);

        /**
         * @brief Move constructor.
         *
         * @param that - the rvalue to move
         */
        SpacePoint(SpacePoint&& that);

        /**
         * @brief Initilalization constructor.
         *
         * @param numParticles - number of particles available
         * @param type - initial particle type of this space point
         */
        SpacePoint(const unsigned int numParticleSlots, const spacePointType_t type);



        // Destructor
        /**
         * @brief Destructor.
         */
        virtual ~SpacePoint();



        // Operators
        /**
         * @brief Copy operator.
         *
         * @param that - the SpacePoint to copy
         * @return reference to object copied
         */
        SpacePoint& operator =(const SpacePoint& that);

        /**
         * @brief Move operator.
         *
         * @param that - the rvalue to move
         * @return reference to object moved
         */
        SpacePoint& operator =(SpacePoint&& that);
};


/**
 * @}
 */


#endif // SPACEPOINT_HPP
