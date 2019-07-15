/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Portions by Keith Bush, PhD
   26 Jan 2012
   ========================
   File Description:
   GameObject.cpp -- Implementation file for 'GameObject', which is an abstract
   class used to provide the central members and methods used by its children.
   Using this parent class allows the game engine to construct a vector of
   'GameObject' pointers and assign those pointers to instances of descendent
   classes.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   'string' and 'int' passed into loadImage(). 2 'int's, 2 'SDL_Surface'
   pointers, and an 'SDL_Rect' pointer passed into applySurface(). Four 'float'
   references each to convertRectToPolar() and convertPolarToRect(). Two
   'SDL_Surface' pointers, an 'SDL_Rect' pointer, and an 'int' passed to the
   constructor. 'SDL_Event' passed to update(). 'SDL_Surface' pointer and
   'Radar' pointer passed to draw(). 'float's for setPositionX() and
   setPositionY(). 'int' passed to setSpriteID().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   'SDL_Surface' pointer returned from loadImage(). 'float's and 'int's
   returned as appropriate from the getter methods. Effectively outputs changes
   to third and fourth agruments in convertRectToPolar() and
   convertPolarToRect(), though this ability is not used.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#include"ArtAsset.h"
#include"constants.h"
#include"GameObject.h"
#include"globals.h"
#include"ResourceManager.h"
#include"utilities.h"
#include"SDL.h"
#include"SDL_image.h"
#include"SDL_mixer.h"
#include<cmath>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>

class SpaceShip;

GameObject::GameObject(ArtAsset *_artAsset, ArtAsset *_radarAsset, ResourceManager *rm)
{
  manager = rm;

  positionX = positionY = 0.0;
  absoluteAngle = 0.5 * PI;
  relativeX = relativeY = 0.0;
  velocityX = velocityY = 0.0;
  thrustX = thrustY = 0.0;
  mass = 1.0;
  spriteID = rSpriteID = 0;
  artAsset = _artAsset;
  radarAsset = _radarAsset;

  boundingRadius = float(std::max(artAsset->getWidth(), artAsset->getHeight())) / 2;
  newPosX = newPosY = 0.0;
  newVelX = newVelY = 10.0;

  objectType = "";
  alignment = NEUTRAL;
  material = GENERIC;
  removed = false;
  fastObject = false;
  colliding = true;
}

//Destructor
GameObject::~GameObject()
{
  sheet = NULL;
  sprites = NULL;
}

void GameObject::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  if(!removed) {
    float deltaT = 1.0;
    findNewPosition(deltaT, initPosX, initPosY, initVelX, initVelY, objects);
    if(!collided) checkCollisions(deltaT, objects);

    velocityX = newVelX;
    velocityY = newVelY;
    positionX = newPosX;
    positionY = newPosY;
  }

  if(health < 0) removed = true;

  //if(positionX > 2000) positionX = -2000;
  //if(positionX < -2000) positionX = 2000;
  //if(positionY > 2000) positionY = -2000;
  //if(positionY < -2000) positionY = 2000;
}

void GameObject::prepareStateInfo()
{
  initPosX = positionX;
  initPosY = positionY;
  initVelX = velocityX;
  initVelY = velocityY;

  if(newPosX == 0 && newPosY == 0) {
    newPosX = initPosX;
    newPosY = initPosY;
  }

  collided = false;
}

void GameObject::storeStateInfo()
{
  prevPosX = positionX;
  prevPosY = positionY;
  prevVelX = velocityX;
  prevVelY = velocityY;
}

void GameObject::remove() {removed = true;}

bool GameObject::dead() {return removed;}

bool GameObject::fast() {return fastObject;}

bool GameObject::collides() {return colliding;}

void GameObject::heal(int hp)
{
  health += hp;
  if(health > maxHealth) health = maxHealth;
}

void GameObject::damage(int dmg) {if(damageable) health -= dmg;}

//Getter Methods
float GameObject::getPositionX() {return positionX;}

float GameObject::getPositionY() {return positionY;}

float GameObject::getAbsoluteAngle() {return absoluteAngle;}

float GameObject::getRelativeX() {return relativeX;}

float GameObject::getRelativeY() {return relativeY;}

float GameObject::getVelocityX() {return velocityX;}

float GameObject::getVelocityY() {return velocityY;}

float GameObject::getVelocity()
{
  return std::sqrt(pow(velocityX, 2) + pow(velocityY, 2));
}

float GameObject::getMass() {return mass;}

int GameObject::getSpriteID() {return spriteID;}

