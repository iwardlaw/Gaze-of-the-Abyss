/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef NPCDEFENDERFACTORY_H
#define NPCDEFENDERFACTORY_H

#include"NPCFactory.h"
#include"NPCDefender.h"

class NPCDefenderFactory : public NPCFactory {
  public:
    virtual ExternalObject* create(int x, int y, int spread,
                              SpaceShip *_player, ArtAsset *artAsset,
                              ArtAsset *radarAsset, ResourceManager *rm)
    {
      return (ExternalObject*)(new NPCDefender(x, y, spread, _player, artAsset,
                                     radarAsset, rm));
    }
};

#endif