#ifndef CHOICE_HPP
#define CHOICE_HPP

/**
 * @file 	choice.hpp
 * @brief 	Defines the Choice type.
 * @authors	Luca Scimone & Simon Willer
 */

/**
 * @typedef Choice
 * @enum    Choice
 * @brief   Type used to know the entry represented in the menu.
 */
typedef enum Choice
{
    MARATHON ,
    BATTLE ,
    EXIT ,
    SETTINGS ,
    VOID_CHOICE
} Choice ;

#endif