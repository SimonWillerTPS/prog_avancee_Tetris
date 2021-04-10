#include "usefull_functions.hpp"
 
int main(int argc, char *argv[])
{
    Game* tetris = new Game( "Tétris" , 1000 , 1000 ) ;
    tetris->init() ;
    delete( tetris ) ;
}