#include "game.hpp"

Game:: Game( std::string title , int width , int height ) :
             win_title( title ) , win_width( width ) , win_height ( height )
{
    if( init_SDL() )
        running = true ;
    else
        exit( 1 ) ;
}

Game:: ~Game()
{            
    close_SDL() ;
}

bool Game:: init_SDL()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl ;
        return false ;
    }

    window = SDL_CreateWindow( win_title.c_str() , SDL_WINDOWPOS_CENTERED , 
                               SDL_WINDOWPOS_CENTERED , win_width , 
                               win_height , 0 ) ;
    if( window == NULL )
    {
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl ;
        return false ;
    }

    renderer = SDL_CreateRenderer( window , 0 , SDL_RENDERER_ACCELERATED ) ;
    if( renderer == NULL )
    {
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl ;
        return false ;
    }

    TTF_Init() ;

    font = TTF_OpenFont( "res/monobit.ttf" , 20 ) ;

    return true ;
}

void Game:: close_SDL()
{
    SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
    
    TTF_CloseFont( font ) ;

    TTF_Quit();
	IMG_Quit();
    SDL_Quit() ;
}

int Game:: launch_menu()
{   
    menu = new Menu( renderer , font , 3 , win_width , win_height ) ;

    if( !menu->set_choice( 0 , MARATHON )) return 1 ;
    if( !menu->set_choice( 1 , BATTLE )) return 1 ;
    if( !menu->set_choice( 2 , EXIT )) return 1 ;

    while( running )
        switch( menu->launch() )
        {
            case MARATHON :
                running = launch_marathon() ;
                break ;
            
            case BATTLE :
                launch_battle() ;
                break ;
            
            case EXIT :
                running = false ;
                break ;
            
            default :
                break ;
        }

    delete( menu ) ;

    return 0 ;
}

bool Game:: launch_marathon()
{
    session_player = new Session( 0 , 0 , win_width , win_height ,
                                  tile_size , renderer , 
                                  font , starting_level ) ;

    bool result = session_player->run() ;

    delete( session_player ) ;

    return result ;
}

bool Game:: launch_battle()
{
    // session_player = new Session( 0 , 0 , win_width / 2 , win_height ,
    //                               tile_size , renderer , 
    //                               font , starting_level ) ;

    // session_IA = new Session( win_width / 2 , 0 , win_width / 2 , 0 , 
    //                           tile_size , renderer , font , starting_level ) ; 
    
    
    return false ;
}
