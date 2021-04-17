#ifndef RANDOM_BAG_HPP
#define RANDOM_BAG_HPP

/**
 * @file    random_bag.hpp
 * @brief   Defines the Random_bag class.
 * @authors Luca Scimone & Simon Willer
 */

#include <iostream>
#include <time.h>
#include <vector>

#define BAG_SIZE    7 /**< @def Number of elements in the bag */
#define VALUE_RANGE 7 /**< @def Range of the values of the bag's elements. */

/**
 * @class   Random_bag
 * @brief   This class is used to improve the random apparition of the Tetris
 *          pieces. It is inspired by the real game.
 */
class Random_bag
{
    private :
        std::vector<int> numbers ; /**< Vector to store the bag's elements. */

    public :
        /**
         * @brief   Initiates a random bag and sets the randomness seed, then
         *          fills the bag.
         */
        Random_bag() ;

        /**
         * @brief   Fills the bag with all the value in the VALUE_RANGE.
         */
        void fill() ;
        
        /**
         * @brief   Returns a random value from the values in the bag, and
         *          takes it away from the bag.
         */
        int draw() ;
} ;

#endif