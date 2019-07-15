/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef BOSS_H
#define BOSS_H

#include"NPCDefender.h"

class Boss : public NPCDefender {
  protected:
    int missileClock, missileDelay;
    void shoot(std::vector<GameObject*>&);
  public:
    Boss(int, int, int, SpaceShip*, ArtAsset*, ArtAsset*, ResourceManager*);
    virtual ~Boss();
    virtual void update(SDL_Event, std::vector<GameObject*>&);
};

#endif