#include "game.hpp"

Game:: Game( std::string title , int width , int height ) :
                 title( title ) , width ( width ) , height( height )
{
    board = new Board() ;
    timer = new LTimer() ;
    timer->start() ;
}

Game:: ~Game()
{
    SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
    SDL_Quit() ;
    delete( timer ) ;
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
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl ;
        return false ;
    }

    window = SDL_CreateWindow( title.c_str() , SDL_WINDOWPOS_CENTERED , 
                               SDL_WINDOWPOS_CENTERED , width , height , 
                               0 ) ;
    if( window == NULL )
    {
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl ;
        return false ;
    }

    // surface = SDL_GetWindowSurface( window ) ;
    // if( surface == NULL ) 
    // {
    //     std::cout << "SDL_Error: " << SDL_GetError() << std::endl ;
    //     return false ;
    // }

    renderer = SDL_CreateRenderer( window , -1 , 0 ) ;
    if( renderer == NULL )
    {
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl ;
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

        if( timer->getTicks() % 2000 < 200 )
            board->movePieceDown() ;

        update_board() ;

        render_board() ;

        SDL_Delay( 200 ) ;
    }
}

void Game:: use_key()
{
    switch(pressed_key)
    {
        case KEY_UP :
            board->rotatePiece();
            break;
        case KEY_DOWN :
            board->movePieceDown();
            break;
        case KEY_LEFT :
            board->movePieceLeft();
            break;
        case KEY_RIGHT :
            board->movePieceRight();
            break;
        case KEY_STORE :
            board->holdPiece();
            break ;
        //case KEY_ENTER :
            //break ;
        case KEY_SPACE :
            board->dropPiece();
            break;
        case KEY_QUIT :
            running= false ;
            break;
        default :
            break;
    }
    pressed_key = KEY_NULL ;
    // SDL_Delay( 1000 / 24 ) ;
}

// bool Game:: load_menu()
// {

// }

void Game:: get_input()
{
    while( SDL_PollEvent( &event ))
    {
        if( event.type == SDL_QUIT )
            pressed_key = KEY_QUIT ;
        else if( event.type == SDL_KEYDOWN )
        {
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
                    fallenCounter = 10 + 1 ;
                    break ;

                case SDLK_ESCAPE :
                    pressed_key = KEY_PAUSE ;
                    break ;

                default :
                    pressed_key = KEY_NULL ;
            }
        }
    }
}

void Game:: render_board()
{
    SDL_SetRenderDrawColor( renderer , 0x03 , 0x41 , 0xAE , 0xFF ) ;
    SDL_RenderClear( renderer ) ;
    
    for ( int i = 0 ; i < BOARD_HEIGHT ; i ++ )
        for ( int j = 0 ; j < BOARD_WIDTH ; j ++ )
        {
            render_square( j * SQUARE_DIM , i * SQUARE_DIM , board->area[ j ][ i ]) ;
        }

    render_holded() ;
    
    render_next_piece() ;
    
    SDL_RenderPresent( renderer ) ;
}

