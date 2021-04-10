#include "input.hpp"

Keys get_input( SDL_Event event )
{
    if( SDL_PollEvent( &event ) == 0 )
        return KEY_NULL ;

    if( event.type == SDL_QUIT )
        return KEY_QUIT ;

    switch( event.key.keysym.sym )
    {
        case SDLK_UP :
            return KEY_UP ;
            break ;
        
        case SDLK_DOWN :
            return KEY_DOWN ;
            break ;

        case SDLK_LEFT :
            return KEY_LEFT ;
            break ;
        
        case SDLK_RIGHT :
            return KEY_RIGHT ;
            break ;

        case SDLK_c :
            return KEY_STORE ;
            break ;

        case SDLK_RETURN :
            return KEY_ENTER ;
            break ;

        case SDLK_SPACE :
            return KEY_SPACE ;
            break ;

        case SDLK_ESCAPE :
            return KEY_PAUSE ;
            break ;

        default :
            return KEY_NULL ;
    }
}