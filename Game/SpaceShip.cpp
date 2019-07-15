/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   SpaceShip.cpp -- Implementation file for the 'SpaceShip' class, which
   represents the player's vehicle. Child of 'GameObject'.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Three 'int's, two 'SDL_Surface' pointers, and an 'SDL_Rect' pointer passed
   to the constructor; 'SDL_Surface' pointer and 'Radar' pointer passed to
   draw(); and 'SDL_Event' passed to update().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#include"SpaceShip.h"
#include"constants.h"
#include"globals.h"
#include"ResourceManager.h"
#include"utilities.h"
#include"SDL.h"
#include<string>

#include<iostream>
#include<iomanip>

SpaceShip::SpaceShip(int screenWidth, int screenHeight, Radar *radar,
  ArtAsset *_artAsset, ArtAsset *_radarAsset, ResourceManager *rm):
  GameObject(_artAsset, _radarAsset, rm)
{
  relativeX = PLAYER_SCREEN_X_RATIO * (screenWidth - artAsset->getWidth());
  relativeY = PLAYER_SCREEN_Y_RATIO * (screenHeight - artAsset->getHeight());

  radarX = radar->scaleX(relativeX/screenWidth) + radar->getBorderThickness() +
           0.5 * radarAsset->getWidth();
  radarY = (relativeY/screenHeight) * radar->scaleY(relativeY/screenHeight) +
           radar->getBorderThickness() + 0.5 * radarAsset->getHeight();

  shootClock = shootDelay = PLAYER_INIT_SHOOT_DELAY;

  objectType = SS;
  alignment = ALLY;
  material = METAL;
  health = maxHealth = 300;
  armor = 0;
  maxArmor = MAX_ARMOR;
  lives = START_LIVES;
  maxLives = DEFAULT_MAX_LIVES;
  missiles = START_MISSILES;
  maxMissiles = DEFAULT_MAX_MISSILES;
  damageCaused = 10;
  damageable = true;

  exploded = false;
}

SpaceShip::~SpaceShip() {}

void SpaceShip::initialize()
{
  positionX = positionY = 0.0;
  velocityX = velocityY = 0.0;
  absoluteAngle = PI / 2;
  if(removed) {
    health = maxHealth;
    armor = 0;
  }
  removed = false;
  colliding = true;
  exploded = false;

  prepareStateInfo();
}

void SpaceShip::draw(SDL_Surface *screen, Radar *radar)
{
  if(!removed) {
    applySurface(relativeX, relativeY, artAsset->getSurface(), screen,
      artAsset->getSprite(spriteID));
    if(radar->active())
      applySurface(radarX, radarY, radarAsset->getSurface(), radar->getSurface(),
      radarAsset->getSprite(rSpriteID));
  }
}

void SpaceShip::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  if(!removed) {
    if(!keys[SDLK_UP] && !keys[SDLK_DOWN] && !keys[SDLK_b])
      thrustX = thrustY = 0.0;

    if(keys[SDLK_UP]) {
      thrustX = PLAYER_THRUST * cos(absoluteAngle);
      thrustY = PLAYER_THRUST * sin(absoluteAngle);
    }
    if(keys[SDLK_DOWN]) {
      thrustX = -PLAYER_THRUST * cos(absoluteAngle);
      thrustY = -PLAYER_THRUST * sin(absoluteAngle);
    }
    if(keys[SDLK_LEFT]) {
      absoluteAngle -= (2 * PI) / artAsset->getNumSprites();
      if(absoluteAngle < 0.0) absoluteAngle += (2 * PI);
    }
    if(keys[SDLK_RIGHT]) {
      absoluteAngle += (2 * PI) / artAsset->getNumSprites();
      if(absoluteAngle > 2 * PI) absoluteAngle -= (2 * PI);
    }
    if(keys[SDLK_b] || keys[SDLK_RCTRL]) {
      if(abs(velocityX) < 0.01) thrustX = -velocityX;
      else thrustX = -0.1 * velocityX;
      if(abs(velocityY) < 0.01) thrustY = -velocityY;
      else thrustY = -0.1 * velocityY;
    }
    if(rapidFireOn && keys[SDLK_SPACE] && shootClock == shootDelay) {
      manager->makeBullet(BULLET, this, this, objects, BULLET_START_LIFE);
      shootClock = 1;
    }

    GameObject::update(event, objects);

    if(shootClock < shootDelay) ++shootClock;

    if(getVelocity() > MAX_PLAYER_VEL) {
      velocityX = initVelX;
      velocityY = initVelY;
    }
  }
  else if(!exploded) {
    manager->makeExplosion(this, this, objects);
    exploded = true;
    colliding = false;
    removeLife();
  }
}

float SpaceShip::getRadarX() {return radarX;}

float SpaceShip::getRadarY() {return radarY;}

void SpaceShip::damage(int dmg)
{
    if(armor > 0)
      armor -= dmg;

    if(armor < 0) {
      health -= dmg + armor;
      armor = 0;
    }
    else if(armor == 0)
    health -= dmg;
}

void SpaceShip::enarmor(int hp)
{
  armor += hp;
  if(armor > maxArmor) armor = maxArmor;
}

void SpaceShip::addLives(int numLives)
{
  if(numLives < 0) removeLives(-numLives);
  else {
    lives += numLives;
    if(lives > maxLives) lives = maxLives;
  }
}

void SpaceShip::removeLives(int numLives)
{
  if(numLives < 0) addLives(-numLives);
  else {
    lives -= numLives;
    if(lives < 0) lives = 0;
  }
}

void SpaceShip::addLife() {if(++lives > maxLives) lives = maxLives;}

void SpaceShip::removeLife() {if(--lives < 0) lives = 0;}

int SpaceShip::getArmor() {return armor;}

int SpaceShip::getMaxArmor() {return maxArmor;}

int SpaceShip::getLives() {return lives;}

int SpaceShip::getMaxLives() {return maxLives;}

int SpaceShip::getNumMissiles() {return missiles;}

int SpaceShip::getMaxMissiles() {return maxMissiles;}

void SpaceShip::addMissiles(int numMissiles)
{
  if(numMissiles < 0) removeMissiles(-numMissiles);
  else {
    missiles += numMissiles;
    if(missiles > maxMissiles) missiles = maxMissiles;
  }
}

void SpaceShip::removeMissiles(int numMissiles)
{
  if(numMissiles < 0) addMissiles(-numMissiles);
  else {
    missiles -= numMissiles;
    if(missiles > 0) missiles = 0;
  }
}

void SpaceShip::addMissile() {if(++missiles > maxMissiles) missiles = maxMissiles;}

void SpaceShip::removeMissile() {if(--missiles < 0) missiles = 0;}