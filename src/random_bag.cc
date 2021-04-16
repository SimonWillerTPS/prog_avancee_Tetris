#include "random_bag.hpp"

Random_bag:: Random_bag()
{
    srand( time( NULL )) ;
    fill() ;
}

void Random_bag:: fill()
{
    for( int i = 0 ; i < BAG_SIZE ; i ++ )
        numbers.push_back( i ) ;
}

int Random_bag:: draw()
{
    int index = rand() % numbers.size() ;
    int value = numbers[ index ] ;
    numbers.erase( numbers.begin() + index ) ;
    if( numbers.size() <= 0 )
        fill() ;
    return value ;
}