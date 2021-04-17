#ifndef SESSION_HPP
#define SESSION_HPP

/**
 * @file    session.hpp
 * @brief   Defines the Session class.
 * @authors Luca Scimone & Simon Willer
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "board.hpp"
#include "colors.hpp"
#include "key.hpp"
#include "timer.hpp"

#define FPS 60                  //@def The number of maximum FPS.
#define TICK_PER_FRAME 1000/FPS //@def Used to calculate framerate. 

class Board ;

/**
 * @class   Session
 * @brief 	This class is used to launch, render and manage the gameplay.
 */
class Session
{
    private :

        LTimer* fps_timer ; //< Timer used to calculate FPS. 
        LTimer* cap_timer ; //< Timer used to set a maximum framerate.

        int win_orig_x ; //< Int used so set the original x coordinate to render the game.
        int win_orig_y ; //< Int used so set the original y coordinate to render the game.
        int width      ; //< Int used to set the width of the game.
        int height     ; //< Int used to set the height of the game.
        int tile_size  ; //< Int used to set the tile's size of the game.
    
        SDL_Renderer* renderer       ;  //< Renderer used to render the screen.
        SDL_Event*    event          ;  //< Event used to detect keyboard inputs.
        TTF_Font*     font           ;  //< Font used to write text.
        Mix_Music*    music          ;  //< Music played during the game.
        Mix_Chunk*    sound_dropped  ;  //< Sound played when a piece is placed.
        Mix_Chunk*    sound_gameover ;  //< Sound played when the player loses the game.
        Mix_Chunk*    sound_line     ;  //< Sound played when lines are completed.
        Mix_Chunk*    sound_rotate   ;  //< Sound played when the piece rotates.
        Mix_Chunk*    sound_pause    ;  //< Sound played when the game is paused.
            // Local :
        SDL_Surface* score_surface ; //< Surface used to render. 
        SDL_Surface* level_surface ; //< Surface used to render.
        SDL_Surface* lines_surface ; //< Surface used to render.   
        SDL_Texture* score_texture ; //< Texture used to render.
        SDL_Texture* level_texture ; //< Texture used to render.
        SDL_Texture* lines_texture ; //< Texture used to render.
        SDL_Rect rectangle         ; //< Rectangle used to render.
        SDL_Rect level_rect        ; //< Rectangle used to render.
        SDL_Rect lines_rect        ; //< Rectangle used to render.
        SDL_Rect score_rect        ; //< Rectangle used to render.
        
        // Board :
        Board* board ; //< Board that manages the game's calculations.

        // FPS management :
        float avgFPS             ; //< 
        int   counted_frames = 0 ; //<
        int   frame_Ticks        ; //<

        // Strings to render at screen :
        std::string     string_score ;
        std::string     string_level ;
        std::string     string_lines ;

        // Key to get input :
        Key pressed_key ;

        // Other attributes :
        bool running ;
        bool closing = false ;
        int  difficulty = 4 ;
        int  down_counter = 0 ;
        int  fallenCounter = 0 ;
        int  starting_level ;

    public :

        // Constructor, destructor :
        Session( int x , int y , int width , int height , int size , 
                 SDL_Renderer* renderer , TTF_Font* font , Mix_Music* music ,
                 Mix_Chunk* dropped , Mix_Chunk* gameover , Mix_Chunk* line ,
                 Mix_Chunk* rotate , Mix_Chunk* pause , int level ) ;
        ~Session() ;

        // Methods :
            // Session itself :
        bool run() ;
        bool IA_run() ;
        void IA_play() ;
        void update_board() ;
        bool use_key() ;
            // SDL :
        void render_board() ;
        void render_square( int pos_x , int pos_y , int color ) ;
        void render_holded() ;
        void render_next_piece() ;
        void render_text() ;
        void renderPiece( int type , int center_x , int center_y ) ;
        bool pause() ;
} ;

#endif