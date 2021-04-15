#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "choice.hpp"
#include "key.hpp"
#include "menu.hpp"
#include "session.hpp"

#define DROPPED_PATH    "res/dropped.mp3"
#define GAMEOVER_PATH   "res/gameover.mp3"
#define LINE_PATH       "res/line.mp3"
#define MUSIC_PATH      "res/tetris_music.mp3"
#define SELECT_PATH     "res/select.mp3"

class Game
{
    private :

        // SDL :
        SDL_Renderer* renderer ;
        SDL_Window*   window ;
        TTF_Font*     font ;
        Mix_Music*    music ;
        Mix_Chunk*    sound_dropped ;
        Mix_Chunk*    sound_gameover ;
        Mix_Chunk*    sound_line ;
        Mix_Chunk*    sound_select ;

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
        int         volume_music = 96 ;
        int         volume_chunk = 96 ;

    public :

        // Constructor, destructor :
        Game( std::string title , int width , int height ) ;
        ~Game() ;
        
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