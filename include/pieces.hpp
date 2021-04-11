/* piece.h */
#ifndef PIECES_H
#define PIECES_H
 
#include "shape.hpp"

const int Piv_X = 1;
const int Piv_Y = 2;

enum Color {CYAN = 1, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED};
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
    Piece(const Piece &p);
 
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