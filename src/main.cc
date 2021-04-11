#include <stdio.h>

#include "game.hpp"

int main()
{
    Game tetris( "Tétris" , 750 , 750 ) ;
    if( tetris.init() )
        tetris.run() ;

    return( 0 ) ;
}