float GameObject::getInitPosX() {return initPosX;}

float GameObject::getInitPosY() {return initPosY;}

float GameObject::getNewPosX() {return newPosX;}

float GameObject::getNewPosY() {return newPosY;}

float GameObject::getInitVelX() {return initVelX;}

float GameObject::getInitVelY() {return initVelY;}

float GameObject::getNewVelX() {return newVelX;}

float GameObject::getNewVelY() {return newVelY;}

float GameObject::getBoundingRadius() {return boundingRadius;}

int GameObject::getSpriteHeight() {return artAsset->getHeight();}

int GameObject::getSpriteWidth() {return artAsset->getWidth();}

int GameObject::getNumSprites() {return artAsset->getNumSprites();}

int GameObject::getRadarWidth() {return radarAsset->getWidth();}

int GameObject::getRadarHeight() {return radarAsset->getHeight();}

int GameObject::getHealth() {return health;}

int GameObject::getMaxHealth() {return maxHealth;}

int GameObject::getDamageCaused() {return damageCaused;}

Alignment GameObject::getAlignment() {return alignment;}

std::string GameObject::getObjectType() {return objectType;}

Material GameObject::getMaterial() {return material;}

//Setter Methods
void GameObject::setPositionX(float positionX) {this->positionX = positionX;}

void GameObject::setPositionY(float positionY) {this->positionY = positionY;}

void GameObject::setVelocityX(float v) {velocityX = v;}

void GameObject::setVelocityY(float v) {velocityY = v;}

void GameObject::setSpriteID(int spriteID) {this->spriteID = spriteID;}

void GameObject::setNewVelX(float v) {newVelX = v;}

void GameObject::setNewVelY(float v) {newVelY = v;}

void GameObject::findNewPosition(float deltaT, float posX, float posY, float velX, float velY, std::vector<GameObject*> &objects)
{
  float forceOfGrav;
  float forceX = 0.0, forceY = 0.0;
  float accelX, accelY;
  float objX, objY;
  float relR, relTheta;

  if(gravityOn && colliding) {
    std::vector<GameObject*>::iterator objIter;
    for(objIter=objects.begin(); objIter!=objects.end(); ++objIter)
      if(*objIter != this && (*objIter)->colliding) {
        forceOfGrav = getGrav(*objIter);
        objX = (*objIter)->initPosX - posX;
        objY = (*objIter)->initPosY - posY;
        convertRectToPolar(objX, objY, relR, relTheta);
        forceX += forceOfGrav * cos(relTheta);
        forceY += forceOfGrav * sin(relTheta);
      }
  }

  forceX += thrustX;
  forceY += thrustY;

  accelX = forceX / mass;
  accelY = forceY / mass;

  newVelX = deltaT * accelX + velX;
  newVelY = deltaT * accelY + velY;

  newPosX = deltaT * newVelX + posX;
  newPosY = deltaT * newVelY + posY;
}

float GameObject::getGrav(GameObject *obj)
{
  float distanceSquared = std::pow(initPosX - obj->initPosX, 2) +
    std::pow(initPosY - obj->initPosY, 2);

  if(distanceSquared < 25.0) distanceSquared = 25.0;
  return (G * mass * obj->getMass()) / distanceSquared;
}

