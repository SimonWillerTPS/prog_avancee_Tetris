#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "choice.hpp"
#include "colors.hpp"

class Menu_item
{
    private :
        std::string     text ;
        SDL_Surface*    surface ;
        SDL_Texture*    texture ;
        SDL_Rect        rectangle ;
        int*            value ;
        int             range ;
        int             type ;
        Choice          choice ;

    public :
        Menu_item( std::string text , int* value , int range ) ;
        Menu_item( std::string text , Choice choice ) ;
        ~Menu_item() ;

        // std::string     get_string() ;
        // SDL_Surface*    get_surface() ;
        // SDL_Texture*    get_texture() ;
        // SDL_Rect        get_rect() ;
        // int             get_value() ;
        int             get_range() ;
        Choice  get_choice() ;

        void set_choice( Choice _choice ) ;
        void more() ;
        void less() ;

        void render_text( TTF_Font* font ) ;
        void create_texture( SDL_Renderer* renderer ) ;
        void free_surface() ;
        void set_rect( int x , int y , int width , int height ) ;
        void render_copy( SDL_Renderer* renderer ) ;
        void destroy_texture() ;

} ;

#endif