#include "session.hpp"

Session:: Session( int x , int y , int width , int height , int size ,
                   SDL_Renderer* renderer , TTF_Font* font , int level ) :
                   orig_x( x ) , orig_y( y ) , width( width ) ,
                   height( height ) , tile_size( size ) , 
                   renderer( renderer ) , font( font ) , 
                   starting_level( level )
{
    board = new Board( starting_level ) ;

    event = new SDL_Event() ;

    fps_timer = new LTimer() ;
    cap_timer = new LTimer() ;

    running = true ;
}

Session:: ~Session()
{
    delete( board ) ;
    delete( event ) ;
    delete( fps_timer ) ;
    delete( cap_timer ) ;
}

bool Session:: run()
{
    fps_timer->start() ;

    while( running )
    {
        cap_timer->start() ;

        avgFPS = counted_frames / ( fps_timer->getTicks() / 1000.f ) ;
        if( avgFPS > 2000000 )
            avgFPS = 0 ;

        pressed_key = get_key( event ) ;
        if( pressed_key == KEY_QUIT )
            running = false ;
        else
            use_key() ;

        if( ++ down_counter > 60 - difficulty * board->getLevel())
        {
            board->movePieceDown() ;
            down_counter = 0 ;
        }
        
        update_board() ;
        render_board() ;

        counted_frames ++ ;
        frame_Ticks = cap_timer->getTicks() ;

        if( frame_Ticks < TICK_PER_FRAME )
            SDL_Delay( TICK_PER_FRAME - frame_Ticks ) ;
    }

    return true ;
}

void Session:: use_key()
{
    switch( pressed_key )
    {
        case KEY_UP :
            board->destroyShadePiece();
            board->rotatePiece();
            board->projectedPiece();
            break;
        case KEY_DOWN :
            board->movePieceDown();
            break;
        case KEY_LEFT :
            board->destroyShadePiece();
            board->movePieceLeft();
            board->projectedPiece();
            break;
        case KEY_RIGHT :
            board->destroyShadePiece();
            board->movePieceRight();
            board->projectedPiece();
            break;
        case KEY_STORE :
            board->destroyShadePiece();
            board->holdPiece();
            break ;
        case KEY_SPACE :
            board->destroyShadePiece();
            board->dropPiece();
            fallenCounter = 60 ;
            break;
        case KEY_QUIT :
            running= false ;
            break;
        default :
            break;
    }
    pressed_key = KEY_NULL ;
}

void Session:: render_board()
{
    SDL_SetRenderDrawColor( renderer , 0x03 , 0x41 , 0xAE , 0xFF ) ;
    SDL_RenderClear( renderer ) ;
    
    for ( int i = 0 ; i < BOARD_HEIGHT ; i ++ )
        for ( int j = 0 ; j < BOARD_WIDTH ; j ++ )
        {
            render_square( j * tile_size , i * tile_size , board->area[ j ][ i ]) ;
        }

    render_text() ;

    render_holded() ;
    
    render_next_piece() ;
    
    SDL_RenderPresent( renderer ) ;
}

