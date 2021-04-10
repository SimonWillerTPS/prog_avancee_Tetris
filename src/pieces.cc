/* piece.cpp */
#include "pieces.hpp"
 
Piece::Piece()
{

}
 
Piece::Piece(int t, int o)
{
    type = t;
    orient = o;
}
 
Piece::Piece(const Piece &p)
{
    type = p.type;
    orient = p.orient;
    color = p.color;
    X = p.X;
    Y = p.Y;
}
 
void Piece::setType(int t)
{
    type = t;
}
 
void Piece::setOrient(int o)
{
    orient = o;
}
 
int Piece::getType()
{
    return type;
}
 
int Piece::getOrient()
{
    return orient;
}
 
void Piece::setColor(int c)
{
    color = c;
}
 
int Piece::getColor()
{
    return color;
}
 
void Piece::setX(int x)
{
    X = x;
}
 
int Piece::getX()
{
    return X;
}
 
void Piece::setY(int y)
{
    Y = y;
}
 
int Piece::getY()
{
    return Y;
}