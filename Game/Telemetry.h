/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   Telemetry.h -- Header file defining the 'Telemetry' class, which maintains
   the game's telemetry surface.
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

#ifndef TELEMETRY_H
#define TELEMETRY_H

#include"SpaceShip.h"
#include"SDL.h"
#include"SDL_ttf.h"
#include<map>
#include<string>

class Telemetry {
  private:
    SDL_Surface *velocityMsg, *directionMsg, *positionMsg;
    SDL_Surface *collisionMsg, *damageMsg, *gravityMsg /*, *inertiaMsg, *rk4Msg*/;
    SDL_Surface *healthMsg, *ffMsg, *diffMsg, *livesMsg;
    TTF_Font *font;
    SDL_Color textColor, healthColor;
    SDL_Surface *surface;
    SDL_Rect offset, surfaceClipRect;
    int width, height, borderThickness;
    int r, g, b;
    int borderR, borderG, borderB;
    int fontOffsetX, fontOffsetY;
    bool onscreen;
  public:
    Telemetry(SDL_Surface*, std::map<std::string, std::string>&, int, int);
    ~Telemetry();
    SDL_Surface* getVelocityMsg();
    SDL_Surface* getDirectionMsg();
    SDL_Surface* getSurface();
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
    int getFontOffsetX();
    /* Getter for 'fontOffsetX', which is the horizontal font offset within the
         telemetry window.
       Postcondition: Returns 'fontOffsetX'.
       */
    int getFontOffsetY();
    /* Getter for 'fontOffsetY', which is the vertical font offset within the
         telemetry window.
       Postcondition: Returns 'fontOffsetY'.
       */
    void toggle();
    /* (De)activates radar.
       Postcondition: 'onscreen' = '!onscreen'.
       */
    bool active();
    /* Checks to see if the radar is active (onscreen).
       Postcondition: Returns 'onscreen'.
       */
    void update(SDL_Event, SpaceShip*);
    /* Updates the telemetry messages.
       Postcondition: If necessary, changes mesages tomatch current player
                      velocity, direction, and position and blits all messages
                      to the telemetry surface.
       */
    void applySurface(int x, int y, SDL_Surface* source,
           SDL_Surface* destination, SDL_Rect* clip);
    /* Blits a surface or portion of a surface to another surface.
       Postcondition: Rectangle 'clip' from 'source' is blit upon 'destination'
                      at coordinates ('x','y').
       */
};

#endif