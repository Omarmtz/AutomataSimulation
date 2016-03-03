/**
 * @file Simulator_CA.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of the Simulator_CA class.
 */


#ifndef SIMULATOR_CA_HPP
#define SIMULATOR_CA_HPP


#include <vector>
#include "fluidInitParams.hpp"
#include "Cell.hpp"
#include "CellularAutomaton.hpp"


/**
 * @ingroup Simulator
 * @{
 */


/**
 * @brief The Simulator_CA class is in charge of the simulation thorugh a
 *        Cellular Automaton, therefore it implements the CellularAutomaton
 *        template. The transition function is parallelized in CUDA.
 *
 * @todo Document CA transition rule (LaTeX formula).
 * @todo transition_CUDA()
 */
class Simulator_CA : public CellularAutomaton<Cell, cellState_t>
{
    public:
        // Constructors
        /**
         * @brief Nullary constructor.
         */
        Simulator_CA();

        /**
         * @brief Copy constructor.
         *
         * @param that - the Simulator_CA to copy
         */
        Simulator_CA(const Simulator_CA& that);

        /**
         * @brief Move constructor.
         *
         * @param that - the rvalue to move
         */
        Simulator_CA(Simulator_CA&& that);

        /**
         * @brief Initialization constructor.
         *
         * @param parsedModel - a Model loaded and transformed by the ModelLoader module to be used by the simulator
         * @param fluidInitParams - a vector with the initialization parameters for the fluids that are to be simulated
         */
        //Simulator_CA(const Model& parsedModel, const std::vector<fluidInitParams_t>& fluidInitParams);
        Simulator_CA(const spaceDimensions_t dimensions, std::vector<fluidInitParams_t> fluidInitParams);


        // Destructor
        /**
          *@brief Destructor.
          */
        ~Simulator_CA();


        // Operators
        /**
         * @brief Copy operator - default.
         *
         * @param that - the Simulator_CA to copy
         * @return reference to object copied
         */
        Simulator_CA& operator =(const Simulator_CA& that);

        /**
         * @brief Move operator.
         *
         * @param that - the rvalue to move
         * @return reference to object moved
         */
        Simulator_CA& operator =(Simulator_CA&& that);


        // Getters
        /**
         * @brief Gets a copy of the CA's configuration at the current timestep @a t.
         *
         * @return an unchangeable copy of the CA's cells
         */
        const Cell* getConfig();


        // Functions
        /**
         * @brief Applies the transition rule defined for this CA to every cell simultaneously.
         *
         * @details This function calls the CUDA kernel transition_CUDA() in order to apply the
         *          transition rule parallel in every cell of the @a lattice. While transition_CUDA()
         *          is in charge of the calculations, this function does the memory management between
         *          the CPU and the GPU.
         *          The transition rule for this cellular automaton is defined as:
         *          - *transition rule description*
         */
        void transition();

        void transition_CUDA();
        void init();



    private:
        // Attributes
        Cell* lattice_d; ///< The lattice used by the GPU as input for the transition rule.
        Cell* buffer_d; ///< The output lattice of the GPU's transition rule application.
        std::vector<fluidInitParams_t> fluidInitParams; ///< The parameters for the fluids that are to be simulated at injection time.
        unsigned int numFluids; ///< The number of fluids interacting with the static mixer.
        unsigned int numCells; ///< The total number of cells in the CA's lattice.
};


/**
 * @}
 */


#endif // SIMULATOR_CA_HPP
