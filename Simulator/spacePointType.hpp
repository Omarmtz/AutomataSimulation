/**
 * @file spacePointType.hpp
 * @author Diego Rodríguez Boy
 * @brief Types of space points.
 */


#ifndef SPACEPOINTTYPE_HPP
#define SPACEPOINTTYPE_HPP


/**
 * @ingroup Simulator
 * @{
 */


/**
 * @brief Data type to classify space points by their (particle) contents.
 */
typedef int spacePointType_t;


/**
 * @brief Predefined space point types.
 */
enum spacePointType_e : spacePointType_t
{
    wall = -1, ///< This space point is a solid wall/object.    
    empty = 0, ///< There is nothing in this space point.
    cold = 1, ///< hot cell space point.
    hot = 2 ///< cold cell space point.
};


/**
  * @}
  */


#endif // SPACEPOINTTYPE_HPP
