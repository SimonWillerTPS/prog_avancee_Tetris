/* piece.h */
#ifndef PIECES_H
#define PIECES_H
/**
 * @file	Pieces.hpp
 * @brief	Pieces used in the Tetris game.
 * @authors	Simon Willer & Luca Scimone
 */
#include "colors.hpp"

/**
 * @brief	Localisation of pieces pivot
 */
const int Piv_X = 1;
const int Piv_Y = 2;
/**
 * @brief	8 colors used in Chess.
 */
enum Color {CYAN = 1, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED, SHADE};

/**
 * @class   Piece
 * @brief 	Different types of pieces used in Tetris.
 * 
 * This class defines the differents pieces used in Tetris, with some usefull
 * attributes & methods used in this game.
 */
class Piece
{
 
private:
    int type; /**< Type of the piece 
								(for the specific moves)*/
    int orient; /**<Its current rotation*/
    Color color; /**< Color of the piece*/
 
    int X; /**< Piece ordinate on the game Board*/
    int Y; /**< Piece abscissa on the game Board*/

public:
    /**
	 * @brief	Constructor of the class Pieces.
     */
    Piece();

    /**
	 * @brief	Constructor of the class Pieces.
     * @param	t : type of the piece
	 * @param	o : orientation of the piece
     */
    Piece(int t, int o);

    /**
	 * @brief   Copy method of piece
     * @param	p : Piece
     */
    Piece( Piece* p);
    
	/**
	 * @brief	Setter of the type of the piece.
     */    
    void setType(int t);

    /**
	 * @brief	Setter of the orinetation of the piece.
     */  
    void setOrient(int o);

    /**
	 * @brief	Getter of the type of the piece.
     */
    int getType();

    /**
	 * @brief	Getter of the orinetation of the piece.
     */  
    int getOrient();

    /**
	 * @brief	Setter of the color of the piece.
     */  
    void setColor(Color c);

    /**
	 * @brief	Getter of the color of the piece.
     */ 
    int getColor();

    /**
	 * @brief	Setter of the ordinate of the piece.
     */ 
    void setX(int x);

    /**
	 * @brief	Getter of the ordinate of the piece.
     */     
    int getX();

    /**
	 * @brief	Setter of the abscissa of the piece.
     */ 
    void setY(int y);

    /**
	 * @brief	Getter of the abscissa of the piece.
     */
    int getY();
};
 
#endif