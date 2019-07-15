/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include"ExternalObjectFactory.h"
#include"Item.h"

class ItemFactory : public ExternalObjectFactory {
  public:
    virtual ExternalObject* create(int x, int y, int spread, SpaceShip *pl,
      ArtAsset *aAsset, ArtAsset *rAsset, ResourceManager *rm)
    {
      return (ExternalObject*)(new Item(x, y, spread, pl, aAsset, rAsset, rm));
    }
};

#endif