/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   ExternalObjectFactory.h -- Header and implementation file for the
   'ExternalObjectFactory' class, which is an abstract placeholder for its
   descendents.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Three 'int's, two 'SDL_Surface' pointers, 'SpaceShip' pointer, and
   an 'SDL_Rect' pointer passed to create().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   'ExternalObject' pointer returned from create().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#ifndef EXTERNALOBJECTFACTORY_H
#define EXTERNALOBJECTFACTORY_H

#include"ExternalObject.h"
#include"SpaceShip.h"

class ExternalObjectFactory {
  public:
    virtual ExternalObject* create(int, int, int, SpaceShip*, ArtAsset*,
                              ArtAsset*, ResourceManager*) = 0;
};

#endif