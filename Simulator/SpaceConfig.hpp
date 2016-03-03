/**
 * @file SpaceConfig.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of the SpaceConfig abstract class.
 */


#ifndef SPACECONFIG_HPP
#define SPACECONFIG_HPP


#include <memory>
#include "SpacePoint.hpp"


/**
 * @ingroup Simulator
 * @{
 */


// Forward declaration.
class SpaceConfig;


/**
 * @brief A space coordinate.
 */
typedef unsigned int coord_t;


/**
 * @brief The size of a dimension.
 */
typedef coord_t dimension_t;


/**
 * @brief The dimensions of a 3D space.
 */
struct spaceDimensions_t
{
    dimension_t x;
    dimension_t y;
    dimension_t z;


    spaceDimensions_t() : spaceDimensions_t(0, 0, 0)
    {
    }


    spaceDimensions_t(const dimension_t x, const dimension_t y, const dimension_t z)
                      : x(x), y(y), z(z)
    {
    }
};


/**
 * @brief A smart pointer to a SpacePoint implementation.
 */
typedef std::shared_ptr<SpaceConfig> SpaceConfigPtr_t;


/**
 * @brief The SpaceConfig class is an abstract class for representing the configuration of a
 *        3D bounded space.
 */
class SpaceConfig
{
    public:
        // Getters
        /**
         * @brief Simple getter.
         *
         * @return dimensions
         */
        spaceDimensions_t getDimensions();

        /**
         * @brief Simple getter.
         *
         * @param x - coord in x
         * @param y - coord in y
         * @param z - coord in z
         * @return pointer to SpacePoint in (x, y, z)
         */
        virtual SpacePointPtr_t getPoint(const coord_t x, const coord_t y, const coord_t z) = 0;



    protected:
        // Attributes
        spaceDimensions_t dimensions; ///< Dimensions in which this space is bounded.
        dimension_t numPoints; ///< The number of points in this space. It equals the volume of @a dimensions.
        SpacePointPtr_t* points; ///< Points that are contained in this space. Management is left to implementation.


        // Constructors
        /**
         * @brief Nullary constructor.
         */
        SpaceConfig();

        /**
         * @brief Copy constructor.
         *
         * @param that - the SpaceConfig to copy
         */
        SpaceConfig(const SpaceConfig& that);

        /**
         * @brief Move constructor.
         *
         * @param that - the rvalue to move
         */
        SpaceConfig(SpaceConfig&& that);

        /**
         * @brief Initialization constructor.
         *
         * @param dimensions - dimensions that will bind this space
         */
        SpaceConfig(const spaceDimensions_t dimensions);


        // Destructor
        /**
          * @brief Destructor - default.
          */
        ~SpaceConfig() = default;


        // Operators
        /**
         * @brief Copy operator.
         *
         * @param that - the SpaceConfig to copy
         * @return reference to object copied
         */
        SpaceConfig& operator =(const SpaceConfig& that);

        /**
         * @brief Move operator.
         *
         * @param that - the rvalue to move
         * @return reference to object moved
         */
        SpaceConfig& operator =(SpaceConfig&& that);
};


/**
 * @}
 */


#endif // SPACECONFIG_HPP
