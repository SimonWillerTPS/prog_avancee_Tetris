#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "choice.hpp"
#include "colors.hpp"
#include "key.hpp"
#include "menu_item.hpp"

class Menu
{
    private :

        SDL_Renderer*           renderer ;
        TTF_Font*               font ;
        Mix_Chunk*              sound ;

        std::vector<Menu_item*> items ;
        SDL_Rect                selected_rect ;

        SDL_Event*              event ;
        Key                     pressed_key ;

        SDL_Surface*            logo_surface ;
        SDL_Texture*            logo_texture ;
        SDL_Rect                logo_rect ;

        int                     win_width ;
        int                     win_height ;
        int                     list_size = 30 ;
        int                     selected = 0 ;
        bool                    selecting ;

    public :

        Menu( SDL_Renderer* renderer , TTF_Font* font  , Mix_Chunk* sound ,
              int width , int height ) ;
        ~Menu() ;

        void   add_item( std::string text , Choice choice ) ;
        void   add_setting( std::string text , int* value , int range ) ;
        Choice launch() ;
        bool   process_key() ;
        void   render() ;
        void   render_logo() ;
        void   render_selected() ;
} ;

#endif