/**
 * @file Simulator.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of the Simulator class.
 */


#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP


#include "Simulator_CA.hpp"
#include "Simulator_Interface.hpp"


/**
 * @ingroup Simulator
 * @{
 */


class Simulator : public Simulator_Interface
{
    public:
        Simulator() = default;
        //Simulator(const Model& parsedModel, const std::vector<fluidInitParams_t>& fluidInitParams);
        Simulator(const spaceDimensions_t dimensions, std::vector<fluidInitParams_t> fluidInitParams);

        void calculateNextConfig();
        SpaceConfigPtr_t getConfig();



    private:
        Simulator_CA simulator_CA;
};


/**
 * @}
 */


#endif // SIMULATOR_HPP
