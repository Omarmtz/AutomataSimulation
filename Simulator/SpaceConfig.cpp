/**
 * @file SpaceConfig.cpp
 * @author Diego Rodríguez Boy
 * @brief Implementation of the SpaceConfig abstract class.
 */


#include "SpaceConfig.hpp"


// Constructors
/**
 * @details It sets dimensions to 0.
 */
SpaceConfig::SpaceConfig() : SpaceConfig(spaceDimensions_t())
{
}



SpaceConfig::SpaceConfig(const SpaceConfig& that)
{
    this->dimensions = that.dimensions;
    this->numPoints = that.numPoints;
}



SpaceConfig::SpaceConfig(SpaceConfig&& that)
{
    this->dimensions = that.dimensions;
    this->numPoints = that.numPoints;

    that.dimensions = spaceDimensions_t();
    that.numPoints = 0;
}



SpaceConfig::SpaceConfig(const spaceDimensions_t dimensions)
                         : dimensions(dimensions)
{
    this->numPoints = dimensions.x * dimensions.y * dimensions.z;
}



// Operators
SpaceConfig& SpaceConfig::operator =(const SpaceConfig& that)
{
    if(this != &that)
    {
        this->dimensions = that.dimensions;
        this->numPoints = that.numPoints;
    }

    return *this;
}



SpaceConfig& SpaceConfig::operator =(SpaceConfig&& that)
{
    if(this != &that)
    {
        this->dimensions = that.dimensions;
        this->numPoints = that.numPoints;

        that.dimensions = spaceDimensions_t();
        that.numPoints = 0;
    }

    return *this;
}



// Getters
spaceDimensions_t SpaceConfig::getDimensions()
{
    return dimensions;
}
