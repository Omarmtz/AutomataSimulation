/**
 * @file Particle.cpp
 * @author Diego Rodríguez Boy
 * @brief Implementation of the Particle class.
 */


#include "Particle.hpp"
#include "Error/ErrorHandler.hpp"

int Particle::s_nIDGenerator = 1;
// Constructors
/**
 * @details Sets attributes to 0.
 */
Particle::Particle() : Particle(0, 0, 0)
{
    id = s_nIDGenerator++;
}



Particle::Particle(spacePointType_t type, mass_t mass, velocity_t velocity)
                   : type(type), mass(mass), velocity(velocity)
{
    id = s_nIDGenerator++;
}



// Setters
void Particle::setType(spacePointType_t type)
{
    this->type = type;
}



/**
 * @throws error_e::signError
 */
void Particle::setMass(mass_t mass)
{
    this->mass = mass;
}



void Particle::setVelocity(velocity_t velocity)
{
    this->velocity = velocity;
}



// Getters
spacePointType_t Particle::getType()
{
    return this->type;
}



mass_t Particle::getMass()
{
    return this->mass;
}



velocity_t Particle::getVelocity()
{
    return this->velocity;
}
