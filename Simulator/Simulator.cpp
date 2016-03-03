/**
 * @file Simulator.cpp
 * @author Diego Rodríguez Boy
 * @brief Implementation of the Simulator class.
 */


#include "Simulator.hpp"
#include "SpaceConfig_CA.hpp"


// Constructors
//Simulator::Simulator(const Model &parsedModel, const std::vector<fluidInitParams_t>& fluidInitParams)
Simulator::Simulator(const spaceDimensions_t dimensions, std::vector<fluidInitParams_t> fluidInitParams)
                     : simulator_CA(dimensions, fluidInitParams)
{
}



void Simulator::calculateNextConfig()
{
    simulator_CA.transition();
}



SpaceConfigPtr_t Simulator::getConfig()
{
    const spaceDimensions_t dims = simulator_CA.getDimensions();
    const Cell* config = simulator_CA.getConfig();

    return SpaceConfigPtr_t(new SpaceConfig_CA(dims, config));
}
