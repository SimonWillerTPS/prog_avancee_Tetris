#ifndef USEFULL_FUNCTIONS_HPP
#define USEFULL_FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "game.hpp"

/**
 * @brief	Prints an error message in the error output and exits the
 * 			program with the code 2.
 * @param 	str string to print.
 */
void error ( std::string str ) ;

/**
 * @brief	Read an integer in a string.
 * 
 * Uses the function strtol to convert a string to an integer
 * and tests the case where the int to convert is 0. If the function
 * does not succeed to read an integer, it quits the program with
 * the function "usage".
 * 
 * @param	str string where to read the integer.
 * @return	integer read in the string
 */
int my_strtol ( std::string str ) ;

#endif