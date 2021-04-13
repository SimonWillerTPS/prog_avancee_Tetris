#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "choice.hpp"
#include "key.hpp"

class Menu
{
    private :

        SDL_Renderer*       renderer ;

        SDL_Surface*        mara_surface ;
        SDL_Texture*        mara_texture ;
        SDL_Rect            mara_rect ;
        SDL_Surface*        batt_surface ;
        SDL_Texture*        batt_texture ;
        SDL_Rect            batt_rect ;
        SDL_Surface*        quit_surface ;
        SDL_Texture*        quit_texture ;
        SDL_Rect            quit_rect ;

        SDL_Rect            selected_rect ;
        SDL_Event*          event ;
        TTF_Font*           font ;

        Key                 pressed_key ;
        std::vector<Choice> choices ;   
        int                 number_of_choices ;
        int                 win_width ;
        int                 win_height ;
        int                 list_size = 30 ;
        int                 selected = 0 ;
        bool                selecting ;

    public :

        Menu( SDL_Renderer* renderer , TTF_Font* font  , int number , 
              int width , int height ) ;
        ~Menu() ;

        bool   set_choice( int number , Choice choice ) ;
        Choice launch() ;
        bool   process_key() ;
        void   render() ;
} ;

#endif