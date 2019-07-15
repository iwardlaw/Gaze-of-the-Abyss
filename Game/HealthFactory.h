/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef HEALTHFACTORY_H
#define HEALTHFACTORY_H

#include"ExternalObjectFactory.h"
#include"Health.h"

class HealthFactory : public ExternalObjectFactory {
  public:
    ExternalObject* create(int x, int y, int spread, SpaceShip *_player,
      ArtAsset *_artAsset, ArtAsset *_radarAsset, ResourceManager *rm)
    {
      return (ExternalObject*)(new Health(x, y, spread, _player, _artAsset,
        _radarAsset, rm));
    }
};

#endif