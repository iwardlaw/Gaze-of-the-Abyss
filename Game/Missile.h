/*
   Isaac Wardlaw
   Beyond Project
   25 Aug 2014
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef MISSILE_H
#define MISSILE_H

#include"Bullet.h"

class Missile : public Bullet {
  protected:
    GameObject *target;
    float targetPosX, targetPosY;
    float targetVelX, targetVelY;
    int thrustDuration, thrustCounter;
    int coastDuration, coastCounter;
    virtual void pursueTarget();
  public:
    Missile(GameObject *src, GameObject *tgt, SpaceShip *pl, ArtAsset *aAsset, ArtAsset *rAsset,
      int _lifespan, ResourceManager *rm);
    virtual ~Missile();
    virtual void update(SDL_Event, std::vector<GameObject*>&);
};

#endif