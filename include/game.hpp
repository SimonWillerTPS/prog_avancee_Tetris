#ifndef GAME_HPP
#define GAME_HPP

#include "usefull_functions.hpp"

/**
 * @file    game.hpp
 * @brief   
 * @authors Simon Willer & Luca Scimone
 */

class Game
{
    private :
        SDL_Renderer*   renderer ;
        SDL_Window*     window ;
        std::string     title ;
        int             win_height ;
        int             win_width ;

    public :
        Game() ;
        Game( std::string title , int win_height , int win_width ) ;
        ~Game() ;
        int init() ;
} ;

#endif