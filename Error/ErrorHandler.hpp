/**
 * @file ErrorHandler.hpp
 * @author Diego Rodríguez Boy
 * @brief Definition of ErrorHandler class.
 */


#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP


#include <fstream>
#include <map>
#include "error.hpp"
#include "Exception.hpp"


/**
  * @ingroup Error
  * @{
  */


#ifdef DEBUG
    /**
      * @brief If the DEBUG symbol is defined, "x" is compiled/executed;
      *        it's ignored otherwise.
      * @param x - code to be conditionally included
      */
    #define DEBUG_STUB(x) { x; }
#else
    #define DEBUG_STUB(x)
#endif


/**
 * @brief The ErrorHandler Singleton.
 *
 * @details It is in charge of logging and managing errors system-wide.
 *
 * @todo DEBUG_STUB macro is not showing in documentation.
 */
class ErrorHandler
{
    public:
        // Destructor
        /**
          * @brief Destructor.
          */
        ~ErrorHandler();


        // Functions
        /**
         * @brief Ensures that the supplied condition is met.
         *
         * @param condition - condition to check
         * @param error - error code to be issued
         * @param details - detailed info about the condition being checked
         */
        static void assert(bool condition, error_e error, std::string details);



    private:
        // Attributes
        static ErrorHandler singletonInstance; ///< The singleton ErrorHandler object; it is created when system is started.

        const std::string fileName = "tt_2013_b032.error.log"; ///< Error log filename.

        std::map<error_e, errorString_t> errorDictionary; ///< Dictionary between enumerated error codes and their string representation.
        std::ofstream logFile; ///< Output file stream where error details are logged.


        // Constructors
        /**
         * @brief Singleton constructor.
         */
        ErrorHandler();
        ErrorHandler(const ErrorHandler&) = delete;
        ErrorHandler(ErrorHandler&&) = delete;


        // Operators
        ErrorHandler& operator =(const ErrorHandler&) = delete;
        ErrorHandler& operator =(ErrorHandler&&) = delete;


        // Functions
        /**
         * @brief Initializes the errorDictionary.
         */
        void initErrorDictionary();

        /**
         * @brief Logs in logFile the errors reported to this module.
         *
         * @param error - error code reported
         * @param details - additional error info
         */
        void log(error_e error, std::string details);

        /**
         * @brief Propagates the error reported through an Exception.
         *
         * @param error - error code reported
         */
        void propagateError(error_e error);
};


/**
 * @}
 */


#endif // ERRORHANDLER_HPP
