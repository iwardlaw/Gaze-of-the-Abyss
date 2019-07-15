/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef ARTASSET_H
#define ARTASSET_H

#include"SDL.h"
#include<map>
#include<string>

class ArtAsset {
  private:
    int width, height;

    //Art asset properties
    int nrows, ncols;
    int rKey,gKey,bKey;

    //Art Assets
    SDL_Surface *sheet;   //source of object's art
    int numSprites;
    SDL_Rect *sprites;
  public:
    ArtAsset(std::map<std::string, std::string>);
    ~ArtAsset();
    int getWidth();
    int getHeight();
    int getNumSprites();
    SDL_Surface* getSurface();
    SDL_Rect* getSprite(int);
};

#endif