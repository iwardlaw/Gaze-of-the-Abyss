/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef NPCATTACKER_H
#define NPCATTACKER_H

#include"NPCDefender.h"

class NPCAttacker : public NPCDefender {
  public:
    NPCAttacker(int, int, int, SpaceShip*, ArtAsset*, ArtAsset*, ResourceManager*);
    virtual ~NPCAttacker();
    virtual void update(SDL_Event, std::vector<GameObject*>&);
};

#endif