#include <stdio.h>

#include "game.hpp"

int main()
{
    Game* tetris = new Game( "Tétris" , 1500 , 750 ) ;
    
    tetris->launch_menu() ;
    
    delete( tetris ) ;

    return( 0 ) ;
}