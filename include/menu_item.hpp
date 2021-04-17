#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

/**
 * @file    menu_item.hpp
 * @brief   This file defines the Menu_item class.
 * @authors Luca Scimone & Simon Willer
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "choice.hpp"
#include "colors.hpp"

/**
 * @class   Menu_item
 * @brief 	This class is used to represent a Menu_item and to store all
 *          usefull attributes, to render it or to set a parameter.
 */
class Menu_item
{
    private :
        std::string     text      ; //*< string representing the text to display. */
        SDL_Surface*    surface   ; //*< Surface to render. */
        SDL_Texture*    texture   ; //*< Texture to render. */
        SDL_Rect        rectangle ; //*< Rectangle to render. */
        int*            value     ; //*< Int* current value of the parameter. */
        int             range     ; //*< Int to know the range of the parameter. Set to 0 when the item is only an entry.*/
        Choice          choice    ; //*< Choice returned when the item is selected by the player. */

    public :

        /**
         * @brief   Constructor of a Menu_item as a parameter.
         * @param   text Text displayed, example : "volume"
         * @param   value pointer to the value of the parameter.
         * @param   range range of the parameter.
         */
        Menu_item( std::string text , int* value , int range ) ;
        
        /**
         * @brief   Constructor of a Menu_item as an entry.
         * @param   text Text displayed, example : "marathon"
         * @param   choice Choice returned when this item is selected by
         *          the player.
         */        Menu_item( std::string text , Choice choice ) ;
        
        /**
         * @brief   Destroys the Menu_item.
         */
        ~Menu_item() ;

        /**
         * @brief   Accessor to the range of the item. If it is 0, then it is
         *          only an entry.
         */
        int get_range() ;

        /**
         * @brief   Accessor to the Choice represented by the item. If it is
         *          a parameter, then it returns VOID_CHOICE.
         */
        Choice  get_choice() ;

        
        /**
         * @brief   Sets the Choice of represented by the item.
         */
        void set_choice( Choice _choice ) ;
        
        /**
         * @brief   Increases the value of the parameter, if possible.
         */
        void more() ;
        
        /**
         * @brief   Dicreases the value of the parameter, if possible.
         */
        void less() ;

        /**
         * @brief   Renders the text of the Menu_item.
         */
        void render_text( TTF_Font* font ) ;
        
        /**
         * @brief   Used to render.
         */
        void create_texture( SDL_Renderer* renderer ) ;
        
        /**
         * @brief   Used to render.
         */
        void free_surface() ;
        
        /**
         * @brief   Sets the coordinates and size of the item's rectangle.
         */
        void set_rect( int x , int y , int width , int height ) ;
        
        /**
         * @brief   Used to render.
         */
        void render_copy( SDL_Renderer* renderer ) ;
        
        /**
         * @brief   Used after rendering.
         */
        void destroy_texture() ;

} ;

#endif