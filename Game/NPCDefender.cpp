/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"NPCDefender.h"
#include"constants.h"
#include"enums.h"
#include"globals.h"
#include"utilities.h"

#include<iostream>
#include<iomanip>

NPCDefender::NPCDefender(int x, int y, int spread, SpaceShip *_player,
  ArtAsset *_artAsset, ArtAsset *_radarAsset, ResourceManager *rm):
  NPC(x, y, spread, _player, _artAsset, _radarAsset, rm)
{
  sightRadius = 0.7 * manager->getScreen()->h;
  baseRadius = 1500;
  objectType = DEF;
  alignment = ENEMY;
  state = IDLE;

  baseX = positionX;
  baseY = positionY;
  targetPosX = baseX;
  targetPosY = baseY;
  targetVelX = targetVelY = 0.0;

  prevDir = CENTER;
  prevThr = NONE;

  shootClock = 0;
  shootDelay = 15;

  health = maxHealth = prevHealth = 75;
  attackMemClock = DEF_ATTACK_MEMORY;

  initializeMatrix();
}

NPCDefender::~NPCDefender() {}

void NPCDefender::initializeMatrix()
{
  matrix[IDLE][SEE_ENEMY] = ATTACK;
  matrix[IDLE][NO_DETECTION] = IDLE;
  matrix[IDLE][TOO_FAR] = IDLE;

  matrix[ATTACK][SEE_ENEMY] = ATTACK;
  matrix[ATTACK][NO_DETECTION] = IDLE;
  matrix[ATTACK][TOO_FAR] = IDLE;
}

void NPCDefender::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  stimulus = getStimulus();
  state = matrix[state][stimulus];

  if(state == IDLE || player->dead()) {
    targetPosX = baseX;
    targetPosY = baseY;
    targetVelX = targetVelY = 0.0;
  }
  else {
    targetPosX = player->getPositionX();
    targetPosY = player->getPositionY();
    targetVelX = player->getVelocityX();
    targetVelY = player->getVelocityY();
  }

  pursueTarget();

  if(state == ATTACK) shoot(objects);

  ++shootClock %= shootDelay;

  prevHealth = health;
  ExternalObject::update(event, objects);

  if(attackMemClock < DEF_ATTACK_MEMORY) ++attackMemClock;

  if(removed) {
    manager->makeExplosion(this, player, objects);

    int i = rand() % 10;
    if(i > 4) {
      HealthSize size;
      i = rand() % 10;
      if(i < 6) size = SMALL;
      else if(i < 9) size = MED;
      else size = LARGE;

      manager->dropHealth(size, this, player, objects);
    }
  }

  thrustX = thrustY = 0.0;

if(getVelocity() > MAX_NPC_VEL) {
    velocityX = initVelX;
    velocityY = initVelY;
  }
}

void NPCDefender::pursueTarget()
{
  if(positionX != targetPosX || positionY != targetPosY ||
     velocityX != targetVelX || velocityY != targetVelY) {
    PathDirection dir = CENTER;
    PathThrust thr = NONE;

    float predictedX, predictedY;
    float optimalX, optimalY;
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

    //optimalDist = getDist(centerPredX, centerPredY, targetPredX, targetPredY);
    centerDist = getDist(centerPredX, centerPredY, targetPredX, targetPredY);
    optimalDist = centerDist;
    //std::cerr << std::fixed << std::setprecision(2) << "\rCenterDiff = " << optimalAngleDiff;

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
      if(state == IDLE) {
        tempDist = getDist(initPosX, initPosY, baseX, baseY);

        if(tempDist > 3.0) {
          targetVelX = std::sqrt(tempDist) * cos(absoluteAngle) * 0.2;
          targetVelY = std::sqrt(tempDist) * sin(absoluteAngle) * 0.2;
        }
        else
          targetVelX = targetVelY = 0.0;

        thrustX = mass * (targetVelX - initVelX);
        thrustY = mass * (targetVelY - initVelY);

        thr = NONE;
      }
      else { // if(state == ATTACK)
        if(getDist(initPosX, initPosY, targetPredX, targetPredY) > 1000.0) {
          targetVelX = MAX_NPC_VEL * cos(absoluteAngle);
          targetVelY = MAX_NPC_VEL * sin(absoluteAngle);
          thrustX = mass * (targetVelX - initVelX);
          thrustY = mass * (targetVelY - initVelY);
          thr = NONE;
        }
        else {
          optimalX = initVelX;
          optimalY = initVelY;

          // Simulate Forward Thrust
          velocityX = initVelX + DEF_THRUST * cos(absoluteAngle) / mass;
          velocityY = initVelY + DEF_THRUST * sin(absoluteAngle) / mass;

          if(getDist(velocityX, velocityY, targetVelX, targetVelY) <
            getDist(optimalX, optimalY, targetVelX, targetVelY)) {
              thr = FORWARD;
              optimalX = velocityX;
              optimalY = velocityY;
          }

          // Simulate Backward Thrust
          velocityX = initVelX - DEF_THRUST * cos(absoluteAngle) / mass;
          velocityY = initVelY - DEF_THRUST * sin(absoluteAngle) / mass;

          if(getDist(velocityX, velocityY, targetVelX, targetVelY) <
            getDist(optimalX, optimalY, targetVelX, targetVelY)) {
              thr = BACK;
          }

          if(thr == FORWARD) {
            thrustX = DEF_THRUST * cos(absoluteAngle);
            thrustY = DEF_THRUST * sin(absoluteAngle);
          }
          else if(thr == BACK) {
            thrustX = -DEF_THRUST * cos(absoluteAngle);
            thrustY = -DEF_THRUST * sin(absoluteAngle);
          }
        }
      }
    }
    else
      std::cerr << "ERROR! No direction attained!" << std::endl;

    prevDir = dir;
    prevThr = thr;
  }
  positionX = initPosX;
  positionY = initPosY;
  velocityX = initVelY;
  velocityY = initVelY;
}

