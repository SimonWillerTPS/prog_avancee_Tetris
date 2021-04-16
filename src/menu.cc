#include "menu.hpp"

Menu:: Menu( SDL_Renderer* renderer , TTF_Font* font  , Mix_Chunk* sound ,
             int width , int height ) : 
             renderer( renderer ) , font( font ) , sound( sound ) ,
             win_width( width ) , win_height( height )
{
    event = new SDL_Event() ;
}

Menu:: ~Menu()
{
    delete( event ) ;
    for( size_t i = 0 ; i < items.size() ; i ++ )
        delete( items[ i ] ) ;
}

void Menu:: add_item( std::string text , Choice choice )
{
    items.push_back( new Menu_item( text , choice ) ) ;
}

void Menu:: add_setting( std::string text , int* value , int range )
{
    items.push_back( new Menu_item( text , value , range ) ) ;
}

Choice Menu:: launch()
{
    selecting = true ;
    
    while( selecting )
    {
        pressed_key = get_key( event ) ;

        if( !process_key() ) return( EXIT ) ;

        render() ;
    }

    return items[ selected ]->get_choice() ;
}

bool Menu:: process_key()
{
    switch( pressed_key )
    {
        case KEY_UP :
            selected -- ;
            if( selected < 0 ) selected = items.size() - 1 ; 
            break;

        case KEY_DOWN :
            selected ++ ;
            if( (size_t) selected > items.size() - 1 ) selected = 0 ; 
            break;

        case KEY_LEFT :
            items[ selected ]->less() ;
            items[ selected ]->set_choice( VOID_CHOICE ) ;
            selecting = false ;
            break;

        case KEY_RIGHT :
            items[ selected ]->more() ;
            items[ selected ]->set_choice( VOID_CHOICE ) ;
            selecting = false ;
            break;

        case KEY_SPACE :
        case KEY_ENTER :
            selecting = false ;
            break;

        case KEY_QUIT :
            return false ;

        default :
            break;
    }
    if( pressed_key != KEY_NULL )
        Mix_PlayChannel( 1 , sound , 0 ) ;

    pressed_key = KEY_NULL ;    
    
    return true ;
}

void Menu:: render()
{
    SDL_SetRenderDrawColor( renderer , COLOR_BACKGROUND , 0xFF ) ;
    SDL_RenderClear( renderer ) ;

    render_logo() ;

    int orig_x = win_width / 2 - 2 * list_size ;
    int orig_y = win_height / 2 ;

    for( size_t i = 0 ; i < items.size() ; i ++ )
    {   
        items[ i ]->render_text( font ) ;
        items[ i ]->create_texture( renderer ) ;
        items[ i ]->free_surface() ;
        if( items[ i ]->get_range() != 0 )
            items[ i ]->set_rect( orig_x - 2 * list_size , 
                                  (int)( orig_y + 2*i * list_size ) ,
                                  8 * list_size , 1 * list_size ) ;
        else
            items[ i ]->set_rect( orig_x , (int)( orig_y + 2*i * list_size ) ,
                                  4 * list_size , 1 * list_size ) ;
        items[ i ]->render_copy( renderer ) ;
        items[ i ]->destroy_texture() ;
    }

    render_selected() ;

    SDL_RenderPresent( renderer ) ;
}

void Menu:: render_logo()
{
    logo_surface = SDL_LoadBMP( "res/logo.bmp" ) ;
    logo_texture = SDL_CreateTextureFromSurface( renderer , logo_surface ) ;
    SDL_FreeSurface( logo_surface ) ;
    logo_rect = { win_width / 2 - (int)( 7.5 * list_size ) ,
                  win_height / 2 - 8 * list_size ,
                  15 * list_size , 5 * list_size } ;
    SDL_RenderCopy( renderer , logo_texture , NULL , &logo_rect ) ;
    SDL_DestroyTexture( logo_texture ) ;
}

void Menu:: render_selected() 
{
    SDL_SetRenderDrawColor( renderer , COLOR_WHITE , 255 ) ;
    if( items[ selected ]->get_range() != 0 )
        selected_rect = { win_width / 2 - 5 * list_size , 
                        (int)( win_height / 2 + 2*selected*list_size - 0.5 ) , 
                        10 * list_size , (int)( 1.5 * list_size ) } ;
    else
        selected_rect = { win_width / 2 - 3 * list_size , 
                        (int)( win_height / 2 + 2*selected*list_size - 0.5 ) , 
                        6 * list_size , (int)( 1.5 * list_size ) } ;
    SDL_RenderDrawRect( renderer , &selected_rect ) ;
}