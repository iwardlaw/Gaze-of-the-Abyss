/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   NPC.cpp -- Implementation file for the 'NPC' class, which represents
   nonplayer ships. Child of 'ExternalObject'.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Four 'int's, two 'SDL_Surface' pointers, and an 'SDL_Rect' pointer passed to
   the constructor; 'SDL_Event' passed to update().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#include"NPC.h"
#include"constants.h"
#include"globals.h"
#include"SpaceShip.h"
#include"SDL_mixer.h"
#include<cmath>
#include<string>

#include<iostream>

NPC::NPC(int x, int y, int spread, SpaceShip* _player, ArtAsset *_artAsset,
       ArtAsset *_radarAsset, ResourceManager *rm):
       ExternalObject(x, y, spread, _player, _artAsset, _radarAsset, rm)
{
  thrust = float(rand() % 100) * ((MAX_NPC_THRUST - MIN_NPC_THRUST)/100) + MIN_NPC_THRUST;
  thrustDuration = rand() % (MAX_NPC_THRUST_DURATION - MIN_NPC_THRUST_DURATION) + MIN_NPC_THRUST_DURATION;
  coastDuration = rand() % (MAX_NPC_COAST_DURATION - MIN_NPC_COAST_DURATION) + MIN_NPC_COAST_DURATION;
  thrustCounter = 1;
  coastCounter = coastDuration + 1;

  objectType = _NPC;
  material = METAL;
  health = maxHealth = 100;
  damageCaused = 10;
  damageable = true;
}

NPC::~NPC() {}

void NPC::update(SDL_Event event, std::vector<GameObject*> &objects)
{
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
    thrustX = thrust * cos(absoluteAngle);
    thrustY = thrust * sin(absoluteAngle);
  }
  else if(thrustCounter == thrustDuration) {
    ++thrustCounter;
    coastCounter = 1;
  }

  ExternalObject::update(event, objects);

  if(removed) manager->makeExplosion(this, player, objects);

  if(getVelocity() > MAX_NPC_VEL) {
    velocityX = initVelX;
    velocityY = initVelY;
  }
}