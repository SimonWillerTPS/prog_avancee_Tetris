#include <stdio.h>

#include "game.hpp"

int main()
{
    Game tetris( "Tétris" , 750 , 750 ) ;
    tetris.init() ;
    tetris.run() ;
}