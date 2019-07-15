/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef ARMOR_H
#define ARMOR_H

#include"ExternalObject.h"

class Armor : public ExternalObject {
  protected:
    int armorRestored;
    int flashDelayCounter;
    int rFlashIdleCounter, rFlashDelayCounter;
  public:
    Armor(int, int, int, SpaceShip*, ArtAsset*, ArtAsset*, ResourceManager*);
    virtual ~Armor();
    int getArmorRestored();
    virtual void update(SDL_Event, std::vector<GameObject*>&);
};

#endif