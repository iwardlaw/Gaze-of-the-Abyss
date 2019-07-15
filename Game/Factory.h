/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   Factory.h -- Header and implementation file for the 'Factory' class, which
   manages the actual object factories.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   'string', four 'int's, two 'SDL_Surface' pointers, 'SpaceShip' pointer, and
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

#ifndef FACTORY_H
#define FACTORY_H

#include"constants.h"
#include"ExternalObjectFactory.h"
#include"ArmorFactory.h"
#include"AsteroidFactory.h"
#include"BossFactory.h"
#include"HealthFactory.h"
#include"ItemFactory.h"
#include"NPCFactory.h"
#include"NPCAttackerFactory.h"
#include"NPCDefenderFactory.h"
#include"SpaceShip.h"
#include<map>
#include<string>

#include<iostream>

class Factory {
  private:
    std::map<std::string, ExternalObjectFactory*> inventory;
  public:
    Factory()
    {
      inventory[AST] = (ExternalObjectFactory*)(new AsteroidFactory);
      inventory[_NPC] = (ExternalObjectFactory*)(new NPCFactory);
      inventory[DEF] = (ExternalObjectFactory*) (new NPCDefenderFactory);
      inventory[ATK] = (ExternalObjectFactory*) (new NPCAttackerFactory);
      inventory[BOSS] = (ExternalObjectFactory*) (new BossFactory);
      inventory[HEALTH] = (ExternalObjectFactory*) (new HealthFactory);
      inventory[ARMOR] = (ExternalObjectFactory*) (new ArmorFactory);
      inventory[ITEM] = (ExternalObjectFactory*) (new ItemFactory);
    }

    ~Factory()
    {
      std::map<std::string, ExternalObjectFactory*>::iterator iter;

      for(iter=inventory.begin(); iter!=inventory.end(); ++iter)
        delete iter->second;
    }

    ExternalObject* create(std::string resource, int x, int y, int spread,
                      SpaceShip* player, ArtAsset *artAsset,
                      ArtAsset *radarAsset, ResourceManager *rm)
    {
      return inventory.find(resource)->second->create(x, y, spread, player,
               artAsset, radarAsset, rm);
    }
};

#endif