void NPCDefender::shoot(std::vector<GameObject*> &objects)
{
  if(shootClock == 0)
    manager->makeBullet(REDBULLET, this, player, objects, BULLET_START_LIFE);
}

NPCStimulus NPCDefender::getStimulus()
{
  if(!player->dead()) {
    if(getDist(positionX, positionY, baseX, baseY) > baseRadius)
      return TOO_FAR;

    //float playerX = player->getPositionX();
    //float playerY = player->getPositionY();
    float plDist = getDist(positionX, positionY, player->getPositionX(),
      player->getPositionY());

    //if(getDist(positionX, positionY, playerX, playerY) <= sightRadius)
    if(plDist <= sightRadius || health < prevHealth) {
      attackMemClock = 0;
      return SEE_ENEMY;
    }
    
    if(attackMemClock < DEF_ATTACK_MEMORY && plDist <= 2.0 * sightRadius)
      return SEE_ENEMY;
  }

  return NO_DETECTION;
}

void NPCDefender::draw(SDL_Surface *screen, Radar *radar)
{
  ExternalObject::draw(screen, radar);
  if(defenderRadiiVisible)
    drawBase(screen);
}

void NPCDefender::drawBase(SDL_Surface *screen)
{
  float x, y, relR, relTheta, xDiff, yDiff;
  SDL_Rect offset;
  Uint32 color = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xAA);
  float baseRelX, baseRelY;

  offset.w = offset.h = 1;

  xDiff = player->getPositionX() - baseX;
  yDiff = player->getPositionY() - baseY;
  convertRectToPolar(xDiff, yDiff, relR, relTheta);

  relTheta -= player->getAbsoluteAngle() - PI / 2;
  if(relTheta > 2 * PI)  relTheta -= 2 * PI;
  if(relTheta < -2 * PI)  relTheta += 2 * PI;

  convertPolarToRect(relR, relTheta, baseRelX, baseRelY);
  baseRelX += player->getRelativeX() + player->getSpriteWidth() / 2;
  baseRelY += player->getRelativeY() + player->getSpriteHeight() / 2;

  offset.x = baseRelX;
  offset.y = baseRelY;

  SDL_FillRect(screen, &offset, color);

  for(relTheta=0.0; relTheta<2*PI; relTheta+=PI/32) {
    convertPolarToRect(baseRadius, relTheta, x, y);
    x += baseRelX;
    y += baseRelY;

    offset.x = x;
    offset.y = y;

    SDL_FillRect(screen, &offset, color);
  }

  color = SDL_MapRGB(screen->format, 0xFF, 0xAA, 0xAA);

  for(relTheta=0.0; relTheta<2*PI; relTheta+=PI/32) {
    convertPolarToRect(sightRadius, relTheta, x, y);
    x += relativeX + artAsset->getWidth() / 2;
    y += relativeY + artAsset->getHeight() / 2;

    offset.x = x;
    offset.y = y;

    SDL_FillRect(screen, &offset, color);
  }
}

NPCState NPCDefender::getState() {return state;}