#ifndef TIMER_HPP
#define TIMER_HPP

/**
 * @file 	timer.hpp
 * @brief 	Defines the Timer class.
 * @author 	Lazy Foo's Productions - http://lazyfoo.net/tutorials/SDL/
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

/**
 * @class   Timer
 * @brief   This class is used to calculate FPS and measure time in the game.
 */
class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

#endif