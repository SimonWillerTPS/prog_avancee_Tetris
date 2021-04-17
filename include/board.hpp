#ifndef BOARD_HPP
#define BOARD_HPP
/**
 * @file	board.hpp
 * @brief	Board used in the Tetris game.
 * @author	Simon Willer & Luca Scimone
 */

#include "pieces.hpp"
#include "random_bag.hpp"
#include "shape.hpp"

// Size of the play area
#define BOARD_HEIGHT    20 
#define BOARD_WIDTH     10 

// Places where the pieces appear
#define SPAWN_X 0
#define SPAWN_Y 5

enum{EMPTY, FULL};

/**
 * @class   Board
 * @brief 	Class for the Tetris game.
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
	 * @brief	Constructor of the class Board
     * @param   level starting level
     */
    Board( int level ) ;

    /**
	 * @brief	Destructor of the class Board
	 */
    ~Board() ;
 
	/**
	 * @brief	Getter of the type of the holded piece
     */ 
    int   getHoldedPieceType() ;

	/**
	 * @brief	Getter of the type of the next piece.
     */ 
    int   getNextPieceType() ;
    
    /**
	 * @brief	Getter of the number of lines completed
     */ 
    int   getLines() ;

    /**
	 * @brief	Getter of the level of the game
     */ 
    int   getLevel() ;

    /**
	 * @brief	Getter of the score of the game
     */ 
    int   getScore() ;

    /**
	 * @brief	Get if a piece is holded.
     */ 
    bool  isHolded() ;

    /**
	 * @brief	Get the content of a specific area in the game board
     */ 
    int   getAreaContent( int i , int j ) ;
  
	/**
	 * @brief	Checks the case that the piece will visit
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
	 * @brief	Fill the case of the board with the color of the piece
	 * @param	i ordinate of the board for the move
	 * @param	j abscissa of the board for the move
     * @param	P_x Pivot of the piece
     * @param	P_y Pivot of the piece
     * @param	t type of the piece
	 * @param	o orientation of the piece
     * @param	value color to fill the board with
	 * @param	visited list of bool of position visited
	*/
    void Fill(int i, int j, int P_X, int P_Y, int t, int o, int value, bool visited[][SIZE]);

    /**
	 * @brief	Fill the board with the color of the piece
	 * @param	i ordinate of the board for the move
	 * @param	j abscissa of the board for the move
     * @param	P_x Pivot of the piece
     * @param	P_y Pivot of the piece
     * @param	t type of the piece
	 * @param	o orientation of the piece
     * @param	value color of the piece
	*/
    void Fill_draw(int i, int j, int P_X, int P_Y, int t, int o, int value);

    /**
	 * @brief	Set the current piece
     * @param   p Piece
     */ 
    void  setCurPiece(Piece p);

    /**
	 * @brief	Set the current shade piece
     * @param   p Piece
     */ 
    void  setCurShadePiece(Piece p);

    /**
	 * @brief	Getter of the current piece
     */ 
    Piece getCurPiece();

    /**
	 * @brief	Getter of the current shade piece
     */ 
    Piece getCurShadePiece();

    /**
	 * @brief	Draw the piece on the board
     * @param   p Piece
     */ 
    void drawPiece(Piece p);

    /**
	 * @brief	draw the shade piece on the board
     * @param   p Piece
     */ 
    void drawShadePiece(Piece p);

    /**
	 * @brief	Make a new Piece
     */ 
    void newPiece();

    /**
	 * @brief	Make a new Piece
     * @param   p Piece
     */ 
    void newPiece(Piece p);

    /**
	 * @brief	Delete a Piece on the board
     * @param   p Piece
     */ 
    void destroyPiece(Piece p);

    /**
	 * @brief	Make a new Piece
     */ 
    void destroyShadePiece();

    /**
	 * @brief	check if we can move the piece the way we want
     * @param   x ordinate where the piece want to move
     * @param   y absciss wher the piece want to move
     */ 
    bool isPieceMovable(int x, int y);

    /**
	 * @brief	check if we can rotate the piece
     * @param   r currernt orientation of the piece
     */
    bool isPieceRotable(int r);

    /**
	 * @brief	rotate the curent piece
     */ 
    bool rotatePiece();

    /**
	 * @brief	move current piece down
     */ 
    void movePieceDown();

    /**
	 * @brief	move current piece left
     */ 
    void movePieceLeft();

    /**
	 * @brief	move current piece right
     */ 
    void movePieceRight();
    
    /**
	 * @brief	Know if the current piece has fallen
     */
    bool isPieceFallen();
    
    /**
	 * @brief	Add a line used against IA
     * @param   y number of lines to add
     */
    void addLines(int y);
    
    /**
	 * @brief	Delete a particular line
     * @param   l line to delete
     */
    void deleteLine(int l);

    /**
	 * @brief	Delete lines that are completed
     */
    int  deletePossibleLines();

    /**
	 * @brief	Know if we can delete lines with the IA move
     */
    int  deletePossibleLinesIA();

    /**
	 * @brief	points for the IA to know where to put the piece
     */
    int  pointsIA();

    /**
	 * @brief	check if we can move the shade piece the way we want
     * @param   x ordinate where the piece want to move
     * @param   y absciss wher the piece want to move
     */ 
    bool isShadePieceMovable(int x, int y);
    
    /**
	 * @brief	Know if we can delete lines with the IA move
     */
    void moveShadePieceDown();

    /**
	 * @brief	Fonction to create de shade piece
     */
    void projectedPiece();
    
    /**
	 * @brief	Store the current piece
     */
    bool holdPiece() ;
    
    /**
	 * @brief	insert a piece on the board that is holded the next piece
     * @param   p Piece
     */ 
    void insertPiece( Piece p ) ;

    /**
	 * @brief	Drop current piece
     */
    void dropPiece();
        
    /**
	 * @brief	Drop shade piece
     */
    void dropShadePiece();
    
    /**
	 * @brief	check if game is over or not
     */
    bool GameOver() ;
    
    /**
	 * @brief	Update the level of the game
     */
    void updateLevel();

    /**
	 * @brief	Update the level of the game
     * @param l number of line deleted
     */
    int  calculScore(int l);

    /**
	 * @brief	clear all pieces of the board
     */
    void clear();
};
 
#endif