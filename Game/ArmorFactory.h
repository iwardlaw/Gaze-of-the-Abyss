/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef ARMORFACTORY_H
#define ARMORFACTORY_H

#include"ExternalObjectFactory.h"
#include"Armor.h"

class ArmorFactory : public ExternalObjectFactory {
  public:
    virtual ExternalObject* create(int x, int y, int spread, SpaceShip *pl,
      ArtAsset *aAsset, ArtAsset *rAsset, ResourceManager *rm)
    {
      return (ExternalObject*)(new Armor(x, y, spread, pl, aAsset, rAsset, rm));
    }
};

#endif