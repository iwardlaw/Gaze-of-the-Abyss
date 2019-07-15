/*
   Isaac Wardlaw
   05 Feb 2014
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"LivesIndicator.h"
#include"constants.h"

LivesIndicator::LivesIndicator(SDL_Surface *_surface, std::map<std::string,
  std::string> &attributes, int screenWidth, int screenHeight)
{
  surface = _surface;
  width = atoi(attributes[WIDTH].c_str());
  height = atoi(attributes[HEIGHT].c_str());
  borderThickness = atoi(attributes[BDRTHICKNESS].c_str());

  rFill = atoi(attributes[RFILLKEY].c_str());
  gFill = atoi(attributes[GFILLKEY].c_str());
  bFill = atoi(attributes[BFILLKEY].c_str());
  borderR = atoi(attributes[BDRR].c_str());
  borderG = atoi(attributes[BDRG].c_str());
  borderB = atoi(attributes[BDRB].c_str());

  offset.x = atoi(attributes[OFFSETX].c_str());
  if(offset.x < 0) offset.x += screenWidth - width + 1;
  offset.y = atoi(attributes[OFFSETY].c_str());
  if(offset.y < 0) offset.y += screenHeight - height + 1;

  font = TTF_OpenFont(attributes[FONTPATH].c_str(),
    atoi(attributes[FONTSIZE].c_str()));
  textColor.r = atoi(attributes[FONTR].c_str());
  textColor.g = atoi(attributes[FONTG].c_str());
  textColor.b = atoi(attributes[FONTB].c_str());

  surfaceClipRect.x = surfaceClipRect.y = borderThickness;
  surfaceClipRect.w = width - 2 * borderThickness;
  surfaceClipRect.h = height - 2 * borderThickness;

  onscreen = true;

  SDL_FillRect(surface, &surface->clip_rect,
    SDL_MapRGB(surface->format, borderR, borderG, borderB));
}

LivesIndicator::~LivesIndicator()
{
  SDL_FreeSurface(surface);
  SDL_FreeSurface(iconSheet);
  surface = iconSheet = NULL;
  iconSprites = NULL;
  TTF_CloseFont(font);
  font = NULL;
}

SDL_Surface* LivesIndicator::getSurface() {return surface;}

SDL_Rect LivesIndicator::getOffset() {return offset;}

SDL_Rect LivesIndicator::getSurfaceClipRect() {return surfaceClipRect;}

int LivesIndicator::getBorderThickness() {return borderThickness;}

void LivesIndicator::toggle() {onscreen = !onscreen;}

bool LivesIndicator::active() {return onscreen;}