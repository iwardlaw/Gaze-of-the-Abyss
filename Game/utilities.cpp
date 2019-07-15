/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"utilities.h"
#include"constants.h"
#include"SDL.h"
#include"SDL_image.h"
#include<cmath>
#include<fstream>
#include<string>
#include<utility>

SDL_Surface* loadImage(std::string fileName, int rMapKey, int gMapKey, int bMapKey)
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load( fileName.c_str() );

	//If the image loaded
	if( loadedImage != NULL )
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );

		//Free the old image
		SDL_FreeSurface( loadedImage );


		//If the image was optimized just fine
		if( optimizedImage != NULL )
		{
			//Map the color key
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, rMapKey, gMapKey, bMapKey);

			//Set all pixels of color "color" to be transparent
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
	}

	//Return the optimized image
	return optimizedImage;
}

void applySurface(int x, int y, SDL_Surface *src, SDL_Surface *dst, SDL_Rect *clip)
{	
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit
	SDL_BlitSurface(src, clip, dst, &offset);
}

void readln(std::istream &in, std::string &s)
{
  //if(!in.eof()) {
  if(in) {
    in >> s;
    while(s.find(COMMENT_CHAR) != std::string::npos) {
      s.erase(s.find(COMMENT_CHAR), std::string::npos);
      while(in.get() != '\n')
        //if(in.eof()) break;
        if(!in) break;
      //if(!in.eof()) in >> s;
      if(in) in >> s;
    }
  }
}

void convertRectToPolar(float x, float y, float &r, float &theta)
{
  r=sqrt(x*x+y*y);

  theta = atan2(y, x);
  //if((x>=0 && y>=0)||(x>=0&&y<=0))
  //  theta=atan(y/x);

  //if(x<0 && y>0)
  //  theta=PI-atan(y/(-x));

  //if(x<0 && y<0)
  //  theta=atan((-y)/(-x))-PI;
}

void convertPolarToRect(float r, float theta, float &x, float &y)
{
  x = r * cos(theta);
  y = r * sin(theta);
}

float getDist(float posX1, float posY1, float posX2, float posY2)
{
  return std::sqrt(std::pow(posX1-posX2, 2) + std::pow(posY1-posY2, 2));
}

int round(float f)
{
  float decimal = f - (int)f;

  if(decimal < 0.5)
    return (int)f;
  
  if(f > 0.0)
    return int(f + 1);

  return int(f - 1);
}

int median(int x, int y, int z)
{
  //return std::max(x, std::min(y, z));

  int a[] = {x, y, z};

  for(int i=2; i>0; --i)
    for(int j=0; j<i; ++j)
      if(a[j] > a[j+1])
        std::swap(a[j], a[j+1]);

  return a[1];
}

std::string difficultyToString(DifficultyLevel diff)
{
  switch(diff) {
    case EASY: return EASY_MSG; break;
    case MEDIUM: return MEDIUM_MSG; break;
    case HARD: return HARD_MSG; break;
    case EXTREME: return EXTREME_MSG; break;
    default: return "";
  }
}