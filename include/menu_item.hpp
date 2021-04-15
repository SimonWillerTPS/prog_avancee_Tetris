#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <SDL2/SDL.h>
#include <string>

class Menu_item
{
    private :
        std::string     string ;
        SDL_Surface*    surface ;
        SDL_Texture*    texture ;
        SDL_Rect        rectangle ;
        int             value ;
        int             range ;

    public :
        Menu_item( std::string string , int parameter , int range ) ;
        ~Menu_item() ;

        std::string get_string() ;
        SDL_Surface* get_surface() ;
        SDL_Texture* get_texture() ;
        SDL_Rect get_rect() ;
        int get_value() ;
        int get_range() ;

} ;

#endif