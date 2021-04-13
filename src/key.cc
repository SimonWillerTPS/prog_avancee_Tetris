#include "key.hpp"

Key get_key( SDL_Event* event )
{
    while( SDL_PollEvent( event ))
    {
        if( event->type == SDL_QUIT )
            return KEY_QUIT ;

        else if( event->type == SDL_KEYDOWN )
            switch( event->key.keysym.sym )
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
    return KEY_NULL ;
}