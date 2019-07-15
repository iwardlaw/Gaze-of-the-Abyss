/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"Boss.h"
#include"constants.h"
#include"enums.h"
#include"utilities.h"

Boss::Boss(int x, int y, int spread, SpaceShip *pl, ArtAsset *aAsset,
  ArtAsset *rAsset, ResourceManager *rm): NPCDefender(x, y, spread, pl, aAsset,
  rAsset, rm)
{
  objectType = BOSS;
  health = maxHealth = prevHealth = 500;

  missileClock = 1;
  missileDelay = rand() % (MAX_BOSS_MISSILE_DELAY - MIN_BOSS_MISSILE_DELAY) +
    MIN_BOSS_MISSILE_DELAY + 1;

  state = ATTACK;
}

Boss::~Boss() {}

void Boss::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  if(!player->dead()) {
    targetPosX = player->getPositionX();
    targetPosY = player->getPositionY();
    targetVelX = player->getVelocityX();
    targetVelY = player->getVelocityY();
  }
  else {
    state = IDLE;
    targetPosX = baseX;
    targetPosY = baseY;
    targetVelX = targetVelY = 0.0;
  }

  pursueTarget();

  float dist = getDist(positionX, positionY, player->getPositionX(), player->getPositionY());
  if(state == ATTACK && dist <= 1000.0) shoot(objects);

  //++missileClock %= missileDelay;
  ++shootClock %= shootDelay;

  prevHealth = health;
  ExternalObject::update(event, objects);

  if(health < maxHealth / 4) shootDelay = 10;

  if(removed) {
    manager->makeExplosion(this, player, objects);
    if(dist <= 300.0) player->damage(100 * dist / 300.0);
    manager->dropHealth(FULL, this, player, objects);
  }

  thrustX = thrustY = 0.0;

if(getVelocity() > MAX_NPC_VEL) {
    velocityX = initVelX;
    velocityY = initVelY;
  }
}

void Boss::shoot(std::vector<GameObject*> &objects)
{
  if(shootClock == 0)
    manager->makeBullet(REDBULLET, this, player, objects, BULLET_START_LIFE);
}