void Game::render_square( int pos_x , int pos_y , int color )
{
    int orig_x = width / 2 - 5 * SQUARE_DIM ;
    int orig_y = height / 2 - 10 * SQUARE_DIM ;

    SDL_Rect rectangle = { orig_x + pos_x , orig_y + pos_y , 
                           SQUARE_DIM , SQUARE_DIM } ;

    switch( color )
    {
        case CYAN :
            SDL_SetRenderDrawColor( renderer , 0x00 , 0xFF , 0xFF , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x00 , 0xF0 , 0xF0 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;

        case BLUE :
            SDL_SetRenderDrawColor( renderer , 0x00 , 0x00 , 0xFF , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x00 , 0x00 , 0xF0 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case GREEN :
            SDL_SetRenderDrawColor( renderer , 0x00 , 0xFF , 0x00 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x00 , 0xF0 , 0x00 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case ORANGE :
            SDL_SetRenderDrawColor( renderer , 0xFF , 0x7F , 0x00 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0xFF , 0x70 , 0x00 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case PURPLE :
            SDL_SetRenderDrawColor( renderer , 0x80 , 0x00 , 0x80 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x70 , 0x00 , 0x70 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case YELLOW :
            SDL_SetRenderDrawColor( renderer , 0xFF , 0xFF , 0x00 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0xF0 , 0xF0 , 0x00 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case RED :
            SDL_SetRenderDrawColor( renderer , 0xFF , 0x00 , 0x00 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0xF0 , 0x00 , 0x00 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case EMPTY :
            SDL_SetRenderDrawColor( renderer , 0 , 0 , 0 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 30 , 30 , 30 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        default :
            break ;
    }
}

void Game:: render_holded()
{
    SDL_Rect rectangle = { width / 2 - 11 * SQUARE_DIM , 
                           height / 2 - 10 * SQUARE_DIM  , 
                           5 * SQUARE_DIM , 5 * SQUARE_DIM } ;
    
    SDL_SetRenderDrawColor( renderer , 0 , 0 , 0 , 255 ) ;
    SDL_RenderFillRect( renderer , &rectangle ) ;
    SDL_SetRenderDrawColor( renderer , 30 , 30 , 30 , 255 ) ;
    SDL_RenderDrawRect( renderer , &rectangle ) ;

    if( board->isHolded())
        renderPiece( board->getHoldedPieceType() , 
                     width / 2 - 6 * SQUARE_DIM - 5 * SQUARE_DIM / 2 ,
                     height / 2 - 10 * SQUARE_DIM + 5 * SQUARE_DIM / 2) ;
}

void Game:: render_next_piece()
{
    SDL_Rect rectangle = { width / 2 + 6 * SQUARE_DIM , 
                           height / 2 - 10 * SQUARE_DIM  , 
                           5 * SQUARE_DIM , 5 * SQUARE_DIM } ;
    
    SDL_SetRenderDrawColor( renderer , 0 , 0 , 0 , 255 ) ;
    SDL_RenderFillRect( renderer , &rectangle ) ;
    SDL_SetRenderDrawColor( renderer , 30 , 30 , 30 , 255 ) ;
    SDL_RenderDrawRect( renderer , &rectangle ) ;

    renderPiece( board->getNextPieceType() , 
                 width / 2 + 6 * SQUARE_DIM + 5 * SQUARE_DIM / 2 ,
                 height / 2 - 10 * SQUARE_DIM + 5 * SQUARE_DIM / 2) ;
}

void Game:: update_board()
{
    if( board->isPieceFallen())
    {
        fallenCounter ++ ;
        if( fallenCounter > 10 )
        {
            board->newPiece() ;
            int a = board->deletePossibleLines() ;
            board->calculScore(a);
            fallenCounter = 0 ;
        }
    }
    
    if( board->GameOver())
    {
        running = false ;
    }
}

void Game:: renderPiece( int type , int center_x , int center_y )
{
    SDL_Rect rectangle ;
    switch( type )
    {
        case 0 :
            for( int i = -1 ; i < 1 ; i ++ )
                for( int j = -1 ; j < 1 ; j ++ )
                {
                    rectangle = { center_x + i * SQUARE_DIM , 
                                  center_y + j * SQUARE_DIM  , 
                                  SQUARE_DIM , SQUARE_DIM } ;
                    SDL_SetRenderDrawColor( renderer , 0x00 , 0xFF , 
                                            0xFF , 255 ) ;
                    SDL_RenderFillRect( renderer , &rectangle ) ;
                    SDL_SetRenderDrawColor( renderer , 0x00 , 0xF0 , 
                                            0xF0 , 255 ) ;
                    SDL_RenderDrawRect( renderer , &rectangle ) ;
                }
            break ;

        case 1 :
            for( int i = -2 ; i < 2 ; i ++ )
            {
                rectangle = { center_x - SQUARE_DIM / 2 ,
                              center_y + i * SQUARE_DIM ,
                              SQUARE_DIM , SQUARE_DIM } ;
                SDL_SetRenderDrawColor( renderer , 0x00 , 0x00 , 0xFF , 255 ) ;
                SDL_RenderFillRect( renderer , &rectangle ) ;
                SDL_SetRenderDrawColor( renderer , 0x00 , 0x00 , 0xF0 , 255 ) ;
                SDL_RenderDrawRect( renderer , &rectangle ) ;
            }
            break ;

        case 5 :
            rectangle = { center_x + SQUARE_DIM / 2 ,
                          center_y - SQUARE_DIM ,
                          SQUARE_DIM , SQUARE_DIM } ;
            SDL_SetRenderDrawColor( renderer , 0x80 , 0x00 , 0x80 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x70 , 0x00 , 0x70 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            for(float i = -1.5 ; i < 1 ; i ++ )
            {
                rectangle = { (int)( center_x + i * SQUARE_DIM ) ,
                              center_y , SQUARE_DIM , SQUARE_DIM } ;
                SDL_SetRenderDrawColor( renderer , 0x80 , 0x00 , 0x80 , 255 ) ;
                SDL_RenderFillRect( renderer , &rectangle ) ;
                SDL_SetRenderDrawColor( renderer , 0x70 , 0x00 , 0x70 , 255 ) ;
                SDL_RenderDrawRect( renderer , &rectangle ) ;
            }
            break ;

        case 2 : //S
            for( int j = 0 ; j < 2 ; j ++ )
                for( float i = -1.5 ; i < 0 ; i ++ )
                {
                    rectangle = { (int)( center_x + ( i + j ) * SQUARE_DIM ) ,
                                  center_y - j * SQUARE_DIM ,
                                  SQUARE_DIM , SQUARE_DIM } ;
                    SDL_SetRenderDrawColor( renderer , 0xFF , 0x7F , 
                                            0x00 , 255 ) ;
                    SDL_RenderFillRect( renderer , &rectangle ) ;
                    SDL_SetRenderDrawColor( renderer , 0xFF , 0x70 , 
                                            0x00 , 255 ) ;
                    SDL_RenderDrawRect( renderer , &rectangle ) ;
                }
            break ;

        case 6 :
            rectangle = { center_x - SQUARE_DIM / 2 ,
                          center_y - SQUARE_DIM ,
                          SQUARE_DIM , SQUARE_DIM } ;
            SDL_SetRenderDrawColor( renderer , 0xFF , 0x00 , 0x00 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0xF0 , 0x00 , 0x00 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            for( float i = -1.5 ; i < 1 ; i ++ )
            {
                rectangle = { (int)( center_x + i * SQUARE_DIM ) ,
                              center_y , SQUARE_DIM , SQUARE_DIM } ;
                SDL_SetRenderDrawColor( renderer , 0xFF , 0x00 , 0x00 , 255 ) ;
                SDL_RenderFillRect( renderer , &rectangle ) ;
                SDL_SetRenderDrawColor( renderer , 0xF0 , 0x00 , 0x00 , 255 ) ;
                SDL_RenderDrawRect( renderer , &rectangle ) ;
            }
            break ;

        case 3 : //Z
            for( int j = -1 ; j < 1 ; j ++ )
                for( float i = -1.5 ; i < 0 ; i ++ )
                {
                    rectangle = { (int)( center_x + (i+j+1) * SQUARE_DIM ) ,
                                  center_y + j * SQUARE_DIM ,
                                  SQUARE_DIM , SQUARE_DIM } ;
                    SDL_SetRenderDrawColor( renderer , 0xFF , 0xFF , 
                                            0x00 , 255 ) ;
                    SDL_RenderFillRect( renderer , &rectangle ) ;
                    SDL_SetRenderDrawColor( renderer , 0xF0 , 0xF0 , 
                                            0x00 , 255 ) ;
                    SDL_RenderDrawRect( renderer , &rectangle ) ;
                }
            break ;

        case 4  : //L
            rectangle = { center_x + SQUARE_DIM / 2 ,
                          center_y - SQUARE_DIM ,
                          SQUARE_DIM , SQUARE_DIM } ;
            SDL_SetRenderDrawColor( renderer , 0x00 , 0xFF , 0x00 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x00 , 0xF0 , 0x00 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            for(float i = -1.5 ; i < 1 ; i ++ )
            {
                rectangle = { (int)( center_x + i * SQUARE_DIM ) ,
                              center_y , SQUARE_DIM , SQUARE_DIM } ;
                SDL_SetRenderDrawColor( renderer , 0x00 , 0xFF , 0x00 , 255 ) ;
                SDL_RenderFillRect( renderer , &rectangle ) ;
                SDL_SetRenderDrawColor( renderer , 0x00 , 0xF0 , 0x00 , 255 ) ;
                SDL_RenderDrawRect( renderer , &rectangle ) ;
            }
            break ;
    }
}

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