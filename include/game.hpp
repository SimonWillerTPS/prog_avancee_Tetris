#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "board.hpp"
#include "choice.hpp"
#include "key.hpp"
#include "menu.hpp"
#include "session.hpp"

class Game
{
    private :

        // SDL :
        SDL_Renderer* renderer ;
        SDL_Window*   window ;
        TTF_Font*     font ;

        // Menu :
        Menu* menu ;

        // Sessions :
        Session* session_player ;
        Session* session_IA ;

        // Attributes :
        std::string win_title ;
        int         win_width ;
        int         win_height ;
        int         starting_level = 0 ;
        int         tile_size = 30 ;
        bool        running ;

    public :

        // Constructor, destructor :
        Game( std::string title , int width , int height ) ;
        ~Game() ;

        // Accessors :

        // Methods :
            // SDL :
        bool init_SDL() ;
        void close_SDL() ;
            // Game itself :
        int  launch_menu() ;
        bool launch_marathon() ;
        bool launch_battle() ;
} ;

#endif