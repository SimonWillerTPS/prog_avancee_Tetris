#include <stdio.h>

#include "game.hpp"

int main()
{
    Game tetris( "Tétris" , 500 , 500 ) ;
    tetris.init() ;
    SDL_Delay(5000) ;
}