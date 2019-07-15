/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"Armor.h"
#include"constants.h"
#include"globals.h"
#include"utilities.h"

Armor::Armor(int x, int y, int spread, SpaceShip *pl, ArtAsset *aAsset,
  ArtAsset *rAsset, ResourceManager *rm): ExternalObject(x, y, spread, pl,
  aAsset, rAsset, rm)
{
  armorRestored = ARMOR_DROP_VAL;
  flashDelayCounter = 1;
  rFlashIdleCounter = rFlashDelayCounter = 1;
  objectType = ARMOR;
  health = maxHealth = 0;
  damageCaused = 0;
  damageable = false;
  colliding = false;
}

Armor::~Armor() {}

int Armor::getArmorRestored() {return armorRestored;}

void Armor::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  if(flashDelayCounter++ >= HEALTH_FLASH_DELAY) {
    ++spriteID %= artAsset->getNumSprites();
    flashDelayCounter = 1;
  }

  int prevRSpriteID = rSpriteID;

  if(rFlashIdleCounter++ >= HEALTH_R_FLASH_IDLE) {
    if(rFlashDelayCounter++ >= HEALTH_R_FLASH_DELAY) {
      ++rSpriteID %= radarAsset->getNumSprites();
      rFlashDelayCounter = 1;
    }
    if(rSpriteID < prevRSpriteID) rFlashIdleCounter = 1;
  }

  float dist = getDist(positionX, positionY, player->getPositionX(), player->getPositionY());
  float sumOfRadii = boundingRadius + player->getBoundingRadius();
  
  if(dist <= sumOfRadii) {
    player->enarmor(armorRestored);
    removed = true;
    manager->playSound(ENARMOR, 0.0, 1000, 1000);
  }

  float xDiff = player->getPositionX() - positionX;
  float yDiff = player->getPositionY() - positionY;
  float relR, relTheta;
  convertRectToPolar(xDiff, yDiff, relR, relTheta);

  if(!player->dead() && keys[SDLK_e] && dist <= COLLECTIBLE_GRAB_DIST) {
    velocityX = (COLLECTIBLE_GRAB_VEL + abs(player->getVelocity())) * cos(relTheta);
    velocityY = (COLLECTIBLE_GRAB_VEL + abs(player->getVelocity())) * sin(relTheta);
  }
  else
    velocityX = velocityY = 0.0;

  prepareStateInfo();
  
  GameObject::update(event, objects);
}