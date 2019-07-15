/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include"SDL.h"
#include"SDL_ttf.h"
#include<map>
#include<string>

class SpaceShip;

class Healthbar {
  private:
    SDL_Surface *surface;
    SDL_Rect offset, surfaceClipRect;
    TTF_Font *font;
    SDL_Color textColor, armorColor;
    int width, height, borderThickness;
    int rFill, gFill, bFill;
    int fullR, fullG, fullB;
    int emptyR, emptyG, emptyB;
    int armorR, armorG, armorB;
    int borderR, borderG, borderB;
    bool onscreen;
  public:
    Healthbar(SDL_Surface*, std::map<std::string, std::string>&, int, int);
    /* Constructor.
       Precondition: 2nd arg must contain values as provided by the resource
                     manager.
       Postcondition: All members set; offscreen = true.
       */
    ~Healthbar();
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
    void toggle();
    /* (De)activates radar.
       Postcondition: 'onscreen' = '!onscreen'.
       */
    bool active();
    /* Checks to see if the radar is active (onscreen).
       Postcondition: Returns 'onscreen'.
       */
    void update(SpaceShip*);
};

#endif