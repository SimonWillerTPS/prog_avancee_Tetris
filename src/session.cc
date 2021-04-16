#include "session.hpp"

Session:: Session( int x , int y , int width , int height , int size , 
                   SDL_Renderer* renderer , TTF_Font* font , Mix_Music* music ,
                   Mix_Chunk* dropped , Mix_Chunk* gameover , Mix_Chunk* line ,
                   Mix_Chunk* rotate , int level ) :
                   orig_x( x ) , orig_y( y ) , width( width ) ,
                   height( height ) , tile_size( size ) , 
                   renderer( renderer ) , font( font ) , 
                   sound_dropped( dropped ) , sound_gameover( gameover ) ,
                   sound_line( line ) ,  sound_rotate( rotate ) ,
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
            return false ;
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

void Session:: update_board()
{
    if( board->isPieceFallen())
    {
        int waiter = 60 - (board->getLevel() * difficulty ) ;
        if( waiter < 10 ) waiter = 10 ;

        if( ++ fallenCounter > waiter)
        {
            Mix_PlayChannel( 1 , sound_dropped , 0 ) ;
            int a = board->deletePossibleLines() ;
            if( a > 0 ) Mix_PlayChannel( 1 , sound_line , 0 ) ;
            board->calculScore(a);
            fallenCounter = 0 ;
            board->newPiece() ;
            board->projectedPiece();
        }
    }
    
    if( board->GameOver())
    {
        Mix_HaltMusic() ;
        Mix_PlayChannel( 1 , sound_gameover , 0 ) ;
        SDL_Delay( 5000 ) ;
        running = false ;
    }

    board->updateLevel() ;
}

void Session:: use_key()
{
    switch( pressed_key )
    {
        case KEY_UP :
            board->destroyShadePiece();
            if( board->rotatePiece() ) 
                Mix_PlayChannel( 1 , sound_rotate , 0 ) ;
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
            board->holdPiece();
            break ;
        case KEY_SPACE :
            board->destroyShadePiece();
            board->dropPiece();
            fallenCounter = 60 ;
            break;
        default :
            break;
    }
    pressed_key = KEY_NULL ;
}

