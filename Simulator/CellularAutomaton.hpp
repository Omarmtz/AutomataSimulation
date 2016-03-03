/**
 * @file CellularAutomaton.hpp
 * @author Diego Rodríguez Boy
 * @brief CellularAutomaton template class.
 */


#ifndef CELLULARAUTOMATON_HPP
#define CELLULARAUTOMATON_HPP


#include <unordered_set>
#include "SpaceConfig.hpp"


/**
 * @ingroup Simulator
 * @{
 */


/**
 * @brief Template class for a 3D Cellular Automaton.
 */
template <class T, class S>
class CellularAutomaton
{
    public:
        // Getters
        const T* getConfig();
        spaceDimensions_t getDimensions();
        std::unordered_set<S> getStates();


        // Functions
        void transition();



    protected:
        // Attributes
        spaceDimensions_t dimensions; ///< Dimensions bounding this CA.
        std::unordered_set<S> states; ///< The states defined for this CA.
        T* lattice; ///< The lattice of cell covering a space defined by @a dimensions. Implementation is in charge of management.


        // Constructor
        /**
         * @brief Nullary constructor.
         */
        CellularAutomaton();

        /**
         * @brief Copy constructor.
         *
         * @param that - the CellularAutomaton to copy
         */
        CellularAutomaton(const CellularAutomaton& that);

        /**
         * @brief Move constructor.
         *
         * @param that - the rvalue to move
         */
        CellularAutomaton(CellularAutomaton&& that);

        /**
         * @brief Initializer constructor.
         *
         * @param dimensions - dimensions that define the lattice space
         * @param states - states defined for the CA
         */
        CellularAutomaton(spaceDimensions_t dimensions, std::unordered_set<S>& states);


        // Destructor
        /**
          * Destructor - default.
          */
        ~CellularAutomaton() = default;


        // Operators
        /**
         * @brief Copy operator.
         *
         * @param that - the CellularAutomaton to copy
         * @return reference to object copied
         */
        CellularAutomaton& operator =(const CellularAutomaton& that);

        /**
         * @brief Move operator.
         *
         * @param that - the rvalue to move
         * @return reference to object moved
         */
        CellularAutomaton& operator =(CellularAutomaton&& that);
};



// Constructors
template <class T, class S>
CellularAutomaton<T, S>::CellularAutomaton()
{
    this->dimensions = spaceDimensions_t();
    this->states = std::unordered_set<S>();
}



template <class T, class S>
CellularAutomaton<T, S>::CellularAutomaton(const CellularAutomaton &that)
{
    this->dimensions = that.dimensions;
    this->states = that.states;
}



template <class T, class S>
CellularAutomaton<T, S>::CellularAutomaton(CellularAutomaton&& that)
{
    this->dimensions = that.dimensions;

    this->states.erase();
    this->states.insert(that.states.begin(), that.states.end());

    that.dimensions = spaceDimensions_t();
    that.states.erase();
}



template <class T, class S>
CellularAutomaton<T, S>::CellularAutomaton(spaceDimensions_t dimensions, std::unordered_set<S>& states)
{
    this->dimensions = dimensions;
    this->states.insert(states.begin(), states.end());
}


// Operators
template <class T, class S>
CellularAutomaton<T, S>& CellularAutomaton<T, S>::operator =(const CellularAutomaton& that)
{
    if(this != &that)
    {
        this->dimensions = that.dimensions;
        this->states = that.states;
    }

    return *this;
}



template <class T, class S>
CellularAutomaton<T, S>& CellularAutomaton<T, S>::operator =(CellularAutomaton<T, S>&& that)
{
    if(this != &that)
    {
        this->dimensions = that.dimensions;
        this->states = that.states;

        that.dimensions = spaceDimensions_t();
        that.states.erase(that.states.begin(), that.states.end());
    }

    return *this;
}



// Getters
template <class T, class S>
spaceDimensions_t CellularAutomaton<T, S>::getDimensions()
{
    return this->dimensions;
}



template <class T, class S>
std::unordered_set<S> CellularAutomaton<T, S>::getStates()
{
    return this->states;
}


/**
  * @}
  */


#endif // CELLULARAUTOMATON_HPP
