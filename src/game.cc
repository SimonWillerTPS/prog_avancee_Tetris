#include "game.hpp"

Game:: Game( std::string title , int width , int height ) :
                 title( title ) , width ( width ) , height( height )
{
    board = new Board() ;
}

Game:: ~Game()
{
    delete( board ) ;
}

SDL_Window* Game:: get_window()
{
    return window ;
}

SDL_Renderer* Game:: get_renderer()
{
    return renderer ;
}

SDL_Surface* Game:: get_surface()
{   
    return surface ;
}

SDL_Texture* Game:: get_texture()
{
    return texture ;
}

int Game:: get_width()
{
    return width ;
}

int Game:: get_height()
{
    return height ;
}

bool Game:: is_running()
{
    return running ;
}

bool Game:: init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
		std::cout << "SDL_Error: %s" << std::endl ;
        return false ;
    }

    window = SDL_CreateWindow( title.c_str() , SDL_WINDOWPOS_CENTERED , 
                               SDL_WINDOWPOS_CENTERED , width , height , 
                               0 ) ;
    if( window == NULL )
    {
        std::cout << "SDL_Error: %s" << std::endl ;
        return false ;
    }

    surface = SDL_GetWindowSurface( window ) ;
    if( surface == NULL ) 
    {
        std::cout << "SDL_Error: %s" << std::endl ;
        return false ;
    }

    renderer = SDL_CreateRenderer( window , -1 , SDL_RENDERER_ACCELERATED ) ;
    if( renderer == NULL )
    {
        std::cout << "SDL_Error: %s" << std::endl ;
        return false ;
    }

    running = true ;

    return true ;
}

void Game:: run()
{
    while( running )
    {
        get_input() ;
        
        if( pressed_key == KEY_QUIT )
            running = false ;
        
        else
            use_key() ;

        //board->update
    }
}

void Game:: use_key()
{
    ;
}

// bool Game:: load_menu()
// {

// }

/* Credit to http://lazyfoo.net/tutorials/SDL/ */
SDL_Texture* Game:: load_texture( std::string path )
{
    //The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void Game:: get_input()
{
    if( SDL_PollEvent( &event ) == 0 )
        pressed_key = KEY_NULL ;

    if( event.type == SDL_QUIT )
        pressed_key = KEY_QUIT ;

    switch( event.key.keysym.sym )
    {
        case SDLK_UP :
            pressed_key = KEY_UP ;
            break ;
        
        case SDLK_DOWN :
            pressed_key = KEY_DOWN ;
            break ;

        case SDLK_LEFT :
            pressed_key = KEY_LEFT ;
            break ;
        
        case SDLK_RIGHT :
            pressed_key = KEY_RIGHT ;
            break ;

        case SDLK_c :
            pressed_key = KEY_STORE ;
            break ;

        case SDLK_RETURN :
            pressed_key = KEY_ENTER ;
            break ;

        case SDLK_SPACE :
            pressed_key = KEY_SPACE ;
            break ;

        case SDLK_ESCAPE :
            pressed_key = KEY_PAUSE ;
            break ;

        default :
            pressed_key = KEY_NULL ;
    }
}