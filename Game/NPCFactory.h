/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   NPCFactory.h -- Header and implementation file for the 'NPCFactory' class,
   which dynamically creates 'NPC' instances.
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

#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include"ExternalObjectFactory.h"
#include"NPC.h"
#include"SpaceShip.h"
#include<string>

#include<iostream>

class NPCFactory : public ExternalObjectFactory {
  public:
    virtual ExternalObject* create(int x, int y, int spread,
                              SpaceShip *_player, ArtAsset *artAsset,
                              ArtAsset *radarAsset, ResourceManager *rm)
    {
      return (ExternalObject*)(new NPC(x, y, spread, _player, artAsset,
                                     radarAsset, rm));
    }
};

#endif