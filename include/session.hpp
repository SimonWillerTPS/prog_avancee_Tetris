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

        LTimer* fps_timer ; /**< Timer used to calculate FPS. */
        LTimer* cap_timer ; /**< Timer used to set a maximum framerate. */

        int win_orig_x ; /**< Int used so set the original x coordinate to render the game. */
        int win_orig_y ; /**< Int used so set the original y coordinate to render the game. */
        int width      ; /**< Int used to set the width of the game. */
        int height     ; /**< Int used to set the height of the game. */
        int tile_size  ; /**< Int used to set the tile's size of the game. */
    
        SDL_Renderer* renderer       ; /**< Renderer used to render the screen. */
        SDL_Event*    event          ; /**< Event used to detect keyboard inputs. */
        TTF_Font*     font           ; /**< Font used to write text. */
        Mix_Music*    music          ; /**< Music played during the game. */
        Mix_Chunk*    sound_dropped  ; /**< Sound played when a piece is placed. */
        Mix_Chunk*    sound_gameover ; /**< Sound played when the player loses the game. */
        Mix_Chunk*    sound_line     ; /**< Sound played when lines are completed. */
        Mix_Chunk*    sound_rotate   ; /**< Sound played when the piece rotates. */
        Mix_Chunk*    sound_pause    ; /**< Sound played when the game is paused. */
        SDL_Surface* score_surface ; /**< Surface used to render. */
        SDL_Surface* level_surface ; /**< Surface used to render. */
        SDL_Surface* lines_surface ; /**< Surface used to render. */
        SDL_Texture* score_texture ; /**< Texture used to render. */
        SDL_Texture* level_texture ; /**< Texture used to render. */
        SDL_Texture* lines_texture ; /**< Texture used to render. */
        SDL_Rect rectangle         ; /**< Rectangle used to render. */
        SDL_Rect level_rect        ; /**< Rectangle used to render. */
        SDL_Rect lines_rect        ; /**< Rectangle used to render. */
        SDL_Rect score_rect        ; /**< Rectangle used to render. */
        
        Board* board ; /**< Board that manages the game's calculations. */

        float avgFPS             ; /**< Float used to calculate FPS. */
        int   counted_frames = 0 ; /**< Int used to calculate FPS. */
        int   frame_Ticks        ; /**< Int used to calculate FPS. */

        // Strings to render at screen :
        std::string     string_score ; //*< String used to render text. */
        std::string     string_level ; //*< String used to render text. */
        std::string     string_lines ; //*< String used to render text. */

        // Key to get input :
        Key pressed_key ; /**< Key used to get the player keyboard's inputs. */

        // Other attributes :
        bool running ;
        bool closing = false ;
        int  difficulty = 4 ;
        int  down_counter = 0 ;
        int  fallenCounter = 0 ;
        int  starting_level ;

    public :

        /**
         * @brief   Inits a Session instance.
         * @param   x coordinates where to begin to display.
         * @param   y coordinates where to begin to display.
         * @param   width width of renderer.
         * @param   height height of the renderer.
         * @param   size size of the game's tiles.
         * @param   renderer renderer to render the game.
         * @param   font font to render the text.
         * @param   music music playing.
         * @param   dropped dropped sound.
         * @param   gameover gameover sound.
         * @param   line complete line sound.
         * @param   rotate rotating sound.
         * @param   pause pause sound.
         * @param   level initial level to start the game.
         */
        Session( int x , int y , int width , int height , int size , 
                 SDL_Renderer* renderer , TTF_Font* font , Mix_Music* music ,
                 Mix_Chunk* dropped , Mix_Chunk* gameover , Mix_Chunk* line ,
                 Mix_Chunk* rotate , Mix_Chunk* pause , int level ) ;
        
        /**
         * @brief   Stops the Session.
         */
        ~Session() ;

        /**
         * @brief   Launches the real game, to take input, calculate and
         *          render the display.
         */
        bool run() ;

        /**
         * @brief   Launches a game controled by the AI.
         */
        bool IA_run() ;

        /**
         * @brief   Launches the AI detection to get its next move.
         */
        void IA_play() ;

        /**
         * @brief   Checks if there are completed lines, or if the game is 
         *          over. Generates next Piece if needed.
         */
        void update_board() ;

        /**
         * @brief   Translates player's input into game's movement.
         */
        bool use_key() ;

        /**
         * @brief   Renders all the screen.
         */
        void render_board() ;

        /**
         * @brief   Renders a screen tile, giving its position and color.
         * @param   x coordinate.
         * @param   y coordinate.
         * @param   color color.
         */
        void render_square( int pos_x , int pos_y , int color ) ;

        /**
         * @brief   Renders the holded piece and the frame.
         */
        void render_holded() ;

        /**
         * @brief   Renders the next piece and the frame.
         */
        void render_next_piece() ;

        /**
         * @brief   Renders texts, like score and level.
         */
        void render_text() ;

        /**
         * @brief   Renders a piece, centered in coordinates.
         * @param   type Piece's type.
         * @param   center_x coordinate of where the center of the piece
         *          should be.
         * @param   center_y coordinate of where the center of the piece
         *          should be.
         */
        void renderPiece( int type , int center_x , int center_y ) ;

        /**
         * @brief   Pauses the game and displays hox to resume it.
         */
        bool pause() ;

        /**
         * @brief   Display the gameover pannel.
         */
        void render_gameover() ;
} ;

#endif