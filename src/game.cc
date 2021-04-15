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

    if( Mix_OpenAudio( 44100 , MIX_DEFAULT_FORMAT , 1 , 2048 ) != 0 )
    {
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl ;
        return false ;
    }

    TTF_Init() ;

    font = TTF_OpenFont( "res/monobit.ttf" , 20 ) ;
    music = Mix_LoadMUS( MUSIC_PATH ) ;
    sound_dropped = Mix_LoadWAV( DROPPED_PATH ) ;
    sound_gameover = Mix_LoadWAV( GAMEOVER_PATH ) ;
    sound_line = Mix_LoadWAV( LINE_PATH ) ;
    sound_select = Mix_LoadWAV( SELECT_PATH ) ;

    if( font == NULL || music == NULL || sound_dropped == NULL
        || sound_select == NULL || sound_gameover == NULL 
        || sound_line == NULL)
    {
        std::cout << "Cannot load ressources, " ;
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl ;
        return false ;
    }

    Mix_VolumeMusic( volume_music ) ;

    return true ;
}

void Game:: close_SDL()
{
    SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
    Mix_FreeMusic( music ) ;
    Mix_FreeChunk( sound_dropped ) ;
    Mix_FreeChunk( sound_gameover ) ;
    Mix_FreeChunk( sound_line ) ;
    Mix_FreeChunk( sound_select ) ;

    TTF_CloseFont( font ) ;

    TTF_Quit();
	IMG_Quit();
    SDL_Quit() ;
}

int Game:: launch_menu()
{   
    menu = new Menu( renderer , font , music , sound_select , volume_music , 
                     volume_chunk , 4 , win_width , win_height ) ;

    if( !menu->set_choice( 0 , MARATHON )) return 1 ;
    if( !menu->set_choice( 1 , BATTLE )) return 1 ;
    if( !menu->set_choice( 2 , SETTINGS )) return 1 ;
    if( !menu->set_choice( 3 , EXIT )) return 1 ;

    while( running )
    {
        if( !Mix_PlayingMusic() )
            Mix_PlayMusic( music , volume_music ) ;
     
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
    }

    delete( menu ) ;

    return 0 ;
}

bool Game:: launch_marathon()
{
    session_player = new Session( 0 , 0 , win_width , win_height ,
                                  tile_size , renderer , font , music ,
                                  sound_dropped , sound_gameover ,
                                  sound_line , starting_level ) ;

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
