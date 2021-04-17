#ifndef BOARD_HPP
#define BOARD_HPP

#include "pieces.hpp"
#include "random_bag.hpp"
#include "shape.hpp"

// Size of the play area
const int BOARD_HEIGHT = 20;
const int BOARD_WIDTH = 10;

// Places where the pieces appear
const int SPAWN_X = 0;
const int SPAWN_Y = 5;

enum{EMPTY, FULL};

/**
 * @brief 	Board class for the Tetris game.
 * 
 * This class defines the game board used in Tetris, with some usefull
 * attributes & methods used in this game.
 */
class Board
{

private:
    
    Piece currentPiece; /**< The piece we play with*/
    Piece holdedPiece;  /**< The piece we have stored*/
    Piece nextPiece;    /**< The next piece that will appear*/
    Piece shadePiece;   /**<The Projected piece or Ghost piece*/
    Random_bag bag ;    /**< */
    bool hold = false ; /**<If a piece is holded */
    bool canHold = true ; /**< */
    bool firstPiece = true ; /**< */
    int linesCompleted = 0 ; /**< */
    int linesCompletedLevel = 0 ; /**< */
    int score = 0 ; /**< */
    int level ; /**< */
    int area[BOARD_WIDTH][BOARD_HEIGHT]; /**< */

 public:
 
    // Constructor :
    Board( int level ) ;
    ~Board() ;
 
    // Accessors :
    int   getHoldedPieceType() ;
    int   getNextPieceType() ;
    int   getLines() ;
    int   getLevel() ;
    int   getScore() ;
    bool  isHolded() ;
    int   getAreaContent( int i , int j ) ;

    // Methods :    
    void Visited(int i, int j, int P_X, int P_Y, int t, int o, bool &flag, bool visited[][SIZE]);
    void Fill(int i, int j, int P_X, int P_Y, int t, int o, int value, bool visited[][SIZE]);
    void Fill_draw(int i, int j, int P_X, int P_Y, int t, int o, int value);

    void  setCurPiece(Piece p);
    void  setCurShadePiece(Piece p);

    Piece getCurPiece();
    Piece getCurShadePiece();

    void drawPiece(Piece p);
    void drawShadePiece(Piece p);
    void newPiece();

    void newPiece(Piece p);
    void destroyPiece(Piece p);
    void destroyShadePiece();
 
    bool isPieceMovable(int x, int y);
    bool isPieceRotable(int r);

    bool rotatePiece();
    void movePieceDown();
    void movePieceLeft();
    void movePieceRight();
    
    bool isPieceFallen();
    
    void addLines(int y);
    void deleteLine(int l);
    int  deletePossibleLines();
    int  deletePossibleLinesIA();
    int  pointsIA();

    bool isShadePieceMovable(int x, int y);
    void moveShadePieceDown();

    void projectedPiece();
 
    bool holdPiece() ;
    void insertPiece( Piece p ) ;

    void dropPiece();
    void dropShadePiece();
    bool GameOver() ;
    
    void updateLevel();
    int  calculScore(int l);

    void clear();
};
 
#endif