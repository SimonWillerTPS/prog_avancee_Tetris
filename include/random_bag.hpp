#ifndef RANDOM_BAG_HPP
#define RANDOM_BAG_HPP

#include <iostream>
#include <time.h>
#include <vector>

#define BAG_SIZE 7
#define VALUE_RANGE 7

class Random_bag
{
    private :
        std::vector<int> numbers ;

    public :
        Random_bag() ;
        void fill() ;
        int draw() ;
} ;

#endif