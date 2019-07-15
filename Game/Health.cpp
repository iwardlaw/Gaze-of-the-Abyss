/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"Health.h"
#include"constants.h"
#include"globals.h"
#include"utilities.h"

#include<iostream>
#include<iomanip>

Health::Health(int x, int y, int spread, SpaceShip *_player,
  ArtAsset *_artAsset, ArtAsset *_radarAsset, ResourceManager *_manager):
  ExternalObject(x, y, spread, _player, _artAsset, _radarAsset, _manager)
{
  if(artAsset == manager->getArtAsset(HEALTH_SM)) size = SMALL;
  else if(artAsset == manager->getArtAsset(HEALTH_MD)) size = MED;
  else if(artAsset == manager->getArtAsset(HEALTH_LG)) size = LARGE;
  else size = FULL;

  int min, max;

  if(size == FULL) {
    hpRestored = player->getMaxHealth();
    objectType = HEALTH_FL;
  }
  else {
    if(size == SMALL) {
      min = MIN_HEALTH_SM;
      max = MAX_HEALTH_SM;
      objectType = HEALTH_SM;
    }
    else if(size == MED) {
      min = MIN_HEALTH_MD;
      max = MAX_HEALTH_MD;
      objectType = HEALTH_MD;
    }
    else {
      min = MIN_HEALTH_LG;
      max = MAX_HEALTH_LG;
      objectType = HEALTH_LG;
    }

    hpRestored = rand() % (max - min) + min + 1;
  }
  //lifespan = _lifespan;
  flashDelayCounter = 1;
  rFlashIdleCounter = rFlashDelayCounter = 1;
  
  health = maxHealth = 0;
  damageCaused = 0;
  damageable = false;
  colliding = false;
}

Health::~Health() {}

int Health::getHpRestored() {return hpRestored;}

HealthSize Health::getSize() {return size;}

//int Health::getLifespan() {return lifespan;}

void Health::update(SDL_Event event, std::vector<GameObject*> &objects)
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
    player->heal(hpRestored);
    removed = true;
    //Mix_PlayChannel(-1, manager->getSFX(HEAL), 0);
    manager->playSound(HEAL, 0.0, 1000, 1000);
  }

  //if(lifespan < 0 && --lifespan == 0) removed = true;

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