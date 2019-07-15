/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   Radar.cpp -- Implementation file for the 'Radar' class, which maintains the
   game's radar surface.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   'SDL_Surface' pointer, a 'map' from a 'string' to a 'string', and two 'int's
   passed to constructor; 'float's for scaleX() and scaleY().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   'SDL_Surface' pointer returned from getSurface(), 'SDL_Rect' pointers from
   getOffset() and getSurfaceClipRect(), 'float's from getScale(), scaleX(),
   and scaleY(), int from getBorderThickness(), and 'bool' from active().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   It occurs to me that this may be better placed within a 'GUIObject'
   superclass; however, assuming that proper functionality is what is most
   important at the moment, I have left it standalone.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#include"Radar.h"
#include"constants.h"
#include<map>
#include<string>

Radar::Radar(SDL_Surface *_surface, std::map<std::string,
  std::string> &attributes, int screenWidth, int screenHeight)
{
  surface = _surface;
  width = atoi(attributes[WIDTH].c_str());
  height = atoi(attributes[HEIGHT].c_str());
  borderThickness = atoi(attributes[BDRTHICKNESS].c_str());

  scale = atof(attributes[SCALE].c_str());

  r = atoi(attributes[RFILLKEY].c_str());
  g = atoi(attributes[GFILLKEY].c_str());
  b = atoi(attributes[BFILLKEY].c_str());
  borderR = atoi(attributes[BDRR].c_str());
  borderG = atoi(attributes[BDRG].c_str());
  borderB = atoi(attributes[BDRB].c_str());

  offset.x = atoi(attributes[OFFSETX].c_str());
  if(offset.x < 0) offset.x += screenWidth - width + 1;
  offset.y = atoi(attributes[OFFSETY].c_str());
  if(offset.y < 0) offset.y += screenHeight - height + 1;

  surfaceClipRect.x = surfaceClipRect.y = borderThickness;
  surfaceClipRect.w = width - 2 * borderThickness;
  surfaceClipRect.h = height - 2 * borderThickness;

  onscreen = true;
}

Radar::~Radar() {surface = NULL;}

SDL_Surface* Radar::getSurface() {return surface;}

SDL_Rect Radar::getOffset() {return offset;}

SDL_Rect Radar::getSurfaceClipRect() {return surfaceClipRect;}

int Radar::getBorderThickness() {return borderThickness;}

float Radar::getScale() {return scale;}

float Radar::scaleX(float x)
{
  return x * float(width - 2.0 * borderThickness);
}

float Radar::scaleY(float y)
{
  return y * float(height - 2.0 * borderThickness);
}

void Radar::toggle() {onscreen = !onscreen;}

bool Radar::active() {return onscreen;}

void Radar::drawRects()
{
  if(onscreen) {
    // Border
    SDL_FillRect(surface, &surface->clip_rect,
      SDL_MapRGB(surface->format, borderR, borderG, borderB));

    // Surface
    SDL_FillRect(surface, &surfaceClipRect,
      SDL_MapRGB(surface->format, r, g, b));
  }
}