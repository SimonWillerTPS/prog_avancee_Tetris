#include "menu.hpp"

Menu:: Menu( int number_of_choices ) : number_of_choices( number_of_choices )
{
    for( int i = 0 ; i < number_of_choices ; i ++ )
        choices.push_back( Choice() ) ;
}

void Menu:: set_choice( int number , Choice choice )
{
    if( number >= (int) choices.size())
        return ;

    choices[ number ] = choice ;
}

Choice Menu:: get_choice( int number )
{
    if( number >= (int) choices.size())
        return VOID ;

    return choices[ number ] ;    
}