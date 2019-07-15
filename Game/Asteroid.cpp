/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   Asteroid.cpp -- Implementation file for the 'Asteroid' class, which
   represents asteroids. Child of 'ExternalObject'.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Four 'int's, two 'SDL_Surface' pointers, and an 'SDL_Rect' pointer passed to
   the constructor; 'SDL_Event' passed to update().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#include"Asteroid.h"
#include"constants.h"
#include<string>

Asteroid::Asteroid(int x, int y, int offset, SpaceShip* _player,
  ArtAsset *_artAsset, ArtAsset *_radarAsset, ResourceManager *rm):
  ExternalObject(x, y, offset, _player, _artAsset, _radarAsset, rm)
{
  spinDelay = (rand() % MAX_AST_SPIN_DELAY) + 1;
  spinCounter = 1;
  posSpin = rand() % 2;
  //adjustPosition();
  
  objectType = AST;
  material = ROCK;
  health = maxHealth = 30;
  damageCaused = 10;
  damageable = true;
}

void Asteroid::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  if(spinCounter++ == spinDelay)
    if(posSpin)  ++spriteID;
    else  --spriteID;

  if(spinCounter > spinDelay)  spinCounter = 1;

  if(spriteID < 0)  spriteID += artAsset->getNumSprites();
  spriteID %= artAsset->getNumSprites();

  GameObject::update(event, objects);

  if(removed) {
    manager->makeExplosion(this, player, objects);

    int i = rand() % 10;
    if(i < 4 /*&& player->getHealth() < player->getMaxHealth()*/) {
    //if(i < 2 && player->getHealth() < player->getMaxHealth()) {
      HealthSize size;
      i = rand() % 100;
      if(i < 70) size = SMALL;
      else if(i < 90) size = MED;
      else if(i < 99) size = LARGE;
      else size = FULL;

      manager->dropHealth(size, this, player, objects);
    }
    else if(i < 7)
    //else if(i < 3 /*&& player->getArmor() < player->getMaxArmor()*/)
    //if(i >= 2 && i < 3 && player->getArmor() < player->getMaxArmor())
      manager->dropArmor(this, player, objects);
  }
  else if(getVelocity() > MAX_AST_VEL) {
    velocityX = initVelX;
    velocityY = initVelY;
  }
}