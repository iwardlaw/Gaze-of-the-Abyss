/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
   File by Keith Bush, PhD
   26 Jan 2012
   ========================
   File Description:
   Timer.h -- Header file for the 'Timer' class.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   'bool's for is_started() and is_paused().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#ifndef TIMER_H
#define TIMER_H

#include"SDL.h"
#include"SDL_image.h"
#include"SDL_ttf.h"

class Timer {
  private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

  public:
    //Initializes variables
    Timer();
    /* Constructor.
       Postcondition: All members = 0 (or 'false').
       */

    //The various clock actions
    void start();
    /* Starts clock.
       Postcondition: 'started' = 'true';
                      'paused' = 'false';
                      'startTicks' set.
       */
    void stop();
    /* Stops clock.
       Postcondition: 'started' = 'false';
                      'paused' = 'false'.
       */
    void pause();
    /* Pauses clock.
       Postcondition: If started and not paused, 'paused' = 'true' and
                      'pausedTicks' calculated.
       */
    void unpause();
    /* Unpauses clock.
       Postcondition: If paused, 'paused' = false, 'startTicks' calculated, and
                      'pausedTicks' reset to 0.
       */

    //Gets the timer's time
    int get_ticks();
    /* Returns applicable ticks.
       Postcondtion: If started and paused, returns 'pausedTicks';
                     if started and unpaused, returns offset of 'startTicks'.
       */

    //Checks the status of the timer
    bool is_started();
    /* Checker for 'started'.
       Postcondition: Returns 'started'.
       */
    bool is_paused();
    /* Checker for 'paused'.
       Postcondition: Returns 'paused'.
       */
};


#endif