#include "game.hpp"

Game:: Game( std::string title , int width , int height ) :
             win_title( title ) , win_width( width ) , win_height ( height )
{

    starting_level = new int( 0 ) ;
    volume_music = new int( DEFAULT_SOUND ) ;
    volume_chunk = new int( DEFAULT_SOUND ) ;

    if( init_SDL() )
        running = true ;
    else
        exit( 1 ) ;

}

Game:: ~Game()
{            
    close_SDL() ;
    delete( starting_level ) ;
    delete( volume_chunk ) ;
    delete( volume_music ) ;
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

    font = TTF_OpenFont( FONT_PATH , 20 ) ;
    music = Mix_LoadMUS( MUSIC_PATH ) ;
    sound_dropped = Mix_LoadWAV( DROPPED_PATH ) ;
    sound_gameover = Mix_LoadWAV( GAMEOVER_PATH ) ;
    sound_line = Mix_LoadWAV( LINE_PATH ) ;
    sound_select = Mix_LoadWAV( SELECT_PATH ) ;
    sound_rotate = Mix_LoadWAV( ROTATE_PATH ) ;

    if( font == NULL || music == NULL || sound_dropped == NULL
        || sound_select == NULL || sound_gameover == NULL 
        || sound_line == NULL || sound_rotate == NULL )
    {
        std::cout << "Cannot load ressources, " ;
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl ;
        return false ;
    }

    Mix_VolumeMusic( (int)( *volume_music * 128 / 20 ) ) ;
    set_chunks_volume() ;

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
    Mix_FreeChunk( sound_rotate ) ;

    TTF_CloseFont( font ) ;

    Mix_Quit() ;
    TTF_Quit();
	IMG_Quit();
    SDL_Quit() ;
}

int Game:: launch_menu()
{   
    menu = new Menu( renderer , font , sound_select ,
                     win_width , win_height ) ;

    menu->add_item( "MARATHON" , MARATHON ) ;
    menu->add_item( "BATTLE" , BATTLE ) ;
    menu->add_item( "SETTIGS" , SETTINGS ) ;
    menu->add_item( "QUIT" , EXIT ) ;

    while( running )
    {
        if( !Mix_PlayingMusic() )
            Mix_PlayMusic( music , -1 ) ;
     
        switch( menu->launch() )
        {
            case MARATHON :
                running = launch_marathon() ;
                break ;
            
            case BATTLE :
                launch_battle() ;
                break ;
            
            case SETTINGS :
                launch_settings() ;
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
                                  sound_line , sound_rotate , 
                                  *starting_level ) ;

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

bool Game:: launch_settings()
{
    settings = new Menu( renderer , font , sound_select , 
                         win_width , win_height ) ;

    settings->add_setting( "EFFECTS VOLUME" , volume_chunk , 20 ) ;
    settings->add_setting( "  MUSIC VOLUME" , volume_music , 20 ) ;
    settings->add_setting( "   FIRST LEVEL" , starting_level , 15 ) ;
    settings->add_item( "RETURN" , EXIT ) ;

    while( settings->launch() != EXIT )
    {
        Mix_VolumeMusic( (int)( *volume_music * 128 / 20 ) ) ;
        set_chunks_volume() ;
    }

    delete( settings ) ;

    return true ;
}

void Game:: set_chunks_volume()
{
    Mix_VolumeChunk( sound_select , (int)( *volume_chunk * 128 / 20 ) ) ;
    Mix_VolumeChunk( sound_dropped , (int)( *volume_chunk * 128 / 20 ) ) ;
    Mix_VolumeChunk( sound_gameover , (int)( *volume_chunk * 128 / 20 ) ) ;
    Mix_VolumeChunk( sound_line , (int)( *volume_chunk * 128 / 20 ) ) ;
    Mix_VolumeChunk( sound_rotate , (int)( *volume_chunk * 128 / 20 ) ) ;
}