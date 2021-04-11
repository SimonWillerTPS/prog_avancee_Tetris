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
#define FPS 60
#define TICK_PER_FRAME 1000/FPS

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
        int             difficulty = 3 ;

        LTimer*         fps_timer ;
        LTimer*         cap_timer ;
        int             counted_frames = 0 ;
        float           avgFPS ;
        int             frame_Ticks ;
        int             down_counter = 0 ;

        int             fallenCounter = 0 ;
        SDL_Texture*    score_texture ;
        SDL_Texture*    level_texture ;
        SDL_Texture*    lines_texture ;
        TTF_Font*       font ;
        std::string     string_score ;
        std::string     string_level ;
        std::string     string_lines ;

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
        void            render_text() ;
        void            update_board() ;
        void            renderPiece( int type , int center_x , int center_y ) ;
        SDL_Texture*    load_texture( std::string path ) ;
} ;


#endif