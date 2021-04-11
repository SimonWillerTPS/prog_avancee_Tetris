#ifndef MENU_HPP
#define MENU_HPP

#include <vector>

typedef enum Choice
{
    MARATHON ,
    EXIT ,
    VOID
} Choice ;

class Menu
{
    private :
        int                 number_of_choices ;
        std::vector<Choice> choices ;   

    public :
        Menu( int number_of_choices ) ;
        ~Menu() ;

        void    set_choice( int number , Choice choice ) ;
        Choice  get_choice( int number ) ;
} ;

#endif