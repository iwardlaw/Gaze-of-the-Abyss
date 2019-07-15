/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"NPCAttacker.h"
#include"constants.h"
#include"utilities.h"

NPCAttacker::NPCAttacker(int x, int y, int spread, SpaceShip *pl, ArtAsset *aAsset,
  ArtAsset *rAsset, ResourceManager *rm): NPCDefender(x, y, spread, pl, aAsset,
  rAsset, rm)
{
  sightRadius = 0.6 * manager->getScreen()->h;
  objectType = ATK;
  shootDelay = 10;
  health = maxHealth = prevHealth = 40;
}

NPCAttacker::~NPCAttacker() {}

void NPCAttacker::update(SDL_Event event, std::vector<GameObject*> &objects)
{
  if(state == IDLE || player->dead()) {
    stimulus = getStimulus();
    state = matrix[state][stimulus];
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

  float dist = getDist(positionX, positionY, player->getPositionX(), player->getPositionY());
  if(state == ATTACK && dist <= 1000.0) shoot(objects);

  ++shootClock %= shootDelay;

  prevHealth = health;
  ExternalObject::update(event, objects);

  if(removed) {
    manager->makeExplosion(this, player, objects);

    int i = rand() % 10;
    if(i > 7) {
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