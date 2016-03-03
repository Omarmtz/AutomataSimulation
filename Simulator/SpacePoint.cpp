/**
 * @file SpacePoint.cpp
 * @author Diego Rodríguez Boy
 * @brief Implementation of the SpacePoint abstract class.
 */


#include "SpacePoint.hpp"
#include "Error/ErrorHandler.hpp"


// Constructors
/**
 * @details It set's @a numParticles to 0 and @a type to spacePointType_e::empty.
 */
SpacePoint::SpacePoint() : SpacePoint(0, spacePointType_e::empty) {}



SpacePoint::SpacePoint(const SpacePoint& that)
                       : numParticleSlots(that.numParticleSlots), type(that.type)
{
    this->particleSlots = new Particle*[that.numParticleSlots];

    // Copy values and reset to nullptr
    for(unsigned int i = 0; i < numParticleSlots; i++)
    {
        if(that.particleSlots[i] != nullptr)
        {
            this->particleSlots[i] = new Particle;
        }

        this->particleSlots[i] = that.particleSlots[i];
    }
}



SpacePoint::SpacePoint(SpacePoint&& that)
                       : numParticleSlots(that.numParticleSlots), type(that.type)
{
    this->particleSlots = new Particle*[that.numParticleSlots];

    // Copy values and reset to nullptr
    for(unsigned int i = 0; i < numParticleSlots; i++)
    {
        if(that.particleSlots[i] != nullptr)
        {
            this->particleSlots[i] = new Particle;
            this->particleSlots[i] = that.particleSlots[i];
            that.particleSlots[i] = nullptr;
        }
    }

    that.type = 0;
    that.numParticleSlots = 0;
}


#include <iostream>
using namespace std;

/**
 * @throws error_e::signError
 */
SpacePoint::SpacePoint(const unsigned int numParticles, const spacePointType_t type)
                       : numParticleSlots(numParticles), type(type)
{
    // Create Particle* array of size "numParticles"
    this->particleSlots = new Particle*[numParticles];

    for(unsigned int i = 0; i < numParticles; i++)
    {
        this->particleSlots[i] = nullptr;
    }
}



// Destructor
SpacePoint::~SpacePoint()
{
    for(unsigned int i = 0; i < this->numParticleSlots; i++)
    {
        if(this->particleSlots[i] != nullptr)
        {
            //delete this->particleSlots[i];
        }
    }

    delete[] this->particleSlots;
}



// Operators
SpacePoint& SpacePoint::operator =(const SpacePoint& that)
{
    if(this != &that)
    {
        // Deallocate memory
        for(unsigned int i = 0; i < this->numParticleSlots; i++)
        {
            if(this->particleSlots[i] != nullptr)
            {
                //delete this->particleSlots[i];
            }
        }

        delete[] this->particleSlots;

        // Copy attributes
        this->numParticleSlots = that.numParticleSlots;
        this->type = that.type;

        this->particleSlots = new Particle*[that.numParticleSlots];

        for(unsigned int i = 0; i < numParticleSlots; i++)
        {
            if(that.particleSlots[i] != nullptr)
            {
                this->particleSlots[i] = new Particle;
            }

            this->particleSlots[i] = that.particleSlots[i];
        }
    }

    return *this;
}



SpacePoint& SpacePoint::operator =(SpacePoint&& that)
{
    if(this != &that)
    {
        // Deallocate memory
        for(unsigned int i = 0; i < this->numParticleSlots; i++)
        {
            if(this->particleSlots[i] != nullptr)
            {
                delete this->particleSlots[i];
            }
        }

        delete[] this->particleSlots;

        // Copy attributes
        this->numParticleSlots = that.numParticleSlots;
        this->type = that.type;

        this->particleSlots = new Particle*[that.numParticleSlots];

        // Copy values and reset to nullptr
        for(unsigned int i = 0; i < numParticleSlots; i++)
        {
            if(that.particleSlots[i] != nullptr)
            {
                this->particleSlots[i] = new Particle;
                this->particleSlots[i] = that.particleSlots[i];

                delete that.particleSlots[i];
                that.particleSlots[i] = nullptr;
            }
            else
            {
                this->particleSlots[i] = nullptr;
            }
        }

        // Reset values
        that.type = 0;
        that.numParticleSlots = 0;
    }

    return *this;
}
