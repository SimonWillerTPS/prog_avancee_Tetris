#include "menu.hpp"

Menu:: Menu( SDL_Renderer* renderer , TTF_Font* font , int number ,
             int width , int height ) : 
             renderer( renderer ) , font( font ) , 
             number_of_choices( number ) , win_width( width ) ,
             win_height( height )
{
    event = new SDL_Event() ;
    for( int i = 0 ; i < number_of_choices ; i ++ )
        choices.push_back( VOID_CHOICE ) ;
}

Menu:: ~Menu()
{
    delete( event ) ;
}

bool Menu:: set_choice( int number , Choice choice )
{
    if( number >= (int) choices.size())
        return false ;

    choices[ number ] = choice ;

    return true ;
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

    return choices[ selected ] ;
}

bool Menu:: process_key()
{
    switch( pressed_key )
    {
        case KEY_UP :
            selected -- ;
            if( selected < 0 ) selected = number_of_choices - 1 ; 
            break;

        case KEY_DOWN :
            selected ++ ;
            if( selected > number_of_choices - 1 ) selected = 0 ; 
            break;

        case KEY_LEFT :
            break;

        case KEY_RIGHT :
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
    pressed_key = KEY_NULL ;    
    
    return true ;
}

void Menu:: render()
{
    SDL_SetRenderDrawColor( renderer , COLOR_BACKGROUND , 0xFF ) ;
    SDL_RenderClear( renderer ) ;

    mara_surface = TTF_RenderText_Solid( font , "MARATHON" ,
                                         { 255 , 255 , 255 } ) ;
    batt_surface = TTF_RenderText_Solid( font , "BATTLE" ,
                                         { 255 , 255 , 255 }) ;
    quit_surface = TTF_RenderText_Solid( font , "QUIT" ,
                                         { 255 , 255 , 255 }) ;
    logo_surface = SDL_LoadBMP( "res/logo.bmp" ) ;

    mara_texture = SDL_CreateTextureFromSurface( renderer , mara_surface) ;
    batt_texture = SDL_CreateTextureFromSurface( renderer , batt_surface) ;
    quit_texture = SDL_CreateTextureFromSurface( renderer , quit_surface) ;
    logo_texture = SDL_CreateTextureFromSurface( renderer , logo_surface ) ;

    SDL_FreeSurface( mara_surface ) ;
    SDL_FreeSurface( batt_surface ) ;
    SDL_FreeSurface( quit_surface ) ;
    SDL_FreeSurface( logo_surface ) ;

    mara_rect = { win_width / 2 - (int)( 1.5 * list_size ) , win_height / 2 , 
                  3 * list_size , list_size } ;
    batt_rect = { win_width / 2 - 1 * list_size , 
                  win_height / 2 + 2 * list_size , 
                  2 * list_size , list_size } ;
    quit_rect = { win_width / 2 - 1 * list_size , 
                  win_height / 2 + 4 * list_size , 
                  2 * list_size , list_size } ;
    logo_rect = { win_width / 2 - (int)( 7.5 * list_size ) ,
                  win_height / 2 - 8 * list_size ,
                  15 * list_size , 5 * list_size } ;

    SDL_RenderCopy( renderer , mara_texture , NULL , &mara_rect ) ;
    SDL_RenderCopy( renderer , batt_texture , NULL , &batt_rect ) ;
    SDL_RenderCopy( renderer , quit_texture , NULL , &quit_rect ) ;
    SDL_RenderCopy( renderer , logo_texture , NULL , &logo_rect ) ;

    SDL_SetRenderDrawColor( renderer , 255 , 255 , 255 , 255 ) ;
    selected_rect = { win_width / 2 - 2 * list_size , 
                      win_height / 2 + 2 * selected * list_size , 
                      4 * list_size , list_size } ;
    SDL_RenderDrawRect( renderer , &selected_rect ) ;

    SDL_DestroyTexture( mara_texture ) ;
    SDL_DestroyTexture( batt_texture ) ;
    SDL_DestroyTexture( quit_texture ) ;
    SDL_DestroyTexture( logo_texture ) ;

    SDL_RenderPresent( renderer ) ;
}