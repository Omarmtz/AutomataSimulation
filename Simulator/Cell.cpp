/**
 * @file Cell.cpp
 * @author Diego Rodríguez Boy
 * @brief Implementation of the Cell class.
 */


#include "Cell.hpp"
#include "Error/ErrorHandler.hpp"


// Constructors
/**
 * @details Initializes @a type to spacePointType_e::empty and everything else to 0.
 */
Cell::Cell() : Cell(0, 0, spacePointType_e::empty, 0){}



Cell::Cell(const unsigned int numParticles, const spacePointType_t type,
     const cellState_t state, const unsigned int numParticleTypes)
     :  SpacePoint(numParticles, type), state(state), numParticleTypes(numParticleTypes)
{
}



// Setters
/**
 * @details If the value of @a particle is @a nullptr, the particle is deleted.
 *          This happens when the particle at @a position is moved to another Cell
 *          and there is no particle moved here to take its place.
 */
void Cell::setParticle(Particle* particle, const unsigned int position)
{
    if(particle == nullptr)
    {
        if(this->particleSlots[position] != nullptr)
        {
            delete this->particleSlots[position];
            this->particleSlots[position] = nullptr;
        }
    }
    else
    {
        this->particleSlots[position] = new Particle(*particle);
    }
}



void Cell::setState(cellState_t state)
{
    this->state = state;
}



// Getters
unsigned int Cell::getNumParticleSlots()
{
    return this->numParticleSlots;
}



Particle* Cell::getParticle(const unsigned int position)
{
    return this->particleSlots[position];
}



cellState_t Cell::getState()
{
    return this->state;
}



spacePointType_t Cell::getType()
{
    this->updateType();

    return this->type;
}



// Functions
void Cell::deleteParticle(unsigned int position)
{
    delete this->particleSlots[position];
    this->particleSlots[position] = nullptr;
}


#include <iostream>
/**
 * @details Type is chosen by the following rule:
 *              - If current type is spacePointType_e::wall, no change is made.
 *              - Else if the cell doesn't contain particles, spacePointType_e::empty is the value.
 *              - Else, the type is that of the most number of particles present.
 */
void Cell::updateType()
{
    // If type is "wall", do nothing.
    if(this->type == spacePointType_e::wall)
    {
        return;
    }
    else
    {
        unsigned int* typeQuantities = new unsigned int[this->numParticleTypes];
        bool noParticles = true;

        for(unsigned int i = 0; i < this->numParticleTypes; i++)
        {
            typeQuantities[i] = 0;
        }

        // Count number of particles of each fluid type.
        for(unsigned int i = 0; i < this->numParticleSlots; i++)
        {
            Particle* currentParticle = this->particleSlots[i];

            if(currentParticle != nullptr)
            {
                spacePointType_t currentType = currentParticle->getType() - 1;
                typeQuantities[currentType]++;

                noParticles = false;
            }
        }

        // If no particles were found, type is "empty".
        if(noParticles)
        {
            this->type = spacePointType_e::empty;
        }
        else
        {
            unsigned int maxCount = 0;
            unsigned int maxCountIndex = 0;

            // Type is that of most occurrences.
            for(unsigned int i = 0; i < this->numParticleTypes; i++)
            {
                if(typeQuantities[i] > maxCount)
                {
                    maxCount = typeQuantities[i];
                    maxCountIndex = i;
                }
            }

            this->type = maxCountIndex + 1;
        }

        delete[] typeQuantities;
    }
}
