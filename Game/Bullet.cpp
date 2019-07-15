/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"Bullet.h"
#include"constants.h"
#include"globals.h"
#include"utilities.h"
#include"SDL_mixer.h"

#include<iostream>
#include<iomanip>

Bullet::Bullet(GameObject *src, SpaceShip *player, ArtAsset *_artAsset,
  ArtAsset *_radarAsset, int _lifespan, ResourceManager *rm):
  ExternalObject(0, 0, 0, player, _artAsset, _radarAsset, rm)
{
  source = src;

  //if((source->getPositionX() > 1000.0 || source->getPositionX() < -1000.0) &&
  //    source->getPositionY() > 1000.0 || source->getPositionY() < -1000.0)
  //  int i = 0;

  absoluteAngle = source->getAbsoluteAngle();
  positionX = source->getPositionX() + (source->getBoundingRadius()+20) * cos(absoluteAngle);
  positionY = source->getPositionY() + (source->getBoundingRadius()+20) * sin(absoluteAngle);
  lifespan = _lifespan;
  lifeCounter = 0;

  sourceVelocityX = source->getVelocityX();
  sourceVelocityY = source->getVelocityY();
  velocityX = BULLET_VEL * cos(absoluteAngle);
  velocityY = BULLET_VEL * sin(absoluteAngle);

  //mass = 0.01;
  mass = 100.0;
  fastObject = true;

  if(artAsset == manager->getArtAsset(BULLET)) objectType = BULLET;
  else if(artAsset == manager->getArtAsset(REDBULLET)) objectType = REDBULLET;
  else if(artAsset == manager->getArtAsset(SCANBULLET)) {
    objectType = SCANBULLET;
    colliding = false;
  }

  alignment = source->getAlignment();
  material = PROJECTILE;
  health = maxHealth = 0;
  if(objectType == BULLET)
    damageCaused = 5;
  if(objectType == REDBULLET)
    if(source->getObjectType() == BOSS)
      damageCaused = 5;
    else
      damageCaused = 3;
  damageable = false;

  if(objectType != MISSILE) {
    int dist = getDist(positionX, positionY, player->getPositionX(),
      player->getPositionY());

    if(objectType == SCANBULLET) manager->playSound(SCANSHOOT, 0, 1000, 1000);
    else manager->playSound(SHOOT, dist, 500, 1000);
  }
}

Bullet::~Bullet() {}

void Bullet::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  positionX += velocityX + sourceVelocityX;
  positionY += velocityY + sourceVelocityY;

  if(++lifeCounter == lifespan) removed = true;
  
  prepareStateInfo();

  GameObject::update(event, objects);

  if(collided) removed = true;

  if(getVelocity() > MAX_BULLET_VEL) {
    velocityX = initVelX;
    velocityY = initVelY;
  }

  //if(velocityX > MAX_BULLET_VEL /* *cos(absoluteAngle) */) velocityX = MAX_BULLET_VEL /* *cos(absoluteAngle) */;
  //if(velocityX < -MAX_BULLET_VEL /* *cos(absoluteAngle) */) velocityX = -MAX_BULLET_VEL /* *cos(absoluteAngle) */;
  //if(velocityY > MAX_BULLET_VEL /* * sin(absoluteAngle) */) velocityY = MAX_BULLET_VEL /* * sin(absoluteAngle) */;
  //if(velocityY < -MAX_BULLET_VEL /* * sin(absoluteAngle) */) velocityY = -MAX_BULLET_VEL /* * sin(absoluteAngle) */;
}

//void Bullet::draw(SDL_Surface *screen, Radar *radar)
//{
//  float xDiff, yDiff, relR, relTheta;
//  xDiff = player->getPositionX() /*+ player->getSpriteWidth() / 2*/ - positionX;
//  yDiff = player->getPositionY() /*+ player->getSpriteHeight() / 2*/ - positionY;
//  //xDiff = positionX - player->getPositionX();
//  //yDiff = positionY - player->getPositionY();
//  convertRectToPolar(xDiff, yDiff, relR, relTheta);
//
//  relTheta -= player->getAbsoluteAngle() - PI / 2;
//  if(relTheta > 2 * PI)  relTheta -= 2 * PI;
//  if(relTheta < -2 * PI)  relTheta += 2 * PI;
//
//  convertPolarToRect(relR, relTheta, relativeX, relativeY);
//  relativeX += player->getRelativeX() + player->getSpriteWidth() / 2 - artAsset->getWidth() / 2;
//  relativeY += player->getRelativeY() + player->getSpriteHeight() / 2 - artAsset->getHeight() / 2;
//
//  float bt = float(radar->getBorderThickness());
//  float rw = radarAsset->getWidth();
//  float rh = radarAsset->getHeight();
//  float scale = radar->getScale();
//  float playerX = player->getRelativeX();
//  float playerY = player->getRelativeY();
//  //float radarX = radar->scaleX(float((relativeX-playerX)/screen->w)/scale) +
//  //               radar->scaleX(float(playerX/screen->w)) + bt + 0.5*rw;
//  //float radarY = radar->scaleY(float((relativeY-playerY)/screen->h)/scale) +
//  //               (playerY/screen->h) * radar->scaleY(float(playerY/screen->h)) +
//  ////               bt + 0.5*rh;
//  //float radarX = radar->scaleX(float((positionX-player->getPositionX())/screen->w)/scale) +
//  //               radar->scaleX(float(player->getRelativeX()/screen->w)) + bt +
//  //               0.5*(player->getRadarWidth()-radarAsset->getWidth());
//  //float radarY = radar->scaleY(float((positionY-player->getPositionY())/screen->h)/scale) +
//  //               (player->getRelativeY()/screen->h) * radar->scaleY(float(player->getRelativeY()/screen->h)) + bt +
//  //               0.5*(player->getRadarHeight()-radarAsset->getHeight());
//
//  //-- I'M GOING TO TRY SOMETHING HERE --//
//
//  float radarX = radar->scaleX(xDiff/screen->w/scale);
//  float radarY = radar->scaleY(yDiff/screen->h/scale);
//
//  convertRectToPolar(radarX, radarY, relR, relTheta);
//
//  relTheta -= player->getAbsoluteAngle() - PI / 2;
//  if(relTheta > 2 * PI)  relTheta -= 2 * PI;
//  if(relTheta < -2 * PI)  relTheta += 2 * PI;
//
//  convertPolarToRect(relR, relTheta, radarX, radarY);
//  radarX += player->getRadarX() + player->getRadarWidth() / 2 - radarAsset->getWidth() / 2;
//  radarY += player->getRadarY() + player->getRadarHeight() / 2 - radarAsset->getHeight() / 2;
//  
//  //-- END TRIAL --//
//
//  if(radarX < bt - rw)
//    radarX = bt - rw;
//  else if(radarX > radar->getSurface()->w - bt - 1 + 0.5*rw)
//    radarX = radar->getSurface()->w - 1 - bt + 0.5*rw;
//
//  if(radarY < bt - rh)
//    radarY = bt - rh;
//  else if(radarY > radar->getSurface()->h - bt - 1 + 0.5*rh)
//    radarY = radar->getSurface()->h - 1 - bt + 0.5*rh;
//
//  applySurface(relativeX, relativeY, artAsset->getSurface(), screen,
//    artAsset->getSprite(spriteID));
//  if(radar->active())
//    applySurface(radarX, radarY, radarAsset->getSurface(), radar->getSurface(),
//      radarAsset->getSprite(rSpriteID));
//}