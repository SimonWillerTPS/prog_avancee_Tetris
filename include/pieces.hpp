/* piece.h */
#ifndef PIECES_H
#define PIECES_H
/**
 * @file	Pieces.hpp
 * @brief	Pieces used in the Tetris game.
 * @author	Simon Willer Luca Scimone
 */
#include "colors.hpp"

/**
 * @brief	Localisation of pieces pivot
 */
const int Piv_X = 1;
const int Piv_Y = 2;

enum Color {CYAN = 1, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED, SHADE};

/**
 * @brief 	Different types of pieces used in Tetris.
 * 
 * This class defines the differents pieces used in Tetris, with some usefull
 * attributes & methods used in this game.
 */
class Piece
{
 
private:
    int type; // Le type de la pièce
    int orient; // Sa rotation courante
    Color color; // Sa couleur
 
    int X; // Son ordonnée dans l'aire de jeu
    int Y; // Son abscisse dans l'aire de jeu
 
public:
    Piece();
    Piece(int k, int o);
    Piece( Piece* p);
 
    void setType(int k);
    void setOrient(int o);
 
    int getType();
    int getOrient();
 
    void setColor(Color c);
    int getColor();
 
    void setX(int x);
    int getX();
 
    void setY(int y);
    int getY();
};
 
#endif