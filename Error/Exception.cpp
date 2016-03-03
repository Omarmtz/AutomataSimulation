/**
 * @file Exception.cpp
 * @author Diego Rodríguez Boy
 * @brief Implementation of Exception class.
 */


#include "Exception.hpp"


// Constructor
/**
 * @details Extracts the contents of the @ref errorString_t structure
 *          into a single line string.
 */
Exception::Exception(const errorString_t& errorString)
{
    this->message = errorString.code + ": " + errorString.description;
}



// Functions
const char* Exception::what()
{
    return message.c_str();
}
