#include "game.hpp"

Game:: Game( std::string title , int width , int height ) :
                 title( title ) , width ( width ) , height( height )
{
    ;
}

Game:: ~Game()
{
    ;
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

    return true ;
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