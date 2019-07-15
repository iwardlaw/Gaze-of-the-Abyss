/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef NPCATTACKERFACTORY_H
#define NPCATTACKERFACTORY_H

#include"NPCFactory.h"
#include"NPCAttacker.h"

class NPCAttackerFactory : public NPCFactory {
  public:
    virtual ExternalObject* create(int x, int y, int spread,
                              SpaceShip *_player, ArtAsset *artAsset,
                              ArtAsset *radarAsset, ResourceManager *rm)
    {
      return (ExternalObject*)(new NPCAttacker(x, y, spread, _player, artAsset,
                                     radarAsset, rm));
    }
};

#endif