#include "usefull_functions.hpp"
#define USAGE_ERROR 2

void error( std::string msg )
{
	std::cerr << "Error : " << msg << std::endl ;
}

int my_strtol( std::string str )
{
	char* tester ;
	int result = strtol( str.c_str() , &tester , 10 ) ;

	if(( result  == 0 ) && ( tester == str ))
		error( "String conversion error" ) ;
	
	else 
		return result ;

	return USAGE_ERROR ;
}