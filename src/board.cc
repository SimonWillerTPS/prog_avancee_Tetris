#include "board.hpp"

Board::Board()
{
    srand(time(NULL));
    for(int i = 0; i < BOARD_WIDTH; ++i)
        for(int j = 0; j < BOARD_HEIGHT; ++j)
            area[i][j] = EMPTY;
    newPiece();
}

int Board:: getHoldedPieceType()
{
    return holdedPiece.getType() ;
}

void Board::Visited(int i, int j, int P_X, int P_Y, int t, int o, bool &flag, bool visited[][SIZE])
{
    if(P_X < 0 || P_Y >= SIZE || P_Y < 0 || P_Y >= SIZE || visited[P_X][P_Y] || SHAPE[t][o][P_X][P_Y] == EMPTY)
        return;
 
    visited[P_X][P_Y] = true;
 
    if(i < 0 || i >= BOARD_HEIGHT || j < 0 || j >= BOARD_WIDTH || area[j][i] != EMPTY)
    {
        flag = false;
        return;
    }
 
    Visited(i, j - 1, P_X, P_Y - 1, t, o, flag, visited);
    Visited(i + 1, j, P_X + 1, P_Y, t, o, flag, visited);
    Visited(i, j + 1, P_X, P_Y + 1, t, o, flag, visited);
    Visited(i - 1, j, P_X - 1, P_Y, t, o, flag, visited);
}

void Board::Fill(int i, int j, int P_X, int P_Y, int t, int o, int value, bool visited[][SIZE])
{
    if(P_X < 0 || P_X >= SIZE || P_Y < 0 || P_Y >= SIZE || visited[P_X][P_Y] || SHAPE[t][o][P_X][P_Y] == EMPTY)
        return;
 
    visited[P_X][P_Y] = true;
    area[j][i] = value;
 
    Fill(i, j - 1, P_X, P_Y - 1, t, o, value, visited);
    Fill(i + 1, j, P_X + 1, P_Y, t, o, value, visited);
    Fill(i, j + 1, P_X, P_Y + 1, t, o, value, visited);
    Fill(i - 1, j, P_X - 1, P_Y, t, o, value, visited);
}
 
void Board::Fill_draw(int i, int j, int P_X, int P_Y, int t, int o, int value)
{
    bool visited[SIZE][SIZE];
 
    for(int l = 0; l < SIZE; ++l)
        for(int m = 0; m < SIZE; ++m)
            visited[l][m] = false;
 
    Fill(i, j, P_X, P_Y, t, o, value, visited);
}

void Board::setCurPiece(Piece p)
{
    currentPiece = p;
}

int Board::getLines()
{
    return linesCompleted;
}

int Board::getLevel()
{
    return level;
}

int Board::getScore()
{
    return score ;
}

void Board::updateLevel()
{
    if (linesCompletedLevel >= 10)
    {
        level +=1;
        linesCompletedLevel -= 10;
    }
}
void Board::destroyPiece(Piece p)
{
    int i = p.getX();
    int j = p.getY();
 
    int k = p.getType();
    int o = p.getOrient();
 
    Fill_draw(i, j, Piv_X, Piv_Y, k, o, EMPTY);
}

int Board:: getNextPieceType()
{
    return nextPiece.getType() ;
}

void Board::newPiece()
{
    if( firstPiece )
    {    
        insertPiece( Piece(rand() % 7 , 0 )) ;
        nextPiece = Piece(rand() % 7 , 0 ) ;
        firstPiece = false ;
    }
    else
    {
        insertPiece( nextPiece ) ;
        nextPiece = Piece(rand() % 7 , 0 ) ;
    }
}


bool Board::isPieceMovable(int x, int y)
{
    destroyPiece(currentPiece);
    bool movable = true;
 
    bool visited[SIZE][SIZE];
 
    for(int l = 0; l < SIZE; ++l)
        for(int m = 0; m < SIZE; ++m)
            visited[l][m] = false;
 
    int t = currentPiece.getType();
    int o = currentPiece.getOrient();
 
    Visited(x, y, Piv_X, Piv_Y, t, o, movable, visited);
    
    drawPiece(currentPiece);
 
    return movable;
}

void Board::drawPiece(Piece p)
{
    int i = p.getX();
    int j = p.getY();
 
    int t = p.getType();
    int o = p.getOrient();

     
    switch(t)
    {
        case 0:  //I
            p.setColor(CYAN);
            break;
        case 1: //J
            p.setColor(BLUE);
            break;
        case 2: //L
            p.setColor(ORANGE);
            break;
        case 3: //O
            p.setColor(YELLOW);
            break;
        case 4: //S
            p.setColor(GREEN);
            break;
        case 5: //T
            p.setColor(PURPLE);
            break;
        case 6: //Z
            p.setColor(RED);
            break;
        default:
            break;
    }
    Fill_draw(i, j, Piv_X, Piv_Y, t, o, p.getColor());
}


bool Board::isPieceRotable(int o)
{
    destroyPiece(currentPiece);
 
    bool rotable = true;
 
    bool visited[SIZE][SIZE];
 
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j)
            visited[i][j] = false;
 
    int t = currentPiece.getType();
 
    Visited(currentPiece.getX(), currentPiece.getY(), Piv_X, Piv_Y, t, o, rotable, visited);
 
    drawPiece(currentPiece);
 
    return rotable;
}