void Session:: render_square( int pos_x , int pos_y , int color )
{
    int orig_x = width / 2 - 5 * tile_size ;
    int orig_y = height - 21 * tile_size ;

    SDL_Rect rectangle = { orig_x + pos_x , orig_y + pos_y , 
                           tile_size , tile_size } ;

    switch( color )
    {
        case CYAN :
            SDL_SetRenderDrawColor( renderer , 0x40 , 0xE0 , 0xD0 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x00 , 0xCE , 0xD1 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;

        case BLUE :
            SDL_SetRenderDrawColor( renderer , 0x00 , 0xBF , 0xFF , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x1E , 0x90 , 0xFF , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case GREEN :
            SDL_SetRenderDrawColor( renderer , 0x6B , 0x8E , 0x23 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x55 , 0x6B , 0x2F , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case ORANGE :
            SDL_SetRenderDrawColor( renderer , 0xFF , 0xA0 , 0x7A , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0xFF , 0x7F , 0x50 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case PURPLE :
            SDL_SetRenderDrawColor( renderer , 0x80 , 0x00 , 0x80 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x4B , 0x00 , 0x82 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case YELLOW :
            SDL_SetRenderDrawColor( renderer , 0xFF , 0xD7 , 0x00 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0xFF , 0xA5 , 0x00 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case RED :
            SDL_SetRenderDrawColor( renderer , 0xDC , 0x014 , 0x3C , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x8B , 0x00 , 0x00 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;

        case SHADE :
            SDL_SetRenderDrawColor( renderer , 0x80, 0x80, 0x80, 125 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x69 , 0x69 , 0x69 , 125 ) ;
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

void Session:: render_holded()
{
    SDL_Rect rectangle = { width / 2 - 11 * tile_size , 
                           height - 21 * tile_size  , 
                           5 * tile_size , 5 * tile_size } ;
    
    SDL_SetRenderDrawColor( renderer , 0 , 0 , 0 , 255 ) ;
    SDL_RenderFillRect( renderer , &rectangle ) ;
    SDL_SetRenderDrawColor( renderer , 30 , 30 , 30 , 255 ) ;
    SDL_RenderDrawRect( renderer , &rectangle ) ;

    if( board->isHolded())
        renderPiece( board->getHoldedPieceType() , 
                     width / 2 - 6 * tile_size - 5 * tile_size / 2 ,
                     height - 21 * tile_size + 5 * tile_size / 2) ;
}

void Session:: render_next_piece()
{
    SDL_Rect rectangle = { width / 2 + 6 * tile_size , 
                           height - 21 * tile_size  , 
                           5 * tile_size , 5 * tile_size } ;
    
    SDL_SetRenderDrawColor( renderer , 0 , 0 , 0 , 255 ) ;
    SDL_RenderFillRect( renderer , &rectangle ) ;
    SDL_SetRenderDrawColor( renderer , 30 , 30 , 30 , 255 ) ;
    SDL_RenderDrawRect( renderer , &rectangle ) ;

    renderPiece( board->getNextPieceType() , 
                 width / 2 + 6 * tile_size + 5 * tile_size / 2 ,
                 height - 21 * tile_size + 5 * tile_size / 2) ;
}

void Session:: update_board()
{
    if( board->isPieceFallen())
    {
        if( ++ fallenCounter > (60 - (board->getLevel() * difficulty )))
        {
            int a = board->deletePossibleLines() ;
            board->calculScore(a);
            fallenCounter = 0 ;
            board->newPiece() ;
            board->projectedPiece();
        }
    }
    
    if( board->GameOver())
    {
        running = false ;
    }

    board->updateLevel() ;
}

void Session:: renderPiece( int type , int center_x , int center_y )
{
    SDL_Rect rectangle ;
    switch( type )
    {
        case 0 :
            for( int i = -1 ; i < 1 ; i ++ )
                for( int j = -1 ; j < 1 ; j ++ )
                {
                    rectangle = { center_x + i * tile_size , 
                                  center_y + j * tile_size  , 
                                  tile_size , tile_size } ;
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
                rectangle = { center_x - tile_size / 2 ,
                              center_y + i * tile_size ,
                              tile_size , tile_size } ;
                SDL_SetRenderDrawColor( renderer , 0x00 , 0x00 , 0xFF , 255 ) ;
                SDL_RenderFillRect( renderer , &rectangle ) ;
                SDL_SetRenderDrawColor( renderer , 0x00 , 0x00 , 0xF0 , 255 ) ;
                SDL_RenderDrawRect( renderer , &rectangle ) ;
            }
            break ;

        case 5 :
            rectangle = { center_x + tile_size / 2 ,
                          center_y - tile_size ,
                          tile_size , tile_size } ;
            SDL_SetRenderDrawColor( renderer , 0x80 , 0x00 , 0x80 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x70 , 0x00 , 0x70 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            for(float i = -1.5 ; i < 1 ; i ++ )
            {
                rectangle = { (int)( center_x + i * tile_size ) ,
                              center_y , tile_size , tile_size } ;
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
                    rectangle = { (int)( center_x + ( i + j ) * tile_size ) ,
                                  center_y - j * tile_size ,
                                  tile_size , tile_size } ;
                    SDL_SetRenderDrawColor( renderer , 0xFF , 0x7F , 
                                            0x00 , 255 ) ;
                    SDL_RenderFillRect( renderer , &rectangle ) ;
                    SDL_SetRenderDrawColor( renderer , 0xFF , 0x70 , 
                                            0x00 , 255 ) ;
                    SDL_RenderDrawRect( renderer , &rectangle ) ;
                }
            break ;

        case 6 :
            rectangle = { center_x - tile_size / 2 ,
                          center_y - tile_size ,
                          tile_size , tile_size } ;
            SDL_SetRenderDrawColor( renderer , 0xFF , 0x00 , 0x00 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0xF0 , 0x00 , 0x00 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            for( float i = -1.5 ; i < 1 ; i ++ )
            {
                rectangle = { (int)( center_x + i * tile_size ) ,
                              center_y , tile_size , tile_size } ;
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
                    rectangle = { (int)( center_x + (i+j+1) * tile_size ) ,
                                  center_y + j * tile_size ,
                                  tile_size , tile_size } ;
                    SDL_SetRenderDrawColor( renderer , 0xFF , 0xFF , 
                                            0x00 , 255 ) ;
                    SDL_RenderFillRect( renderer , &rectangle ) ;
                    SDL_SetRenderDrawColor( renderer , 0xF0 , 0xF0 , 
                                            0x00 , 255 ) ;
                    SDL_RenderDrawRect( renderer , &rectangle ) ;
                }
            break ;

        case 4  : //L
            rectangle = { center_x + tile_size / 2 ,
                          center_y - tile_size ,
                          tile_size , tile_size } ;
            SDL_SetRenderDrawColor( renderer , 0x00 , 0xFF , 0x00 , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , 0x00 , 0xF0 , 0x00 , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            for(float i = -1.5 ; i < 1 ; i ++ )
            {
                rectangle = { (int)( center_x + i * tile_size ) ,
                              center_y , tile_size , tile_size } ;
                SDL_SetRenderDrawColor( renderer , 0x00 , 0xFF , 0x00 , 255 ) ;
                SDL_RenderFillRect( renderer , &rectangle ) ;
                SDL_SetRenderDrawColor( renderer , 0x00 , 0xF0 , 0x00 , 255 ) ;
                SDL_RenderDrawRect( renderer , &rectangle ) ;
            }
            break ;
    }
}

void Session:: render_text()
{
    string_level = "LEVEL : " + std::to_string( board->getLevel()) ;
    string_lines = "LINES : " + std::to_string( board->getLines()) ;
    string_score = "SCORE : " + std::to_string( board->getScore()) ;
    
    SDL_Surface* level_surface = TTF_RenderText_Solid( font , 
                                                       string_level.c_str() ,
                                                       { 255 , 255 , 255 } ) ; 
    SDL_Surface* lines_surface = TTF_RenderText_Solid( font , 
                                                       string_lines.c_str() ,
                                                       { 255 , 255 , 255 } ) ; 
    SDL_Surface* score_surface = TTF_RenderText_Solid( font , 
                                                       string_score.c_str() ,
                                                       { 255 , 255 , 255 } ) ; 

    level_texture = SDL_CreateTextureFromSurface( renderer , level_surface ) ; 
    lines_texture = SDL_CreateTextureFromSurface( renderer , lines_surface ) ;
    score_texture = SDL_CreateTextureFromSurface( renderer , score_surface ) ;

    SDL_FreeSurface( level_surface ) ;
    SDL_FreeSurface( lines_surface ) ;
    SDL_FreeSurface( score_surface ) ;

    SDL_Rect score_rect = { width / 2 - 11 * tile_size , 
                            height - 4 * tile_size ,
                            5 * tile_size , tile_size } ;
    
    SDL_Rect level_rect = { width / 2 - 11 * tile_size , 
                            height - 3 * tile_size ,
                            5 * tile_size , tile_size } ;

    SDL_Rect lines_rect = { width / 2 - 11 * tile_size , 
                            height - 2 * tile_size ,
                            5 * tile_size , tile_size } ;

    SDL_RenderCopy( renderer , level_texture , NULL , &level_rect ) ;
    SDL_RenderCopy( renderer , lines_texture , NULL , &lines_rect ) ;
    SDL_RenderCopy( renderer , score_texture , NULL , &score_rect ) ;
}