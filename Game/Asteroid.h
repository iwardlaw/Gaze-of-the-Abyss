/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   Asteroid.h -- Header file defining the 'Asteroid' class, which represents 
   asteroids. Child of 'ExternalObject'.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Four 'int's, two 'SDL_Surface' pointers, and an 'SDL_Rect' pointer passed to
   the constructor; 'SDL_Event' passed to update().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#ifndef ASTEROID_H
#define ASTEROID_H

#include"ExternalObject.h"
#include<string>

class Asteroid : public ExternalObject {
  private:
    int spinDelay, spinCounter;
    bool posSpin;
  public:
    Asteroid(int, int, int, SpaceShip*, ArtAsset*, ArtAsset*, ResourceManager*);
    /* Constructor. Passes args to constructor of 'ExternalObject'.
       Postcondition: Asteroid constructed according to art assets and
                      constructor of 'ExternalObject'; spin direction and spin
                      speed are assigned randomly.
       */
    void update(SDL_Event, std::vector<GameObject*>&);
    /* Updates asteroid's state based on arg.
       Postcondition: Asteroid spins in its randomly assigned direction at its
                      randomly assigned speed.
       */
};

#endif