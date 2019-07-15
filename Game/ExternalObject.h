/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   ExternalObject.h -- Header file defining the 'ExternalObject' class, which
   represents all objects that are not the player. Child of 'GameObject'.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Four 'int's, a pointer to a 'SpaceShip' object (the player), two
   'SDL_Surface' pointers, and an 'SDL_Rect' pointer passed to the constructor;
   'SDL_Surface' pointer and 'Radar' pointer passed to draw(); and 'SDL_Event'
   passed to update().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#ifndef EXTERNALOBJECT_H
#define EXTERNALOBJECT_H

#include"GameObject.h"
#include"Radar.h"
#include"ResourceManager.h"
#include"SpaceShip.h"
#include"SDL.h"
#include<string>

#include<fstream>

class ExternalObject : public GameObject {
  protected:
    SpaceShip* player;
    void rotateLeft();
    void rotateRight();
    void turnLeft();
    void turnRight();
    int getRelativeX();
    int getRelativeY();
    void setAbsoluteX(int);
    void setAbsoluteY(int);
  public:
    ExternalObject(int, int, int, SpaceShip*, ArtAsset*, ArtAsset*,
      ResourceManager*);
    /* Constructor. The final four args are art assets.
       Postcondition: Initializes external object according to constructor of
                      'GameObject' at a random point within a circle centered
                      on ('x','y') with a radius of 'spread', facing a random
                      direction; the pointer to the player is used during the
                      object's lifetime.
       */
    virtual ~ExternalObject();
    /* Destructor. Does nothing.
       */
    void draw(SDL_Surface*, Radar*);
    /* Blits object to the surface pointed to by the 1st arg (screen) and its
         radar image to the surface of the 2nd arg (radar).
       Postcondition: Object blit with appropriate sprite to the appropriate
                      location on the screen and, if active, the radar relative
                      to the player; it does not appear on the screen if it is
                      without the player's field of view; its radar image
                      appears immediately inside the border if it is without
                      radar range.
       */
    virtual void update(SDL_Event, std::vector<GameObject*>&);
    /* Updates object's internal state based on arg.
       Postcondition: If LEFT is pressed, 'spriteID' incremented;
                      if RIGHT is pressed, 'spriteID' decremented.
       */
    void remove();
};

#endif