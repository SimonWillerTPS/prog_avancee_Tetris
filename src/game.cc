#include "game.hpp"

Game::Game()
{
    std::cout << "A void game has been created." << std::endl ;
}

Game::Game( std::string title , int win_height , int win_width ) :
            title( title ) , win_height( win_height ) , win_width( win_width )
{
    std::cout << "The game " << title << " has been created." << std::endl ;
}

Game::~Game()
{
    std::cout << "A game has been deleted." << std::endl ;
}

int Game::init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        error( "cannot initialize SDL") ;
        return( 1 ) ;
    }
    
    if(( window = SDL_CreateWindow( title.c_str() , SDL_WINDOWPOS_CENTERED ,
                                    SDL_WINDOWPOS_CENTERED ,
                                    win_height , win_width , 
                                    0 )) == NULL ) ;
    {
        error( "cannot create SDL window") ;
        return( 1 ) ;
    }

    if(( renderer = SDL_CreateRenderer( window , -1 ,
                                        SDL_RENDERER_ACCELERATED )) == NULL )
    {
        error( "cannot create SDL renderer" ) ;
        return( 1 ) ;    
    }

    return( 0 ) ;
}