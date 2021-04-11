#ifndef BOARD_HPP
#define BOARD_HPP

#include "game.hpp"
#include "pieces.hpp"
#include "usefull_functions.hpp"
#include <time.h>

const int BOARD_HEIGHT = 20;
const int BOARD_WIDTH = 10;

const int SPAWN_X = 0;
const int SPAWN_Y = 5;

enum{EMPTY, FULL};

class Board
{

private:
    
    Piece currentPiece;
    Piece holdedPiece;
    Piece nextPiece;
    Piece shadePiece;
    bool hold = false ;
    bool canHold = true ;
    bool firstPiece = true ;
    int linesCompleted = 0 ;
    int linesCompletedLevel = 0 ;
    int score = 0 ;
    int level = 0 ;

 public:
    int area[BOARD_WIDTH][BOARD_HEIGHT];
 
    Board();
 
    void setCurPiece(Piece p);
    Piece getCurPiece();
    int getHoldedPieceType() ;
    int getNextPieceType() ;
    int getLinesCompleted() ;
    int getLevel() ;
    void updateLevel();

    bool isHolded() ;
    
    void Visited(int i, int j, int P_X, int P_Y, int t, int o, bool &flag, bool visited[][SIZE]);
    void Fill(int i, int j, int P_X, int P_Y, int t, int o, int value, bool visited[][SIZE]);
    void Fill_draw(int i, int j, int P_X, int P_Y, int t, int o, int value);

    void drawPiece(Piece p);
    void newPiece();

    void newPiece(Piece p);
    void destroyPiece(Piece p);
 
    bool isPieceMovable(int x, int y);
    bool isPieceRotable(int r);

    void rotatePiece();

    void movePieceDown();
    void movePieceLeft();
    void movePieceRight();
    
    bool isPieceFallen();
    
    void addLines(int y);
    void deleteLine(int l);
    int deletePossibleLines();

    void projectedPiece();
 
    bool holdPiece() ;
    void insertPiece( Piece p ) ;

    void dropPiece();
    void dropShadePiece();
    bool GameOver() ;
    int calculScore(int l);

    void clear();
};
 
#endif