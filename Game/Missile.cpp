/*
   Isaac Wardlaw
   Beyond Project
   25 Aug 2014
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"Missile.h"
#include"constants.h"
#include"utilities.h"
#include<iostream>

Missile::Missile(GameObject *src, GameObject *tgt, SpaceShip *pl, ArtAsset *aAsset,
  ArtAsset *rAsset, int _lifespan, ResourceManager *rm) : Bullet(src, pl, aAsset, rAsset,
  _lifespan, rm)
{
  spriteID = 0;
  objectType = MISSILE;
  health = maxHealth = 5;
  fastObject = false;
  material = METAL;
  damageCaused = 20;
  damageable = true;
  target = tgt;

  positionX += 1.25 * source->getVelocityX();
  positionY += 1.25 * source->getVelocityY();
  velocityX = MISSILE_VEL * cos(absoluteAngle);
  velocityY = MISSILE_VEL * sin(absoluteAngle);

  thrustDuration = MISSILE_THRUST_DURATION;
  thrustCounter = 1;
  coastDuration = MISSILE_COAST_DURATION;
  coastCounter = coastDuration + 1;

  int dist = getDist(positionX, positionY, player->getPositionX(),
    player->getPositionY());

  manager->playSound(FIRE_MISSILE, dist, 500, 1000);
}

Missile::~Missile() {}

void Missile::update(SDL_Event event, std::vector<GameObject*> &objects)
{

  if(++lifeCounter == lifespan) removed = true;

  if(target != NULL) {
    targetPosX = target->getPositionX();
    targetPosY = target->getPositionY();
    targetVelX = target->getVelocityX();
    targetVelY = target->getVelocityY();

    pursueTarget();
  }
  else {
    //thrustX = mass * initVelX;
    //thrustY = mass * initVelY;

    if(coastCounter == 1)
      thrustX = thrustY = 0.0;
    if(coastCounter < coastDuration)
      ++coastCounter;
    else if(coastCounter == coastDuration) {
      ++coastCounter;
      thrustCounter = 1;
    }
    else if(thrustCounter < thrustDuration) {
      ++thrustCounter;
      thrustX = MISSILE_THRUST * cos(absoluteAngle);
      thrustY = MISSILE_THRUST * sin(absoluteAngle);
    }
    else if(thrustCounter == thrustDuration) {
      ++thrustCounter;
      coastCounter = 1;
    }
  }

  prepareStateInfo();

  ExternalObject::update(event, objects);

  if(collided) removed = true;

  thrustX = thrustY = 0.0;

  if(removed) manager->makeExplosion(this, player, objects);

  if(getVelocity() > MAX_MISSILE_VEL) {
    velocityX = initVelX;
    velocityY = initVelY;
  }
}

void Missile::pursueTarget()
{
  PathDirection dir = CENTER;
  float predictedX, predictedY, optimalX, optimalY;
  float optimalDist, tempDist, centerDist, leftDist, rightDist;
  float centerPredX, centerPredY, leftPredX, leftPredY, rightPredX, rightPredY;
  float tempAngle;

  float targetPredX = targetPosX + targetVelX;
  float targetPredY = targetPosY + targetVelY;

  if(velocityX == 0.0 && velocityY == 0.0) {
    velocityX = cos(absoluteAngle);
    velocityY = sin(absoluteAngle);
  }

  centerPredX = initPosX + velocityX;
  centerPredY = initPosY + velocityY;

  float posXDiff = centerPredX - initPosX;
  float posYDiff = centerPredY - initPosY;
  float objXDiff = targetPredX - initPosX;
  float objYDiff = targetPredY - initPosY;

  float initVel = velocityX / cos(absoluteAngle);
  float relR, relTheta;

  convertRectToPolar(objXDiff, objYDiff, relR, relTheta);
  if(relTheta > 2 * PI) relTheta -= 2 * PI;
  if(relTheta < 0.0) relTheta += 2 * PI;

  float optimalAngleDiff = abs(relTheta - absoluteAngle);
  if(optimalAngleDiff >= 2 * PI) optimalAngleDiff -= 2 * PI;
  if(optimalAngleDiff < 0.0) optimalAngleDiff += 2 * PI;

  float optimalDotProduct = posXDiff * objXDiff + posYDiff * objYDiff;
  float tempDotProduct;

  centerDist = getDist(centerPredX, centerPredY, targetPredX, targetPredY);
  optimalDist = centerDist;

  // Simulate Left Pivot
  tempAngle = absoluteAngle - ((2 * PI) / artAsset->getNumSprites());

  velocityX = initVel * cos(tempAngle);
  velocityY = initVel * sin(tempAngle);

  leftPredX = initPosX + velocityX;
  leftPredY = initPosY + velocityY;

  posXDiff = leftPredX - initPosX;
  posYDiff = leftPredY - initPosY;
  tempDotProduct = posXDiff * objXDiff + posYDiff * objYDiff;

  tempDist = getDist(leftPredX, leftPredY, targetPredX, targetPredY);
  leftDist = getDist(leftPredX, leftPredY, targetPredX, targetPredY);

  tempAngle = abs(relTheta - tempAngle);
  if(tempAngle >= 2 * PI) tempAngle -= 2 * PI;
  if(tempAngle < 0.0) tempAngle += 2 * PI;

  //std::cerr << std::fixed << std::setprecision(2) << "  LeftDiff = " << tempAngle;

  if(tempAngle <= optimalAngleDiff) {
    dir = LEFT;
    optimalDist = tempDist;
    optimalAngleDiff = tempAngle;
  }

  // Simulate Right Pivot
  tempAngle = absoluteAngle + ((2 * PI) / artAsset->getNumSprites());

  velocityX = initVel * cos(tempAngle);
  velocityY = initVel * sin(tempAngle);

  rightPredX = initPosX + velocityX;
  rightPredY = initPosY + velocityY;

  posXDiff = rightPredX - initPosX;
  posYDiff = rightPredY - initPosY;
  tempDotProduct = posXDiff * objXDiff + posYDiff * objYDiff;

  tempDist = getDist(rightPredX, rightPredY, targetPredX, targetPredY);
  rightDist = getDist(rightPredX, rightPredY, targetPredX, targetPredY);

  tempAngle = abs(relTheta - tempAngle);
  if(tempAngle >= 2 * PI) tempAngle -= 2 * PI;
  if(tempAngle < 0.0) tempAngle += 2 * PI;

  //std::cerr << std::fixed << std::setprecision(2) << "  RightDiff = " << tempAngle;
  //std::cerr << std::fixed << std::setprecision(2) << "  Opt = " << optimalAngleDiff;

  if(tempAngle < optimalAngleDiff) {
    dir = RIGHT;
    optimalDist = tempDist;
  }

  if(dir == LEFT)
    turnLeft();
  else if(dir == RIGHT)
    turnRight();
  else if(dir == CENTER) {
    thrustX = mass * initVelX;
    thrustY = mass * initVelY;
  }

  positionX = initPosX;
  positionY = initPosY;
  velocityX = initVelY;
  velocityY = initVelY;
}