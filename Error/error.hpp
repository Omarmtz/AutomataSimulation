/**
 * @file error.hpp
 * @author Diego Rodríguez Boy
 * @brief Basic user-defined error data types and structures.
 */


#ifndef ERROR_HPP
#define ERROR_HPP


#include <string>


/**
 * @ingroup Error
 * @{
 */


/**
 * @brief Available error types.
 */
enum class error_e
{
    cellStateError, ///< The cell has taken an illegal Cell::state value - i.e. a state value undefined for the CA.
    cudaError, ///< An error in the GPU (graphic card) occurred.
    fileNotFoundError, ///< An attempt was made to open a nonexisting file.
    indexError, ///< An attempt was made to access an element out of bounds.
    outOfMemoryError, ///< The system ran out of memory.
    nullptrError, ///< A nullptr was passed instead of a pointer to a valid object.
    signError, ///< A wild negative number appeared where a positive number was expected.
    unkownError ///< What did you do? Call 911!
};



/**
 * @brief Container for the human-readable description
 *        of an @ref error_e enumerator.
 */
struct errorString_t
{
    std::string code; ///< The error code.
    std::string description; ///< A description of what the error code stands for.

    /**
     * @brief Default constructor.
     */
    errorString_t() : errorString_t("", "") {}

    /**
     * @brief Initialization constructor.
     *
     * @param code - the error code string representation
     * @param description - description for this particular error code
     */
    errorString_t(const std::string& code, const std::string& description)
                  : code(code), description(description) {}
};


/**
 * @}
 */


#endif // ERROR_HPP
