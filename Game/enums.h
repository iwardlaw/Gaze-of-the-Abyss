/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef ENUMS_H
#define ENUMS_H

enum Alignment {ALLY, NEUTRAL, ENEMY};
enum DifficultyLevel {EASY, MEDIUM, HARD, EXTREME};
enum HealthSize {SMALL, MED, LARGE, FULL};
enum Material {GENERIC, ROCK, METAL, PROJECTILE};
enum MenuItemState {HIGHLIGHTED, NOT_HIGHLIGHTED, PRESSED};
enum NPCState {IDLE, ATTACK};
enum NPCStimulus {SEE_ENEMY, NO_DETECTION, TOO_FAR};
enum PathDirection {LEFT, CENTER, RIGHT};
enum PathThrust {FORWARD, NONE, BACK};

#endif