#ifndef INPUT_HPP
#define INPUT_HPP

#include "game.hpp"

#include <SDL2/SDL.h>

enum Keys
{
    KEY_UP ,
    KEY_DOWN ,
    KEY_LEFT ,
    KEY_RIGHT ,
    KEY_STORE ,
    KEY_ENTER ,
    KEY_SPACE ,
    KEY_PAUSE ,
    KEY_QUIT ,
    KEY_NULL
} ;

Keys get_input( SDL_Event &event ) ;

#endif