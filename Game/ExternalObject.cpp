/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   ExternalObject.cpp -- Implementation file for the 'ExternalObject' class,
   which represents all objects that are not the player. Child of 'GameObject'.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Four 'int's, a pointer to a 'SpaceShip' object (the player), two
   'SDL_Surface' pointers, and an 'SDL_Rect' pointer passed to the constructor;
   'SDL_Surface' pointer and 'Radar' pointer passed to draw(); and 'SDL_Event'
   passed to update().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#include"ExternalObject.h"
#include"constants.h"
#include"globals.h"
#include"Radar.h"
#include"utilities.h"
#include"SDL.h"
#include<cstdlib>

#include<iostream>
#include<fstream>

ExternalObject::ExternalObject(int x, int y, int spread, SpaceShip *_player,
  ArtAsset *_artAsset, ArtAsset *_radarAsset, ResourceManager *rm):
  GameObject(_artAsset, _radarAsset, rm)
{
  float r, theta;

  player = _player;

  if(spread != 0) {
    r = rand() % abs(spread);
    theta = (PI * 2) * 
      (float(rand() % player->getNumSprites()) / player->getNumSprites());
    convertPolarToRect(r, theta, positionX, positionY);
  }
  positionX += - x;
  positionY += - y;

  spriteID = rand() % artAsset->getNumSprites();

  absoluteAngle = ((2 * PI * spriteID) / artAsset->getNumSprites()) + 0.5 * PI;

  removed = false;
}

ExternalObject::~ExternalObject() {}

void ExternalObject::draw(SDL_Surface *screen, Radar *radar)
{
  float xDiff, yDiff, relR, relTheta;
  xDiff = player->getPositionX() - positionX;
  yDiff = player->getPositionY() - positionY;
  convertRectToPolar(xDiff, yDiff, relR, relTheta);

  relTheta -= player->getAbsoluteAngle() - PI / 2;
  if(relTheta > 2 * PI)  relTheta -= 2 * PI;
  if(relTheta < -2 * PI)  relTheta += 2 * PI;

  convertPolarToRect(relR, relTheta, relativeX, relativeY);
  relativeX += player->getRelativeX() + player->getSpriteWidth() / 2 - artAsset->getWidth() / 2;
  relativeY += player->getRelativeY() + player->getSpriteHeight() / 2 - artAsset->getHeight() / 2;

  float bt = float(radar->getBorderThickness());
  float rw = radarAsset->getWidth();
  float rh = radarAsset->getHeight();
  float scale = radar->getScale();
  float playerX = player->getRelativeX();
  float playerY = player->getRelativeY();

  float radarX = radar->scaleX(xDiff/screen->w/scale);
  float radarY = radar->scaleY(yDiff/screen->h/scale);

  convertRectToPolar(radarX, radarY, relR, relTheta);

  relTheta -= player->getAbsoluteAngle() - PI / 2;
  if(relTheta > 2 * PI)  relTheta -= 2 * PI;
  if(relTheta < -2 * PI)  relTheta += 2 * PI;

  convertPolarToRect(relR, relTheta, radarX, radarY);
  radarX += player->getRadarX() + player->getRadarWidth() / 2 - radarAsset->getWidth() / 2;
  radarY += player->getRadarY() + player->getRadarHeight() / 2 - radarAsset->getHeight() / 2;

  if(radarX < bt - rw)
    radarX = bt - rw;
  else if(radarX > radar->getSurface()->w - bt - 1 + 0.5*rw)
    radarX = radar->getSurface()->w - 1 - bt + 0.5*rw;

  if(radarY < bt - rh)
    radarY = bt - rh;
  else if(radarY > radar->getSurface()->h - bt - 1 + 0.5*rh)
    radarY = radar->getSurface()->h - 1 - bt + 0.5*rh;

  applySurface(relativeX, relativeY, artAsset->getSurface(), screen,
    artAsset->getSprite(spriteID));
  if(radar->active())
    applySurface(radarX, radarY, radarAsset->getSurface(), radar->getSurface(),
      radarAsset->getSprite(rSpriteID));
}

void ExternalObject::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  //if(event.type == SDL_KEYDOWN)
  //  switch(event.key.keysym.sym) {
  //    case SDLK_LEFT:  rotateRight(); break;
  //    case SDLK_RIGHT: rotateLeft(); break;
  //  }

  if(keys[SDLK_LEFT] && !keys[SDLK_RIGHT]) rotateRight();
  else if(keys[SDLK_RIGHT] && !keys[SDLK_LEFT]) rotateLeft();

  int rNumSprites = radarAsset->getNumSprites();

  rSpriteID = round(((absoluteAngle - player->getAbsoluteAngle()) / (2*PI)) *
    rNumSprites);
  while(rSpriteID < 0)  rSpriteID += rNumSprites + 1;
  rSpriteID %= rNumSprites;

  GameObject::update(event, objects);
}

void ExternalObject::remove() {GameObject::remove();}

void ExternalObject::rotateLeft() {if(--spriteID < 0) spriteID += artAsset->getNumSprites();}

void ExternalObject::rotateRight() {++spriteID %= artAsset->getNumSprites();}

void ExternalObject::turnLeft()
{
  rotateLeft();
  absoluteAngle -= (2 * PI) / artAsset->getNumSprites();
  if(absoluteAngle < 0.0) absoluteAngle += 2 * PI;
}

void ExternalObject::turnRight()
{
  rotateRight();
  absoluteAngle += (2 * PI) / artAsset->getNumSprites();
  if(absoluteAngle > 2 * PI) absoluteAngle -= 2 * PI;
}

int ExternalObject::getRelativeX() {return player->getPositionX() - positionX;}

int ExternalObject::getRelativeY() {return player->getPositionY() - positionY;}

void ExternalObject::setAbsoluteX(int x)
{
  positionX = x + player->getPositionX();
}

void ExternalObject::setAbsoluteY(int y)
{
  positionY = y + player->getPositionY();
}