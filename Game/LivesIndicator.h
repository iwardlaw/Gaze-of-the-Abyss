/*
   Isaac Wardlaw
   05 Feb 2014
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef LIVESINDICATOR_H
#define LIVESINDICATOR_H

#include"SDL.h"
#include"SDL_ttf.h"
#include<map>
#include<string>

class LivesIndicator {
  private:
    SDL_Surface *surface;
    SDL_Rect offset, surfaceClipRect;
    TTF_Font *font;
    SDL_Color textColor;
    int width, height, borderThickness;
    int rFill, gFill, bFill;
    int borderR, borderG, borderB;
    bool onscreen;

    // Icon Assets
    SDL_Surface *iconSheet;
    SDL_Rect *iconSprites;

    // Icon Intermediate (Engine/Art Interaction)
    int iconSpriteID;
    int iconSpriteWidth;
    int iconSpriteHeight;
  public:
    LivesIndicator(SDL_Surface*, std::map<std::string, std::string>&, int, int);
    /* Constructor.
       Precondition: 2nd arg must contain values as provided by the resource
                     manager.
       Postcondition: All members set; offscreen = false.
       */
    ~LivesIndicator();
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
};

#endif