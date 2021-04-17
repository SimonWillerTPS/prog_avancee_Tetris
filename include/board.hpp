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
    Random_bag bag ;    /**< bag for  random generation of tetromino*/
    bool hold = false ; /**<If a piece is holded */
    bool canHold = true ; /**< If you can hold a piece */
    bool firstPiece = true ; /**< To know if it's the first piece */
    int linesCompleted = 0 ; /**< Number of lines completed dince the start*/
    int linesCompletedLevel = 0 ; /**<Lines completed each level */
    int score = 0 ; /**< Score of the game*/
    int level ; /**< Level of the game*/
    int area[BOARD_WIDTH][BOARD_HEIGHT]; /**<board array */

public:
 
    /**
	 * @brief	Constructor of the class Board.
     */
    Board( int level ) ;

    /**
	 * @brief	Destructor of the class Board.
	 */
    ~Board() ;
 
	/**
	 * @brief	Getter of the type of the holded piece.
     */ 
    int   getHoldedPieceType() ;

	/**
	 * @brief	Getter of the type of the next piece.
     */ 
    int   getNextPieceType() ;
    
    /**
	 * @brief	Getter of the number of lines completed.
     */ 
    int   getLines() ;

    /**
	 * @brief	Getter of the level of the game.
     */ 
    int   getLevel() ;

    /**
	 * @brief	Getter of the score of the game.
     */ 
    int   getScore() ;
    /**
	 * @brief	Get if a piece is holded.
     */ 
    bool  isHolded() ;
    /**
	 * @brief	Get the content of a specific area in the game board.
     */ 
    int   getAreaContent( int i , int j ) ;
  
	/**
	 * @brief	Checks the case that the piece will visit.
	 * @param	i ordinate of the board for the move
	 * @param	j abscissa of the board for the move
     * @param	P_x Pivot of the piece
     * @param	P_y Pivot of the piece
     * @param	t type of the piece
	 * @param	o orientation of the piece
     * @param	flag bool to know if we can do the move we wanted
	 * @param	visited list of bool of position visited
	*/  
    void Visited(int i, int j, int P_X, int P_Y, int t, int o, bool &flag, bool visited[][SIZE]);

    /**
	 * @brief	Checks the case that the piece will visit.
	 * @param	i ordinate of the board for the move
	 * @param	j abscissa of the board for the move
     * @param	P_x Pivot of the piece
     * @param	P_y Pivot of the piece
     * @param	t type of the piece
	 * @param	o orientation of the piece
     * @param	flag bool to know if we can do the move we wanted
	 * @param	visited list of bool of position visited
	*/
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