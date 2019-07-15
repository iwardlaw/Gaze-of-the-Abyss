/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include"enums.h"
#include"GameObject.h"
#include"SDL.h"
#include"SDL_mixer.h"
#include<fstream>
#include<string>

SDL_Surface* loadImage(std::string fileName, int rMapKey, int gMapKey,
  int bMapKey);
void applySurface(int x, int y, SDL_Surface *src, SDL_Surface *dst,
  SDL_Rect *clip = NULL);
void readln(std::istream& in, std::string& s);
void convertRectToPolar(float x, float y, float &r, float &theta);
void convertPolarToRect(float r, float theta, float &x, float &y);
float getDist(float posX1, float posY1, float posX2, float posY2);
int round(float);
int median(int, int, int);
std::string difficultyToString(DifficultyLevel);

#endif