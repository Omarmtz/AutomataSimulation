/**
 * @file SpaceConfig_CA.cpp
 * @author Diego Rodríguez Boy
 * @brief Implementation of the SpaceConfig_CA class.
 */


#include "SpaceConfig_CA.hpp"


// Constructors
/**
 * @details Initializes everything to 0.
 */
SpaceConfig_CA::SpaceConfig_CA() : SpaceConfig_CA(spaceDimensions_t(), nullptr)
{
}



SpaceConfig_CA::SpaceConfig_CA(const SpaceConfig_CA &that) : SpaceConfig(that)
{
    this->points = new SpacePointPtr_t[this->numPoints];

    for(dimension_t i = 0; i < this->numPoints; i++)
    {
        this->points[i] = SpacePointPtr_t(that.points[i]);
    }
}



SpaceConfig_CA::SpaceConfig_CA(SpaceConfig_CA&& that) : SpaceConfig(that)
{
    this->points = new SpacePointPtr_t[this->numPoints];

    for(dimension_t i = 0; i < this->numPoints; i++)
    {
        this->points[i] = SpacePointPtr_t(that.points[i]);
    }

    delete that.points;
}



SpaceConfig_CA::SpaceConfig_CA(const spaceDimensions_t dimensions, const Cell *lattice)
                               : SpaceConfig(dimensions)
{
    this->points = new SpacePointPtr_t[this->numPoints];

    for(dimension_t i = 0; i < this->numPoints; i++)
    {
        this->points[i] = SpacePointPtr_t(new Cell(lattice[i]));
    }
}



// Destructor
SpaceConfig_CA::~SpaceConfig_CA()
{
    delete[] this->points;
}



// Operators
SpaceConfig_CA& SpaceConfig_CA::operator =(const SpaceConfig_CA& that)
{
    if(this != &that)
    {
        SpaceConfig::operator =(that);

        delete[] this->points;
        this->points = new SpacePointPtr_t[this->numPoints];

        for(dimension_t i = 0; i < this->numPoints; i++)
        {
            this->points[i] = SpacePointPtr_t(that.points[i]);
        }
    }

    return *this;
}



SpaceConfig_CA& SpaceConfig_CA::operator =(SpaceConfig_CA&& that)
{
    if(this != &that)
    {
        SpaceConfig::operator =(that);

        delete[] this->points;
        this->points = new SpacePointPtr_t[this->numPoints];

        for(dimension_t i = 0; i < this->numPoints; i++)
        {
            this->points[i] = SpacePointPtr_t(that.points[i]);
        }

        delete[] that.points;
    }

    return *this;
}



// Getters
SpacePointPtr_t SpaceConfig_CA::getPoint(const coord_t x, const coord_t y, const coord_t z)
{
    dimension_t index = x;
    index += y * this->dimensions.x;
    index += z * this->dimensions.y * this->dimensions.x;

    return this->points[index];
}
