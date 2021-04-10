#ifndef GAME_HPP
#define GAME_HPP

#include "input.hpp"
#include "board.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game
{
    private :

        Board*          board ;
        SDL_Renderer*   renderer ;
        SDL_Window*     window ;
        SDL_Surface*    surface ;
        SDL_Texture*    texture ;
        std::string     title ;
        int             width ;
        int             height ;
        bool            running ;


    public :

        Game( std::string title , int width , int height ) ;
        ~Game() ;

        SDL_Window*     get_window() ;
        SDL_Renderer*   get_renderer() ;
        SDL_Surface*    get_surface() ;
        SDL_Texture*    get_texture() ;
        std::string     get_title() ;
        int             get_width() ;
        int             get_height() ;
        bool            is_running() ;

        bool            init() ;
        SDL_Texture*    load_texture( std::string path ) ;
        
} ;


#endif