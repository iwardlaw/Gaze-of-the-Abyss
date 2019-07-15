/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"Item.h"
#include"constants.h"
#include"globals.h"
#include"utilities.h"

Item::Item(int x, int y, int spread, SpaceShip *pl, ArtAsset *aAsset,
  ArtAsset *rAsset, ResourceManager *rm): ExternalObject(x, y, spread, pl,
  aAsset, rAsset, rm)
{
  flashIdleCounter = flashDelayCounter= 1;
  rFlashIdleCounter = rFlashDelayCounter = 1;
  objectType = ITEM;
  health = maxHealth = 0;
  damageCaused = 0;
  damageable = false;
  colliding = false;
  spriteID = 0;
}

Item::~Item() {}

void Item::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  int prevSpriteID = spriteID;

  if(flashIdleCounter++ >= COLLECTIBLE_FLASH_IDLE) {
    if(flashDelayCounter++ >= COLLECTIBLE_FLASH_DELAY) {
      ++spriteID %= artAsset->getNumSprites();
      flashDelayCounter = 1;
    }
    if(spriteID < prevSpriteID) flashIdleCounter = 1;
  }

  int prevRSpriteID = rSpriteID;

  if(rFlashIdleCounter++ >= COLLECTIBLE_R_FLASH_IDLE) {
    if(rFlashDelayCounter++ >= COLLECTIBLE_R_FLASH_DELAY) {
      ++rSpriteID %= radarAsset->getNumSprites();
      rFlashDelayCounter = 1;
    }
    if(rSpriteID < prevRSpriteID) rFlashIdleCounter = 1;
  }

  float dist = getDist(positionX, positionY, player->getPositionX(), player->getPositionY());
  float sumOfRadii = boundingRadius + player->getBoundingRadius();
  
  if(dist <= sumOfRadii) {
    manager->addToInv(this);
    removed = true;
    manager->playSound(COLLECT, 0.0, 1000, 1000);
  }
  
  GameObject::update(event, objects);
}