void Board::rotatePiece()
{
    int o = currentPiece.getOrient();
 
    if(o != 3)
        o++;
    else
        o = 0;
 
    if(isPieceRotable(o))
    {
        destroyPiece(currentPiece);
        //destroyPiece(shadePiece);
        currentPiece.setOrient(o);
 
        drawPiece(currentPiece);
    }
}

void Board::movePieceDown()
{
    int x = currentPiece.getX();
    int y = currentPiece.getY();
 
    if(isPieceMovable(x + 1, y))
    {
        destroyPiece(currentPiece);
        currentPiece.setX(x + 1);
 
        drawPiece(currentPiece);
    }
}

bool Board::shadeDropTest(int x, int y)
{
    bool drop = true;
 
    bool visited[SIZE][SIZE];
 
    for(int l = 0; l < SIZE; ++l)
        for(int m = 0; m < SIZE; ++m)
            visited[l][m] = false;
 
    int t = shadePiece.getType();
    int o = shadePiece.getOrient();
 
    Visited(x, y, Piv_X, Piv_Y, t, o, drop, visited);
 
    return drop;
}

void Board::moveShadePieceDown()
{
    int x = shadePiece.getX();
    int y = shadePiece.getY();

        if (shadeDropTest(x + 1, y))
        {
            destroyPiece(shadePiece);
            shadePiece.setX(x + 1);
        }
}

void Board::dropShadePiece()
{
    int x = shadePiece.getX();
    int y = shadePiece.getY();
    while (shadeDropTest(x++,y))
        moveShadePieceDown();

}
 
void Board::movePieceLeft()
{
    int x = currentPiece.getX();
    int y = currentPiece.getY();
 
    if( isPieceMovable(x, y - 1))
    {
        destroyPiece(currentPiece);
        //destroyPiece(shadePiece);
        currentPiece.setY(y - 1);
 
        drawPiece(currentPiece);
    }
}
 
void Board::movePieceRight()
{
    int x = currentPiece.getX();
    int y = currentPiece.getY();
 
    if(isPieceMovable(x, y + 1))
    {
        destroyPiece(currentPiece);
        //destroyPiece(shadePiece);
        currentPiece.setY(y + 1);
 
        drawPiece(currentPiece);
    }
}
 

void Board::deleteLine(int y)
{
    destroyPiece(currentPiece);
 
    for(int j = y; j > 0; --j)
    {
        for(int i = 0; i < BOARD_WIDTH; ++i)
            area[i][j] = area[i][j-1];
    }
 
    drawPiece(currentPiece);
}
 
int Board::deletePossibleLines()
{
    int nbLinesDeleted = 0;
 
    for(int j = 0; j < BOARD_HEIGHT; ++j)
    {
        int i = 0;
 
        for(; i < BOARD_WIDTH && area[i][j] != EMPTY; ++i);
 
        if(i == BOARD_WIDTH)
        {
            nbLinesDeleted++;
            deleteLine(j);
        }
    }
    linesCompleted += nbLinesDeleted ;
    linesCompletedLevel += nbLinesDeleted ;
    return nbLinesDeleted;
}
 
void Board::dropPiece()
{
    int x = currentPiece.getX();
    int y = currentPiece.getY();
 
    while(isPieceMovable(x++, y))
        movePieceDown();
}
 
bool Board::isPieceFallen()
{
    int x = currentPiece.getX();
    int y = currentPiece.getY();
 
    if(isPieceMovable(x + 1, y))
        return false;
    
    canHold = true ;

    return true;
}

bool Board:: holdPiece()
{
    if( !canHold )
        return false ;

    if( !hold )
    {
        holdedPiece = currentPiece ;
        destroyPiece( currentPiece ) ;
        newPiece() ;
        hold = true ;
    }
    else
    {
        Piece buffer = holdedPiece ;
        holdedPiece = currentPiece ;
        destroyPiece( currentPiece ) ;
        insertPiece( buffer ) ;
    }
    canHold = false ; 
    return true ;
}

bool Board::isHolded()
{
    return hold ;
}

void Board:: insertPiece( Piece p )
{
    p.setOrient(0);
    p.setX(SPAWN_X);
    p.setY(SPAWN_Y);
 
    drawPiece(p);
 
    setCurPiece(p);
}

void Board::projectedPiece()
{
    destroyPiece(shadePiece);
    shadePiece.setX(currentPiece.getX()) ;
    shadePiece.setY(currentPiece.getY()) ;
    shadePiece.setType(currentPiece.getType());
    shadePiece.setOrient(currentPiece.getOrient());
    shadePiece.setColor(RED);
    dropShadePiece();
    drawPiece(shadePiece);
}

bool Board::GameOver()
{
    int posX = currentPiece.getX();
    int posY = currentPiece.getY();
    if((isPieceMovable(posX + 1, posY) == false) && (posX == 0 ))
    {
        return true;
    }
    return false;
}

void Board::clear()
{
    for(int i = 0; i < BOARD_WIDTH; ++i)
    {
        for(int j = 0; j < BOARD_HEIGHT; ++j)
            area[i][j] = EMPTY;
    }
}

int Board::calculScore(int line_Destroyed)
{
    switch(line_Destroyed)
    {
        case 1:
            score += 40 * (level + 1);
            break;
        case 2:
            score += 100 * (level + 1);
            break;
        case 3:
            score += 300 * (level + 1);
            break;
        case 4:
             score += 1200 * (level + 1);
             break;
         default:
             break;
    }
 
    return score;
}