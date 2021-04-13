#include <stdio.h>

#include "game.hpp"

int main()
{
    Game* tetris = new Game( "Tétris" , 1440 , 660 ) ;
    
    tetris->launch_menu() ;
    
    delete( tetris ) ;

    return( 0 ) ;
}