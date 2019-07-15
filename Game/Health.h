/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef HEALTH_H
#define HEALTH_H

#include"ExternalObject.h"

class Health : public ExternalObject {
  protected:
    HealthSize size;
    int hpRestored;
    //int lifespan;
    int /*flashIdleCounter,*/ flashDelayCounter;
    int rFlashIdleCounter, rFlashDelayCounter;
  public:
    Health(int, int, int, SpaceShip*, ArtAsset*, ArtAsset*, ResourceManager*);
    virtual ~Health();
    int getHpRestored();
    HealthSize getSize();
    //int getLifespan();
    virtual void update(SDL_Event, std::vector<GameObject*>&);
};

#endif