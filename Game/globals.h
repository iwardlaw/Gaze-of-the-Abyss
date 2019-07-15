/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include"enums.h"
#include"Explosion.h"
#include<map>
#include"SDL.h"

extern bool collisionOn;
extern bool damageOn;
extern bool defenderRadiiVisible;
extern bool friendlyFireOn;
extern bool gravityOn;
extern bool inertiaOn;
extern bool rapidFireOn;
extern bool rk4On;

extern DifficultyLevel difficulty;

extern std::map<SDLKey, bool> keys;

extern SDLKey key_up;
extern SDLKey key_down;
extern SDLKey key_left;
extern SDLKey key_right;
extern SDLKey key_shoot;
extern SDLKey key_scan;
extern SDLKey key_grab;
extern SDLKey key_pause;
extern SDLKey key_changeLevel;
extern SDLKey key_brake;
extern SDLKey key_quit;
extern SDLKey key_toggleRadar;
extern SDLKey key_toggleHealthbar;
extern SDLKey key_toggleTelemetry;
extern SDLKey key_toggleRapidFire;
extern SDLKey key_toggleCollision;
extern SDLKey key_toggleDamage;
extern SDLKey key_toggleDefenderRadii;
extern SDLKey key_toggleFriendlyFire;
extern SDLKey key_toggleGravity;
extern SDLKey key_toggleIntertia;
extern SDLKey key_toggleRk4;
extern SDLKey key_destroyEnemies;
extern SDLKey key_clearMap;
extern SDLKey key_collectItems;
extern SDLKey key_selfDestruct;

#endif