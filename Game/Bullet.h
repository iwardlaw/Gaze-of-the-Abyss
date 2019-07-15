/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef BULLET_H
#define BULLET_H

#include"ExternalObject.h"
#include"SpaceShip.h"
#include"SDL.h"

class Bullet : public ExternalObject {
  protected:
    GameObject *source;
    int lifespan, lifeCounter;
    float sourceVelocityX, sourceVelocityY;
  public:
    Bullet(GameObject*, SpaceShip*, ArtAsset*, ArtAsset*, int, ResourceManager*);
    virtual ~Bullet();
    virtual void update(SDL_Event, std::vector<GameObject*>&);
    //virtual void draw(SDL_Surface*, Radar*);
};

#endif