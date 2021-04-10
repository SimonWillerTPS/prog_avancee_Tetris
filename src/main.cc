#include <stdio.h>

#include "game.hpp"

int main()
{
    Game tetris( "Tétris" , 500 , 900 ) ;
    tetris.init() ;
    tetris.run() ;
}