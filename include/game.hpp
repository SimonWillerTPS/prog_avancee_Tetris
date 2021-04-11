#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

// #include "input.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "shape.hpp"
#include "timer.hpp"

#define SQUARE_DIM 30
#define FPS 24

class Board ;

typedef enum Keys
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
} Keys ;

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
        SDL_Event       event ;
        Keys            pressed_key = KEY_NULL ;
        LTimer*         timer ;
        int             fallenCounter = 0 ;

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
        void            run() ;
        void            use_key() ;
        void            get_input() ;
        void            render_board() ;
        void            render_square( int pos_x , int pos_y , int color ) ;
        void            render_holded() ;
        void            render_next_piece() ;
        void            update_board() ;
        void            renderPiece( int type , int center_x , int center_y ) ;
        SDL_Texture*    load_texture( std::string path ) ;
} ;


#endif