#ifndef KEY_HPP
#define KEY_HPP

#include <SDL2/SDL_ttf.h>

typedef enum Key
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
} Key ;

Key get_key( SDL_Event* event ) ;

#endif