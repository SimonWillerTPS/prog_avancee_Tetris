#include "menu_item.hpp"

Menu_item:: Menu_item( std::string text , int* value , int range ) :
           text( text ) , value( value ) , range( range )
{
    choice = VOID_CHOICE ;
}

Menu_item:: Menu_item( std::string text , Choice choice ) : 
            text( text ) , choice( choice )
{
    value = 0 ; range = 0 ;
}

Menu_item:: ~Menu_item()
{
    // if( surface != NULL ) SDL_FreeSurface( surface ) ;
    // if( texture != NULL ) SDL_DestroyTexture( texture ) ;
}

int Menu_item:: get_range()
{
    return range ;
}

Choice Menu_item:: get_choice() 
{
    return choice ;
}

void Menu_item:: set_choice( Choice _choice )
{
    choice = _choice ;
}

void Menu_item:: more()
{
    if( range != 0 )
    {
        if( *value < range )
            *value += 1 ;

        if( *value > range )
            *value = range ;
    }
}

void Menu_item:: less()
{
    if( range != 0 )
    {
        if( *value > 0 )
            *value -= 1 ;

        if( *value < 0 )
            *value = 0 ;
    }
}

void Menu_item:: render_text( TTF_Font* font )
{
    if( range == 0 )
        surface = TTF_RenderText_Solid( font , text.c_str() , 
                                    { 255 , 255 , 255 } ) ;
    else    
    {   
        std::string result = text + "    " + std::to_string( *value ) ;

        surface = TTF_RenderText_Solid( font , result.c_str() ,
                                        { 255 , 255 , 255 } ) ;
    }
}

void Menu_item:: create_texture( SDL_Renderer* renderer )
{
    texture = SDL_CreateTextureFromSurface( renderer , surface ) ;
}

void Menu_item:: free_surface()
{
    SDL_FreeSurface( surface ) ;
}

void Menu_item:: set_rect( int x , int y , int width , int height )
{
    rectangle = { x , y , width , height } ;
}

void Menu_item:: render_copy( SDL_Renderer* renderer )
{
    SDL_RenderCopy( renderer , texture , NULL , &rectangle ) ;
}

void Menu_item:: destroy_texture()
{
    SDL_DestroyTexture( texture ) ;
}

