#ifndef GAME_HPP
#define GAME_HPP

/**
 * @file    game.hpp
 * @brief   Defines the Game class.
 * @authors Luca Scimone & Simon Willer
 */

#include <iostream>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "choice.hpp"
#include "key.hpp"
#include "menu.hpp"
#include "session.hpp"

#define FONT_PATH     "res/font.ttf"         // @def Path to the font file.
#define DROPPED_PATH  "res/dropped.mp3"      // @def Path to the dropped_sound file.
#define GAMEOVER_PATH "res/gameover.mp3"     // @def Path to the gameover_sound file.
#define LINE_PATH     "res/line.mp3"         // @def Path to the line_sound file.
#define PAUSE_PATH    "res/pause.wav"        // @def Path to the pause_sound file.
#define MUSIC_PATH    "res/tetris_music.mp3" // @def Path to the music file.
#define SELECT_PATH   "res/select.mp3"       // @def Path to the select_sound file.
#define ROTATE_PATH   "res/rotate.mp3"       // @def Path to the rotate_sound file.

#define DEFAULT_SOUND 10 // @def Default volume level. (Max is 20.)

/**
 * @class   Game
 * @brief   This class is used to make a game instance.
 */
class Game
{
    private :

        // pthread_t thread_player ;
        // pthread_t thread_IA ;

        SDL_Window*   window         ; //< Window used to run the game.
        SDL_Renderer* renderer       ; //< Renderer used to render the screen.  
        TTF_Font*     font           ; //< Font used to write texts.
        Mix_Music*    music          ; //< Music that is played during the game.
        Mix_Chunk*    sound_dropped  ; //< Sound played when a piece is placed.
        Mix_Chunk*    sound_gameover ; //< Sound played when the player loses the game.
        Mix_Chunk*    sound_line     ; //< Sound played when lines are completed.
        Mix_Chunk*    sound_select   ; //< Sound played in the menus, during selections.
        Mix_Chunk*    sound_rotate   ; //< Sound played when the piece rotates.
        Mix_Chunk*    sound_pause    ; //< Sound played when the game is paused.

        Menu* menu     ; //< Menu used for the "main menu" of the game.
        Menu* settings ; //< Menu used for the "settings menu" of the game.

        Session* session_player ; //< Session launched for the player to play.
        Session* session_IA     ; //< Session launched for the IA to play.

        std::string win_title      ; //< String used for the title of the game's window
        int         win_width      ; //< Int used to set the window's width.
        int         win_height     ; //< Int used to set the window's height.
        int         tile_size = 30 ; //< Int used to set the size of the game's tiles.
        bool        running        ; //< Bool used to know when to stop the game.
        int*        starting_level ; //< Int* used to defines at which level the game starts.
        int*        volume_music   ; //< Int* used to set the music's volume.
        int*        volume_chunk   ; //< Int* used to set the sound effect's volume.

    public :

        /**
         * @brief   Inits a game instance.
         * @param   title title of the game's window.
         * @param   width width of the game's window.
         * @param   height height of the game's window.
         */
        Game( std::string title , int width , int height ) ;

        /**
         * @brief   Stops the game.
         */
        ~Game() ;
        
        /**
         * @brief   Init all that the SDL library needs. Loads ressources also.
         */
        bool init_SDL() ;

        /**
         * @brief   Close all ressources and instance created by and 
         *          for the SDL library.
         */
        void close_SDL() ;

        /**
         * @brief   Launches the menu. Takes inputs from the player to allow 
         *          him to choose the game mode and to go in the settings.
         */
        int  launch_menu() ;

        /**
         * @brief   Launches a session in marathon mode.
         */
        bool launch_marathon() ;

        /**
         * @brief   Launches 2 sessions for the battle agains IA mode.
         */
        bool launch_battle() ;

        /**
         * @brief   Launches the settings menu for the player to modify sound
         *          volume and beggining level.
         */
        bool launch_settings() ;

        /**
         * @brief   Sets the volume of all the sound effects (not the music).
         */
        void set_chunks_volume() ;

} ;

#endif