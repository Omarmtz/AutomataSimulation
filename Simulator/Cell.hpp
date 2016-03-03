/**
 * @file Cell.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of the Cell class.
 */


#ifndef CELL_HPP
#define CELL_HPP


#include "SpacePoint.hpp"


/**
 * @ingroup Simulator
 * @{
 */


/**
 * @brief The state a cell has.
 *
 * @details The possible states are defined by the CA.
 */
typedef unsigned int cellState_t;


/**
 * @brief This class represents a cell from the CA.
 */
class Cell : public SpacePoint
{
    public:
        // Constructors
        /**
         * @brief Nullary constructor.
         */
        Cell();

        /**
         * @brief Copy constructor - default.
         */
        Cell(const Cell&) = default;

        /**
         * @brief Move constructor - default.
         */
        Cell(Cell&&) = default;

        /**
         * @brief Initialization constructor.
         *
         * @param numParticleSlots - the maximumu amount of particles this cell can hold
         * @param type - the intial type of space point
         * @param state - the initial state of the cell
         * @param numParticleTypes - the number of different possible fluid particle types
         *
         * @throws error_e::signError
         */
        Cell(const unsigned int numParticleSlots, const spacePointType_t type,
             const cellState_t state, const unsigned int numParticleTypes);


        // Destructor
        /**
          * @brief Destructor - default.
          */
        ~Cell() = default;


        // Operators
        /**
         * @brief Copy operator - default.
         *
         * @return reference to object copied
         */
        Cell& operator =(const Cell&) = default;

        /**
         * @brief Move operator - default.
         *
         * @return reference to object moved
         */
        Cell& operator =(Cell&&) = default;


        // Setters
        /**
         * @brief Simple setter.
         *
         * @param particle - particle to update
         * @param position - number of particle slot
         */
        void setParticle(Particle* particle, const unsigned int position);

        /**
         * @brief Simple setter.
         *
         * @param state
         */
        void setState(cellState_t state);


        // Getters
        /**
         * @brief Simple getter.
         *
         * @return the capacity of particles in the cell
         */
        unsigned int getNumParticleSlots();

        /**
         * @brief Simple getter.
         *
         * @param position - a particle's position
         * @retval nullptr - no particle was found at the specified @a position
         * @retval particle - a pointer to the particle at the slot number requested
         */
        Particle* getParticle(const unsigned int position);

        /**
         * @brief Simple getter.
         *
         * @return state
         */
        cellState_t getState();

        /**
         * @brief Simple getter.
         *
         * @return type
         */
        spacePointType_t getType();


        // Functions
        /**
         * @brief Deletes the reserved memory for a particle and sets the value to @a nullptr.
         * @param position - a particle's position
         */
        void deleteParticle(unsigned int position);

        /**
         * @brief Calculates the current type.
         */
        void updateType();



    private:
        cellState_t state; ///< The current state of this cell.
        unsigned int numParticleTypes; ///< The number of different fluid types available.
};


/**
  * @}
  */


#endif // CELL_HPP
