/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"Explosion.h"
#include"constants.h"
#include"utilities.h"
#include"SDL_mixer.h"

#include<iostream>
#include<iomanip>

void Explosion::initSoundingCount() {soundingCount = 0;}

Explosion::Explosion(int x, int y, SpaceShip *_player, ArtAsset *_artAsset,
  ResourceManager *rm): ExternalObject(x, y, 0, _player, _artAsset, NULL, rm)
{
  counter = 1;
  soundCounter = 1;
  objectType = EXPLOSION;
  colliding = false;
  damageable = false;
  damageCaused = 0;
  health = maxHealth = 0;
  spriteID = 0;

  float dist = getDist(positionX, positionY, player->getPositionX(),
    player->getPositionY());

  //++soundingCount;
  //int excessiveExplosions = soundingCount - MAX_FULL_VOL_EXPLOSIONS;
  //if(excessiveExplosions < 1) excessiveExplosions = 1;
  //else if (excessiveExplosions > 1) excessiveExplosions *= 2;
  //manager->playSound(EXPLODE, dist, 500, 1000 / excessiveExplosions);

  if(++soundingCount <= MAX_FULL_VOL_EXPLOSIONS)
    manager->playSound(EXPLODE, dist, 500, 1000);
}

Explosion::~Explosion() {}

void Explosion::draw(SDL_Surface *screen, Radar *radar)
{
  float xDiff, yDiff, relR, relTheta;
  xDiff = player->getPositionX() - positionX;
  yDiff = player->getPositionY() - positionY;
  convertRectToPolar(xDiff, yDiff, relR, relTheta);

  relTheta -= player->getAbsoluteAngle() - PI * 0.5;
  if(relTheta > 2 * PI)  relTheta -= 2 * PI;
  if(relTheta < -2 * PI)  relTheta += 2 * PI;

  convertPolarToRect(relR, relTheta, relativeX, relativeY);
  relativeX += player->getRelativeX() + player->getSpriteWidth() / 2 - 50;
  relativeY += player->getRelativeY() + player->getSpriteHeight() / 2 - 50;

  applySurface(relativeX, relativeY, artAsset->getSurface(), screen,
    artAsset->getSprite(spriteID));
}

void Explosion::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  if(counter++ == EXPLOSION_LATENCY) {
    if(spriteID++ == artAsset->getNumSprites()) removed = true;
    counter = 1;
  }

  if(soundCounter < EXPLOSION_SOUND_DURATION) {
    ++soundCounter;
    if(soundCounter == EXPLOSION_SOUND_DURATION)
      --soundingCount;
  }

  prepareStateInfo();
  GameObject::update(event, objects);
}