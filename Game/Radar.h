/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   Radar.h -- Header file defining the 'Radar' class, which maintains the
   game's radar surface.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   'SDL_Surface' pointer, a 'map' from a 'string' to a 'string', and two 'int's
   passed to constructor; 'float's for scaleX() and scaleY().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   'SDL_Surface' pointer returned from getSurface(), 'SDL_Rect' pointers from
   getOffset() and getSurfaceClipRect(), 'float's from getScale(), scaleX(),
   and scaleY(), int from getBorderThickness(), and 'bool' from active().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   It occurs to me that this may be better placed within a 'GUIObject'
   superclass; however, assuming that proper functionality is what is most
   important at the moment, I have left it standalone.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#ifndef RADAR_H
#define RADAR_H

#include"SDL.h"
#include<map>
#include<string>

class Radar {
  private:
    SDL_Surface *surface;
    SDL_Rect offset, surfaceClipRect;
    int width, height, borderThickness;
    float scale;
    int r, g, b;
    int borderR, borderG, borderB;
    bool onscreen;
  public:
    Radar(SDL_Surface*, std::map<std::string, std::string>&, int, int);
    /* Constructor.
       Precondition: 2nd arg must contain values as provided by the resource
                     manager.
       Postcondition: All members set; offscreen = false.
       */
    ~Radar();
    /* Destructor.
       Postcondition: Sets 'surface' to 'NULL'.
       */
    SDL_Surface* getSurface();
    /* Getter for 'surface'.
       Postcondition: Returns 'surface'.
       */
    SDL_Rect getOffset();
    /* Getter for 'offset'.
       Postcondition: Returns 'offset'.
       */
    SDL_Rect getSurfaceClipRect();
    /* Getter for 'surfaceClipRect', the clip rect for the actual surface,
         without the border.
       Postcondition: Returns 'surfaceClipRect'.
       */
    int getBorderThickness();
    /* Getter for 'borderThickness'.
       Postcondition: Returns 'borderThickness'.
       */
    float getScale();
    /* Getter for 'scale'.
       Postcondition: Returns 'scale'.
       */
    float scaleX(float);
    /* Helps scale the arg to a value appropriate for the radar size.
       Postcondition: Returns arg multiplied by drawing surface width.
       */
    float scaleY(float);
    /* Helps scale the arg to a value appropriate for the radar size.
       Postcondition: Returns arg multiplied by drawing surface height.
       */
    void toggle();
    /* (De)activates radar.
       Postcondition: 'onscreen' = '!onscreen'.
       */
    bool active();
    /* Checks to see if the radar is active (onscreen).
       Postcondition: Returns 'onscreen'.
       */
    void drawRects();
    /* Fills rectangles on the surface with the border and then plain black.
       Postcondition: Radar surface wiped of all objects.
       */
};

#endif