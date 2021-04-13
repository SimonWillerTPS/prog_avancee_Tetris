#ifndef SESSION_HPP
#define SESSION_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "board.hpp"
#include "key.hpp"
#include "pieces.hpp"
#include "shape.hpp"
#include "timer.hpp"

#define FPS 60
#define TICK_PER_FRAME 1000/FPS

class Board ;

class Session
{
    private :

        // Timers :
        LTimer* fps_timer ;
        LTimer* cap_timer ;

        // Attributes for renderer coord. and sizes :
        int orig_x ;
        int orig_y ;
        int width ;
        int height ;
        int tile_size ;

        // SDL :
            // Given by Game :
        SDL_Renderer* renderer ;
        SDL_Event*    event ;
        TTF_Font*     font ;
            // Local :
        SDL_Surface* score_surface ;
        SDL_Surface* level_surface ;
        SDL_Surface* lines_surface ;    
        SDL_Texture* score_texture ;
        SDL_Texture* level_texture ;
        SDL_Texture* lines_texture ;
        SDL_Rect rectangle ;
        SDL_Rect level_rect ;
        SDL_Rect lines_rect ;
        SDL_Rect score_rect ;
        
        // Board :
        Board* board ;

        // FPS management :
        float avgFPS ;
        int   counted_frames = 0 ;
        int   frame_Ticks ;

        // Strings to render at screen :
        std::string     string_score ;
        std::string     string_level ;
        std::string     string_lines ;

        // Key to get input :
        Key pressed_key ;

        // Other attributes :
        bool running ;
        int  difficulty = 3 ;
        int  down_counter = 0 ;
        int  fallenCounter = 0 ;
        int  starting_level ;

    public :

        // Constructor, destructor :
        Session( int x , int y , int width , int height , int size , 
                 SDL_Renderer* renderer , TTF_Font* font , int level ) ;
        ~Session() ;

        // Methods :
            // Session itself :
        bool run() ;
        void update_board() ;
        void use_key() ;
            // SDL :
        void render_board() ;
        void render_square( int pos_x , int pos_y , int color ) ;
        void render_holded() ;
        void render_next_piece() ;
        void render_text() ;
        void renderPiece( int type , int center_x , int center_y ) ;
} ;


#endif