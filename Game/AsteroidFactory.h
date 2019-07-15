/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   AsteroidFactory.h -- Header and implementation file for the
   'AsteroidFactory' class, which dynamically creates 'Asteroid' instances.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Four 'int's, two 'SDL_Surface' pointers, 'SpaceShip' pointer, and
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

#ifndef ASTEROIDFACTORY_H
#define ASTEROIDFACTORY_H

#include"ExternalObjectFactory.h"
#include"Asteroid.h"
#include"SpaceShip.h"

class AsteroidFactory : public ExternalObjectFactory {
  public:
    virtual ExternalObject* create(int x, int y, int spread,
                              SpaceShip *_player, ArtAsset *artAsset,
                              ArtAsset *radarAsset, ResourceManager *rm)
    {
      return (ExternalObject*)(new Asteroid(x, y, spread, _player, artAsset,
                                     radarAsset, rm));
    }
};

#endif