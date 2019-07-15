/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"ArtAsset.h"
#include"constants.h"
#include"utilities.h"
#include"SDL.h"
#include<map>
#include<string>

ArtAsset::ArtAsset(std::map<std::string, std::string> attributes)
{
  rKey = atoi(attributes[RMAPKEY].c_str());
  gKey = atoi(attributes[GMAPKEY].c_str());
  bKey = atoi(attributes[BMAPKEY].c_str());

  sheet = loadImage(attributes[IMAGEPATH], rKey, gKey, bKey);

  nrows = atoi(attributes[NROWS].c_str());
  ncols = atoi(attributes[NCOLS].c_str());
  numSprites = atoi(attributes[NUMSPRITES].c_str());
  width = atoi(attributes[WIDTH].c_str());
  height = atoi(attributes[HEIGHT].c_str());

  sprites = new SDL_Rect[numSprites];

  int row, col;
  for(int i=0; i<numSprites; i++){
		row = i/ncols;
		col = i%ncols;
		sprites[i].x = col * width;
		sprites[i].y = row * height;
		sprites[i].w = width;
		sprites[i].h = height;
	}
}

ArtAsset::~ArtAsset() {
  SDL_FreeSurface(sheet);
  delete [] sprites;
}

int ArtAsset::getWidth() {return width;}

int ArtAsset::getHeight() {return height;}

int ArtAsset::getNumSprites() {return numSprites;}

SDL_Surface* ArtAsset::getSurface() {return sheet;}

SDL_Rect* ArtAsset::getSprite(int id) {return &sprites[id];}