void GameObject::checkCollisions(float deltaT, std::vector<GameObject*> &objects)
{
  std::vector<GameObject*>::iterator objIter;
  const float collisionRange = boundingRadius / 8;
  float t = deltaT, initDeltaT = deltaT;
  float diff;
  float lambdaX, lambdaY;
  float damageMultiplier;
  float velDiffX, velDiffY;
  float dist, sumOfRadii;

  for(objIter=objects.begin(); objIter!=objects.end(); ++objIter) {
    dist = getDist(newPosX, newPosY, (*objIter)->newPosX, (*objIter)->newPosY);
    if(*objIter != this && dist < 200.0 && !(*objIter)->fast()) {
      sumOfRadii = (boundingRadius + (*objIter)->boundingRadius);
      diff = dist - sumOfRadii;
      if(diff <= 0.0) {
        if(colliding && (*objIter)->colliding && collisionOn) {
          velDiffX = abs(newVelX - (*objIter)->newVelX);
          velDiffY = abs(newVelY - (*objIter)->newVelY);
          if(velDiffX == 0.0 || velDiffY == 0.0) {
            deltaT /= 2.0;
            t = deltaT;
            findNewPosition(t, prevPosX, prevPosY, prevVelX, prevVelY, objects);
            (*objIter)->findNewPosition(t, (*objIter)->prevPosX, (*objIter)->prevPosY, (*objIter)->prevVelX, (*objIter)->prevVelY, objects);
            dist = getDist(newPosX, newPosY, (*objIter)->newPosX, (*objIter)->newPosY);
            diff = dist - sumOfRadii;
            while(abs(diff) > collisionRange) {
              if(diff > 0.0) {
                deltaT /= 2;
                t += deltaT;
              }
              else if(diff < 0.0) {
                deltaT /= 2;
                t -= deltaT;
              }
              findNewPosition(t, prevPosX, prevPosY, prevVelX, prevVelY, objects);
              (*objIter)->findNewPosition(t, (*objIter)->prevPosX, (*objIter)->prevPosY, (*objIter)->prevVelX, (*objIter)->prevVelY, objects);
              dist = getDist(newPosX, newPosY, (*objIter)->newPosX, (*objIter)->newPosY);
              diff = dist - sumOfRadii;
            }
          }

          getLambda(*objIter, lambdaX, lambdaY, damageMultiplier);

          //if(velDiffX == 0.0 && velDiffY == 0.0)
          //  lambdaX = lambdaY = -5000.0;

          newVelX += lambdaX / mass;
          newVelY += lambdaY / mass;
          (*objIter)->newVelX -= lambdaX / mass;
          (*objIter)->newVelY -= lambdaY / mass;

          findNewPosition(initDeltaT - t, newPosX, newPosY, newVelX, newVelY, objects);
          (*objIter)->findNewPosition(initDeltaT - t, (*objIter)->newPosX,
            (*objIter)->newPosY, (*objIter)->newVelX, (*objIter)->newVelY, objects);

          (*objIter)->positionX = (*objIter)->newPosX;
          (*objIter)->positionY = (*objIter)->newPosY;
          (*objIter)->velocityX = (*objIter)->newVelX;
          (*objIter)->velocityY = (*objIter)->newVelY;

          (*objIter)->prepareStateInfo();
          (*objIter)->storeStateInfo();

          collided = true;
          (*objIter)->collided = true;

          if(damageOn && (friendlyFireOn || alignment != (*objIter)->alignment)) {
            damage((*objIter)->damageCaused * damageMultiplier);
            (*objIter)->damage(damageCaused * damageMultiplier);
          }

          //if(this != objects[0])
          dist = getDist(positionX, positionY, objects[0]->positionX,
            objects[0]->positionY);
          //else dist = 0;

          manager->playSound(collisionSound(*objIter), dist, 300, 200);
        }
        if(objectType == SCANBULLET) {
          if(manager->addToInfoLog((*objIter)->objectType))
            manager->playSound(SCAN, dist, 1000, 1000);
          collided = true;
        }
      }
    }
  }
}

void GameObject::getLambda(GameObject *obj, float &lambdaX, float &lambdaY, float &damageMultiplier)
{
  float objX = obj->newPosX - newPosX;
  float objY = obj->newPosY - newPosY;
  float relR, relTheta;
  float tempVelX, tempVelY;

  convertRectToPolar(objX, objY, relR, relTheta);

  float normalX = cos(relTheta);
  float normalY = sin(relTheta);

  float restitution = mass * obj->mass * (1 +  EPSILON);

  tempVelX = restitution * (newVelX - obj->newVelX);
  tempVelY = restitution * (newVelY - obj->newVelY);

  lambdaX = -((tempVelX * normalX + tempVelY * normalY) / (mass + obj->mass)) * normalX;
  lambdaY = -((tempVelX * normalX + tempVelY * normalY) / (mass + obj->mass)) * normalY;

  convertRectToPolar(lambdaX, lambdaY, damageMultiplier, relTheta);
  damageMultiplier /= DAMAGE_DIVIDEND;
}

void GameObject::adjustPosition()
{
  positionX += artAsset->getWidth() / 2;
  positionY += artAsset->getHeight() / 2;
}

std::string GameObject::collisionSound(GameObject *obj)
{
  if(material == PROJECTILE || obj->material == PROJECTILE)
    return COL_PROJECTILE;

  if(material == METAL) {
    if(obj->material == METAL) return COL_METAL_METAL;
    if(obj->material == ROCK) return COL_METAL_ROCK;
  }

  if(material == ROCK) {
    if(obj->material == METAL) return COL_METAL_ROCK;
    if(obj->material == ROCK) return COL_ROCK_ROCK;
  }

  return COL_ROCK_ROCK;
}