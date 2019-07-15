/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"globals.h"

bool collisionOn;
bool damageOn;
bool defenderRadiiVisible;
bool friendlyFireOn;
bool gravityOn;
bool inertiaOn;
bool rapidFireOn;
bool rk4On;

DifficultyLevel difficulty;

std::map<SDLKey, bool> keys;