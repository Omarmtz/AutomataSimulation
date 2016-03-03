/**
 * @file Simulator_Interface.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of the Simulator_Interface interface.
 */

#ifndef SIMULATOR_INTERFACE_HPP
#define SIMULATOR_INTERFACE_HPP


#include "SpaceConfig.hpp"


/**
 * @ingroup Simulator
 * @{
 */


/**
 * @brief The interface Simulator_Interface defines the behaviour of the Simulator class.
 */
class Simulator_Interface
{
    public:
        virtual void calculateNextConfig() = 0;
        virtual SpaceConfigPtr_t getConfig() = 0;
};


/**
 * @}
 */


#endif // SIMULATOR_INTERFACE_HPP
