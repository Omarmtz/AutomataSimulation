/**
 * @file SpaceConfig_CA.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of the SpaceConfig_CA class.
 */


#ifndef SPACECONFIG_CA_HPP
#define SPACECONFIG_CA_HPP


#include "Cell.hpp"
#include "SpaceConfig.hpp"


/**
 * @ingroup Simulator
 * @{
 */


/**
 * @brief The SpaceConfig_CA class is an implementation of the SpaceConfig abstract
 *        class for CellularAutomata.
 */
class SpaceConfig_CA : public SpaceConfig
{
    public:
        // Constructor
        /**
         * @brief Nullary constructor.
         */
        SpaceConfig_CA();

        /**
         * @brief Copy constructor.
         *
         * @param that - the SpaceConfig_CA to copy
         */
        SpaceConfig_CA(const SpaceConfig_CA& that);

        /**
         * @brief Move constructor.
         *
         * @param that - the rvalue to move
         */
        SpaceConfig_CA(SpaceConfig_CA&& that);

        /**
         * @brief Initialization constructor.
         *
         * @param dimensions - dimensions of the CA
         * @param lattice - the cells (points) in the CA
         * @param numCells - number of cells that are contained in lattice
         */
        SpaceConfig_CA(const spaceDimensions_t dimensions, const Cell* lattice);


        // Destructor
        /**
          * @brief Destructor.
          */
        ~SpaceConfig_CA();


        // Operators
        /**
         * @brief Copy operator.
         *
         * @param that - the SpaceConfig_CA to copy
         * @return reference to object copied
         */
        SpaceConfig_CA& operator =(const SpaceConfig_CA& that);

        /**
         * @brief Move operator.
         *
         * @param that - the rvalue to move
         * @return reference to object moved
         */
        SpaceConfig_CA& operator =(SpaceConfig_CA&& that);


        // Getters
        SpacePointPtr_t getPoint(const coord_t x, const coord_t y, const coord_t z);
};


/**
 * @}
 */


#endif // SPACECONFIG_CA_HPP
