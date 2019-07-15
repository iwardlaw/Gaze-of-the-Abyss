/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   SpaceShip.h -- Header file defining the 'SpaceShip' class, which represents
   the player's vehicle. Child of 'GameObject'.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Three 'int's, two 'SDL_Surface' pointers, and an 'SDL_Rect' pointer passed
   to the constructor; 'SDL_Surface' pointer and 'Radar' pointer passed to
   draw(); and 'SDL_Event' passed to update().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include"GameObject.h"
#include"Radar.h"
#include"SDL.h"
#include<string>
#include<map>

class SpaceShip : public GameObject {
  protected:
    float radarX, radarY;
    int shootClock, shootDelay;
    int missiles, maxMissiles;
    int armor, maxArmor;
    int lives, maxLives;
    bool exploded;
  public:
    SpaceShip(int, int, Radar*, ArtAsset*, ArtAsset*, ResourceManager*);
    /* Constructor.
       Postcondition: Initializes player's ship according to the 'GameObject'
                      constructor and fixes its sprite at halfway across the
                      screen and three-fourths down, facing up; absolute
                      coordinates are (0, 0), and absolute direction is north.
       */
    virtual ~SpaceShip();
    /* Destructor. Does nothing.
       */
    void initialize();

    void draw(SDL_Surface*, Radar*);
    /* Blits the player's ship to the surface pointed to by the 1st arg
         (screen) and its radar imgae to the surface of the 2nd arg (radar).
       Postcondition: applySurface() called using ship's relative (x, y) on
                      both the screen and, if it is active, the radar; since
                      this position is relative to itself, there is no apparent
                      change.
       */
    void update(SDL_Event, std::vector<GameObject*>&);
    /* Updates player's state based on arg.
       Postcondition: Player moves forward in absolute space if UP is pressed,
                      rotates counterclockwise in absolute space if LEFT is
                      pressed, or rotates clockwise in absolute space if RIGHT
                      is pressed.
       */
    float getRadarX();
    /* Getter for 'radarX'.
       Postcondition: Returns 'radarX'.
       */
    float getRadarY();
    /* Getter for 'radarY'.
       Postcondition: Returns 'radarY'.
       */
    void damage(int dmg);

    void enarmor(int hp);

    void addLives(int numLives);

    void removeLives(int numLives);

    void addLife();

    void removeLife();

    int getArmor();

    int getMaxArmor();

    int getLives();

    int getMaxLives();

    int getNumMissiles();

    int getMaxMissiles();

    void addMissiles(int numMissiles);

    void removeMissiles(int numMissiles);

    void addMissile();

    void removeMissile();
};

#endif