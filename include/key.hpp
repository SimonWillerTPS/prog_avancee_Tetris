#ifndef KEY_HPP
#define KEY_HPP

/**
 * @file    key.hpp
 * @brief   This files defines the Key type and the function to get one.
 * @authors Luca Scimone & Simon Willer
 */

#include <SDL2/SDL_ttf.h>

/**
 * @typedef Key
 * @enum    Key
 * @brief   Type that represents the key used to play the game.
 */
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

/**
 * @brief   Returns the keyboard input from the player.
 * @param   event SDL_event to get the keyboard input.
 */
Key get_key( SDL_Event* event ) ;

#endif