/**
 * @file ErrorHandler.cpp
 * @author Diego Rodríguez Boy
 * @brief Implementation of ErrorHandler class.
 */


#include <ctime>
#include <iostream>
#include "ErrorHandler.hpp"


//Data members
ErrorHandler ErrorHandler::singletonInstance;



// Constructor
/**
 * @details It attempts to open the file specified by ErrorHandler::fileName;
 *          if it fails, the log will be written to std::cerr.
 *          Then, it initializes the ErrorHandler::errorDictionary.
 */
ErrorHandler::ErrorHandler()
{
    // Open log file in output-append mode.
    this->logFile.open(this->fileName, std::ios::out | std::ios::app);

    // If log file was not opened successfully, notify user that
    // errors will be written to std::err instead of log file.
    if(this->logFile.fail())
    {
        std::cerr << "The log file \"" << this->fileName <<
                     "\" couldn't be opened. Errors will be "
                     "written to std::cerr instead." << std::endl;
    }

    // Populate the error dictionary.
    this->initErrorDictionary();
}



// Destructor
/**
 * @details Close ErrorHandler::logFile if it was opened successfully.
 */
ErrorHandler::~ErrorHandler()
{
    // Close log file.
    this->logFile.close();
}



// Functions
/**
 * @details Checks whether the condition is fulfilled.
 *          - If it is, nothing happens.
 *          - If it's not:
 *              -# The specified error and the details supplied are logged.
 *              -# The error is propagated.
 */
void ErrorHandler::assert(bool condition, error_e error, std::string details)
{
    if(condition)
    {
        // Condition fullfilled, mission acomplished!
        // No further action is expected.
    }
    else
    {
        // Condition NOT fullfilled, better luck next time.
        singletonInstance.log(error, details);
        singletonInstance.propagateError(error);
    }
}



void ErrorHandler::initErrorDictionary()
{
    error_e key;
    errorString_t value;
    std::pair<error_e, errorString_t> key_value;

    key = error_e::cellStateError;
    value.code = "cellStateError";
    value.description = "The cell has taken an illegal Cell::state value - i.e. a state value undefined for the CA.";
    key_value = std::make_pair(key, value);
    this->errorDictionary.insert(this->errorDictionary.end(), key_value);

    key = error_e::cudaError;
    value.code = "cudaError";
    value.description = "An error in the GPU (graphic card) occurred.";
    key_value = std::make_pair(key, value);
    this->errorDictionary.insert(this->errorDictionary.end(), key_value);

    key = error_e::fileNotFoundError;
    value.code = "fileNotFoundError";
    value.description = "An attempt was made to open a nonexisting file.";
    key_value = std::make_pair(key, value);
    this->errorDictionary.insert(this->errorDictionary.end(), key_value);

    key = error_e::indexError;
    value.code = "indexError";
    value.description = "An attempt was made to access an element out of bounds.";
    key_value = std::make_pair(key, value);
    this->errorDictionary.insert(this->errorDictionary.end(), key_value);

    key = error_e::nullptrError;
    value.code = "nullptrError";
    value.description = "A nullptr was passed instead of a pointer to a valid object.";
    key_value = std::make_pair(key, value);
    this->errorDictionary.insert(this->errorDictionary.end(), key_value);

    key = error_e::outOfMemoryError;
    value.code = "outOfMemoryError";
    value.description = "The system ran out of memory.";
    key_value = std::make_pair(key, value);
    this->errorDictionary.insert(this->errorDictionary.end(), key_value);

    key = error_e::signError;
    value.code = "signError";
    value.description = "A wild negative number appeared where a positive number was expected.";
    key_value = std::make_pair(key, value);
    this->errorDictionary.insert(this->errorDictionary.end(), key_value);

    key = error_e::unkownError;
    value.code = "unkownError";
    value.description = "What did you do? Call 911!";
    key_value = std::make_pair(key, value);
    this->errorDictionary.insert(this->errorDictionary.end(), key_value);
}



void ErrorHandler::log(error_e error, std::string details)
{
    // Get current date and time.
    time_t currentTimeInSeconds = time(0);
    const char* dateTimeString = ctime(&currentTimeInSeconds);

    // Retrieve error information from dictionary.
    errorString_t errorString = this->errorDictionary[error];

    // Create message to log.
    std::string logMsg = "";
    logMsg += dateTimeString;

    for(int i = logMsg.length(); i > 0; i--)
    {
        logMsg += "-";
    }

    logMsg += "\n";
    logMsg += "Error: " + errorString.code + "\n";
    logMsg += "Description: " + errorString.description + "\n";
    logMsg += "Details: " + details + "\n\n\n";

    // If log file is writable.
    if(this->logFile.good())
    {
        // Log message.
        this->logFile << logMsg;
        this->logFile.flush();
    }
    else
    {
        // Output to std::cerr.
        std::cerr << logMsg;
    }
}



/**
 * @details Throws an Exception with its appropiate description.
 *
 * @todo Decide, based on future @ref error_e members,
 *       if every error code should throw an Exception.
 */
void ErrorHandler::propagateError(error_e error)
{
    throw Exception(this->errorDictionary[error]);
}
