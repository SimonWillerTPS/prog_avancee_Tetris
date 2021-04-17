#ifndef MENU_HPP
#define MENU_HPP

/**
 * @file    menu.hpp
 * @brief   Defines the Menu class.
 * @authors Luca Scimone & Simon Willer
 */

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

/**
 * @class   Menu
 * @brief   This class is used to launch, render and manage a game menu.
 */
class Menu
{
    private :

        SDL_Renderer*           renderer      ; /**< Renderer used to render the screen. */
        TTF_Font*               font          ; /**< Font used to write text. */
        Mix_Chunk*              sound         ; /**< Sound played in the menus, during selections. */
        std::vector<Menu_item*> items         ; /**< Vector of Menu_item that represents the menu entry. */
        SDL_Rect                selected_rect ; /**< Rectangle to render which is the current selecter entry. */
        SDL_Event*              event         ; /**< Event used to detect keyboard inputs. */
        Key                     pressed_key   ; /**< Key used to get the player keyboard's inputs. */
        SDL_Surface*            logo_surface  ; /**< Surface used to render. */
        SDL_Texture*            logo_texture  ; /**< Texture used to render. */
        SDL_Rect                logo_rect     ; /**< Rectangle used to render. */

        int                     win_width      ; /**< Int used to set the width of the menu display. */
        int                     win_height     ; /**< Int used to set the height of the menu display. */
        int                     list_size = 30 ; /**< Int used to set the proportinnal size of the entries. */
        int                     selected = 0   ; /**< Int used to know which Menu_item is currently selected. */
        bool                    selecting      ; /**< Bool to know when to stop the Menu. */

    public :

        /**
         * @brief   Inits a Menu instance.
         * @param   renderer renderer to render the game.
         * @param   font font to render the text.
         * @param   sound selecting sound.
         * @param   width width of renderer.
         * @param   height height of the renderer.
         */
        Menu( SDL_Renderer* renderer , TTF_Font* font  , Mix_Chunk* sound ,
              int width , int height ) ;

        /**
         * @brief   Deletes the Menu.
         */
        ~Menu() ;

        /**
         * @brief   Adds a Menu_item to the items vector,
         *          which is only an entry.
         */        
        void   add_item( std::string text , Choice choice ) ;
        
        
        /**
         * @brief   Adds a Menu_item to the items vector which is a parameter.
         */
        void   add_setting( std::string text , int* value , int range ) ;

        /**
         * @brief   Launches the menu to render, and take inputs.
         */
        Choice launch() ;

        /**
         * @brief   Processes the player's inputs.
         */
        bool   process_key() ;

        /**
         * @brief   Renders the menu.
         */
        void   render() ;

        /**
         * @brief   Renders the Tetris Logo.
         */
        void   render_logo() ;

        /**
         * @brief   Renders the rectangle that shows which entry is
         *          currently selected.
         */
        void   render_selected() ;
} ;

#endif