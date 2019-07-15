/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef ITEM_H
#define ITEM_H

#include"ExternalObject.h"

class Item : public ExternalObject {
  protected:
    int flashIdleCounter, flashDelayCounter;
    int rFlashIdleCounter, rFlashDelayCounter;
  public:
    Item(int, int, int, SpaceShip*, ArtAsset*, ArtAsset*, ResourceManager*);
    virtual ~Item();
    virtual void update(SDL_Event, std::vector<GameObject*>&);
};

#endif