void Session:: render_board()
{
    SDL_SetRenderDrawColor( renderer , COLOR_BACKGROUND , 0xFF ) ;
    SDL_RenderClear( renderer ) ;
    
    for ( int i = 0 ; i < BOARD_HEIGHT ; i ++ )
        for ( int j = 0 ; j < BOARD_WIDTH ; j ++ )
        {
            render_square( j * tile_size , i * tile_size , 
                           board->getAreaContent( j , i )) ;
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

    rectangle = { orig_x + pos_x , orig_y + pos_y , 
                  tile_size , tile_size } ;

    switch( color )
    {
        case CYAN :
            SDL_SetRenderDrawColor( renderer , COLOR_O_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_O_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;

        case BLUE :
            SDL_SetRenderDrawColor( renderer , COLOR_I_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_I_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case GREEN :
            SDL_SetRenderDrawColor( renderer , COLOR_L_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_L_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case ORANGE :
            SDL_SetRenderDrawColor( renderer , COLOR_S_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_S_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case PURPLE :
            SDL_SetRenderDrawColor( renderer , COLOR_J_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_J_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case YELLOW :
            SDL_SetRenderDrawColor( renderer , COLOR_Z_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_Z_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case RED :
            SDL_SetRenderDrawColor( renderer , COLOR_T_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_T_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;

        case SHADE :
            SDL_SetRenderDrawColor( renderer , COLOR_SHADE_IN, 125 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_SHADE_OUT , 125 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
            
        case EMPTY :
            SDL_SetRenderDrawColor( renderer , COLOR_GRID_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_GRID_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            break ;
        
            
        default :
            break ;
    }
}

void Session:: render_holded()
{
    rectangle = { width / 2 - 11 * tile_size , 
                  height - 21 * tile_size  , 
                  5 * tile_size , 6 * tile_size } ;
    
    SDL_SetRenderDrawColor( renderer , COLOR_GRID_IN , 255 ) ;
    SDL_RenderFillRect( renderer , &rectangle ) ;
    SDL_SetRenderDrawColor( renderer , COLOR_GRID_OUT , 255 ) ;
    SDL_RenderDrawRect( renderer , &rectangle ) ;

    if( board->isHolded())
        renderPiece( board->getHoldedPieceType() , 
                     width / 2 - 6 * tile_size - 5 * tile_size / 2 ,
                     height - 20 * tile_size + 5 * tile_size / 2) ;

    level_surface = TTF_RenderText_Solid( font , "STOCK" ,
                                          { 255 , 255 , 255 } ) ; 
    level_texture = SDL_CreateTextureFromSurface( renderer , level_surface ) ; 
    SDL_FreeSurface( level_surface ) ;
    rectangle = { width / 2 - 10 * tile_size , 
                  height - 21 * tile_size  , 
                  3 * tile_size , 1 * tile_size } ;
    SDL_RenderCopy( renderer , level_texture , NULL , &rectangle ) ;
    SDL_DestroyTexture( level_texture ) ;
}

void Session:: render_next_piece()
{
    rectangle = { width / 2 + 6 * tile_size , 
                  height - 21 * tile_size  , 
                  5 * tile_size , 6 * tile_size } ;
    
    SDL_SetRenderDrawColor( renderer , COLOR_GRID_IN , 255 ) ;
    SDL_RenderFillRect( renderer , &rectangle ) ;
    SDL_SetRenderDrawColor( renderer , COLOR_GRID_OUT , 255 ) ;
    SDL_RenderDrawRect( renderer , &rectangle ) ;

    renderPiece( board->getNextPieceType() , 
                 width / 2 + 6 * tile_size + 5 * tile_size / 2 ,
                 height - 20 * tile_size + 5 * tile_size / 2) ;

    level_surface = TTF_RenderText_Solid( font , "NEXT" ,
                                          { 255 , 255 , 255 } ) ; 
    level_texture = SDL_CreateTextureFromSurface( renderer , level_surface ) ; 
    SDL_FreeSurface( level_surface ) ;
    rectangle = { width / 2 + 7 * tile_size , 
                  height - 21 * tile_size  , 
                  3 * tile_size , 1 * tile_size } ;
    SDL_RenderCopy( renderer , level_texture , NULL , &rectangle ) ;
    SDL_DestroyTexture( level_texture ) ;
}

void Session:: renderPiece( int type , int center_x , int center_y )
{
    switch( type )
    {
        case 0 :
            for( int i = -1 ; i < 1 ; i ++ )
                for( int j = -1 ; j < 1 ; j ++ )
                {
                    rectangle = { center_x + i * tile_size , 
                                  center_y + j * tile_size  , 
                                  tile_size , tile_size } ;
                    SDL_SetRenderDrawColor( renderer , COLOR_O_IN , 255 ) ;
                    SDL_RenderFillRect( renderer , &rectangle ) ;
                    SDL_SetRenderDrawColor( renderer , COLOR_O_OUT , 255 ) ;
                    SDL_RenderDrawRect( renderer , &rectangle ) ;
                }
            break ;

        case 1 :
            for( int i = -2 ; i < 2 ; i ++ )
            {
                rectangle = { center_x - tile_size / 2 ,
                              center_y + i * tile_size ,
                              tile_size , tile_size } ;
                SDL_SetRenderDrawColor( renderer , COLOR_I_IN , 255 ) ;
                SDL_RenderFillRect( renderer , &rectangle ) ;
                SDL_SetRenderDrawColor( renderer , COLOR_I_OUT , 255 ) ;
                SDL_RenderDrawRect( renderer , &rectangle ) ;
            }
            break ;

        case 5 :
            rectangle = { center_x - 3 * tile_size / 2 ,
                          center_y - tile_size ,
                          tile_size , tile_size } ;
            SDL_SetRenderDrawColor( renderer , COLOR_J_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_J_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            for(float i = -1.5 ; i < 1 ; i ++ )
            {
                rectangle = { (int)( center_x + i * tile_size ) ,
                              center_y , tile_size , tile_size } ;
                SDL_SetRenderDrawColor( renderer , COLOR_J_IN , 255 ) ;
                SDL_RenderFillRect( renderer , &rectangle ) ;
                SDL_SetRenderDrawColor( renderer , COLOR_J_OUT , 255 ) ;
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
                    SDL_SetRenderDrawColor( renderer , COLOR_S_IN , 255 ) ;
                    SDL_RenderFillRect( renderer , &rectangle ) ;
                    SDL_SetRenderDrawColor( renderer , COLOR_S_OUT , 255 ) ;
                    SDL_RenderDrawRect( renderer , &rectangle ) ;
                }
            break ;

        case 6 :
            rectangle = { center_x - tile_size / 2 ,
                          center_y - tile_size ,
                          tile_size , tile_size } ;
            SDL_SetRenderDrawColor( renderer , COLOR_T_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_T_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            for( float i = -1.5 ; i < 1 ; i ++ )
            {
                rectangle = { (int)( center_x + i * tile_size ) ,
                              center_y , tile_size , tile_size } ;
                SDL_SetRenderDrawColor( renderer , COLOR_T_IN , 255 ) ;
                SDL_RenderFillRect( renderer , &rectangle ) ;
                SDL_SetRenderDrawColor( renderer , COLOR_T_OUT , 255 ) ;
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
                    SDL_SetRenderDrawColor( renderer , COLOR_Z_IN , 255 ) ;
                    SDL_RenderFillRect( renderer , &rectangle ) ;
                    SDL_SetRenderDrawColor( renderer , COLOR_Z_OUT , 255 ) ;
                    SDL_RenderDrawRect( renderer , &rectangle ) ;
                }
            break ;

        case 4  : //L
            rectangle = { center_x + tile_size / 2 ,
                          center_y - tile_size ,
                          tile_size , tile_size } ;
            SDL_SetRenderDrawColor( renderer , COLOR_L_IN , 255 ) ;
            SDL_RenderFillRect( renderer , &rectangle ) ;
            SDL_SetRenderDrawColor( renderer , COLOR_L_OUT , 255 ) ;
            SDL_RenderDrawRect( renderer , &rectangle ) ;
            for(float i = -1.5 ; i < 1 ; i ++ )
            {
                rectangle = { (int)( center_x + i * tile_size ) ,
                              center_y , tile_size , tile_size } ;
                SDL_SetRenderDrawColor( renderer , COLOR_L_IN , 255 ) ;
                SDL_RenderFillRect( renderer , &rectangle ) ;
                SDL_SetRenderDrawColor( renderer , COLOR_L_OUT , 255 ) ;
                SDL_RenderDrawRect( renderer , &rectangle ) ;
            }
            break ;
    }
}

void Session:: render_text()
{
    string_level = "LEVEL " + std::to_string( board->getLevel()) ;
    string_lines = "LINES " + std::to_string( board->getLines()) ;
    string_score = "SCORE " + std::to_string( board->getScore()) ;
    
    level_surface = TTF_RenderText_Solid( font , 
                                          string_level.c_str() ,
                                          { 255 , 255 , 255 } ) ; 
    lines_surface = TTF_RenderText_Solid( font , 
                                          string_lines.c_str() ,
                                          { 255 , 255 , 255 } ) ; 
    score_surface = TTF_RenderText_Solid( font , 
                                          string_score.c_str() ,
                                          { 255 , 255 , 255 } ) ; 

    level_texture = SDL_CreateTextureFromSurface( renderer , level_surface ) ; 
    lines_texture = SDL_CreateTextureFromSurface( renderer , lines_surface ) ;
    score_texture = SDL_CreateTextureFromSurface( renderer , score_surface ) ;

    SDL_FreeSurface( level_surface ) ;
    SDL_FreeSurface( lines_surface ) ;
    SDL_FreeSurface( score_surface ) ;

    score_rect = { width / 2 - 11 * tile_size , 
                   height - 4 * tile_size ,
                   5 * tile_size , tile_size } ;
    
    level_rect = { width / 2 - 11 * tile_size , 
                   height - 3 * tile_size ,
                   5 * tile_size , tile_size } ;

    lines_rect = { width / 2 - 11 * tile_size , 
                   height - 2 * tile_size ,
                   5 * tile_size , tile_size } ;

    SDL_RenderCopy( renderer , level_texture , NULL , &level_rect ) ;
    SDL_RenderCopy( renderer , lines_texture , NULL , &lines_rect ) ;
    SDL_RenderCopy( renderer , score_texture , NULL , &score_rect ) ;

    SDL_DestroyTexture( level_texture ) ;
    SDL_DestroyTexture( lines_texture ) ;
    SDL_DestroyTexture( score_texture ) ;
}