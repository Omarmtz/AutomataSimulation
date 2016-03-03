/**
 * @file Exception.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of Exception class.
 */


#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <exception>
#include "error.hpp"


/**
  * @ingroup Error
  * @{
  */

/**
 * @brief The custom exception class used system-wide.
 */
class Exception : public std::exception
{
    public:
        // Constructors
        Exception() = delete;

        /**
         * @brief Default copy constructor.
         */
        Exception(const Exception&) = default;

        /**
          * @brief Degault move constructor.
          */
        Exception(Exception&&) = default;

        /**
         * @brief Exception constructor. Initializes the exception message.
         *
         * @param errorString - structure containing exception info to be issued
         */
        Exception(const errorString_t& errorString);


        // Destructor
        /**
          * @brief Default destructor.
          */
        ~Exception() = default;


        // Operators
        Exception& operator =(const Exception&) = delete;
        Exception& operator =(Exception&&) = delete;


        // Functions
        /**
         * @brief Implementation of std::exception::what() function.
         *
         * @return a message containing "what" caused the exception
         */
        const char* what();



    private:
        std::string message; ///< Message containing exception info.
};


/**
 * @}
 */


#endif // EXCEPTION_H
