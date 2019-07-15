/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"Healthbar.h"
#include"constants.h"
#include"SpaceShip.h"
#include"utilities.h"
#include<sstream>

Healthbar::Healthbar(SDL_Surface *_surface, std::map<std::string,
  std::string> &attributes, int screenWidth, int screenHeight)
{
  surface = _surface;
  width = atoi(attributes[WIDTH].c_str());
  height = atoi(attributes[HEIGHT].c_str());
  borderThickness = atoi(attributes[BDRTHICKNESS].c_str());

  rFill = atoi(attributes[RFILLKEY].c_str());
  gFill = atoi(attributes[GFILLKEY].c_str());
  bFill = atoi(attributes[BFILLKEY].c_str());
  fullR = atoi(attributes[FULLR].c_str());
  fullG = atoi(attributes[FULLG].c_str());
  fullB = atoi(attributes[FULLB].c_str());
  emptyR = atoi(attributes[EMPTYR].c_str());
  emptyG = atoi(attributes[EMPTYG].c_str());
  emptyB = atoi(attributes[EMPTYB].c_str());
  //armorR = atoi(attributes[ARMORR].c_str());
  //armorG = atoi(attributes[ARMORG].c_str());
  //armorB = atoi(attributes[ARMORB].c_str());
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
  armorColor.r = atoi(attributes[ARMORR].c_str());
  armorColor.g = atoi(attributes[ARMORG].c_str());
  armorColor.b = atoi(attributes[ARMORB].c_str());

  surfaceClipRect.x = surfaceClipRect.y = borderThickness;
  surfaceClipRect.w = width - 2 * borderThickness;
  surfaceClipRect.h = height - 2 * borderThickness;

  onscreen = true;

  SDL_FillRect(surface, &surface->clip_rect,
    SDL_MapRGB(surface->format, borderR, borderG, borderB));
}

Healthbar::~Healthbar()
{
  SDL_FreeSurface(surface);
  surface = NULL;
  TTF_CloseFont(font);
  font = NULL;
}

SDL_Surface* Healthbar::getSurface() {return surface;}

SDL_Rect Healthbar::getOffset() {return offset;}

SDL_Rect Healthbar::getSurfaceClipRect() {return surfaceClipRect;}

int Healthbar::getBorderThickness() {return borderThickness;}

void Healthbar::toggle() {onscreen = !onscreen;}

bool Healthbar::active() {return onscreen;}

void Healthbar::update(SpaceShip *player)
{
  if(onscreen) {
    SDL_FillRect(surface, &surfaceClipRect,
      SDL_MapRGB(surface->format, rFill, gFill, bFill));

    int plHealth = player->getHealth();
    if(plHealth < 0) plHealth = 0;
    int maxHealth = player->getMaxHealth();
    float healthPercentage = (float)plHealth / maxHealth;

    SDL_Rect bar;
    bar.x = bar.y = 5;
    bar.h = 20;
    bar.w = healthPercentage * 190;

    int r, g, b;
    int halfHealth = maxHealth / 2;
    if(plHealth > halfHealth) {
      r = (float(maxHealth - plHealth) / halfHealth) * 225;
      g = 225;
    }
    else {
      g = ((float)plHealth / halfHealth) * 225;
      r = 225;
    }    
    b = (fullB - emptyB) * healthPercentage + emptyB;

    SDL_FillRect(surface, &bar, SDL_MapRGB(surface->format, r, g, b));

    int plArmor = player->getArmor();
    if(plArmor > 0) {
      int maxArmor = player->getMaxArmor();
      float armorPercentage = (float)plArmor / maxArmor;

      bar.y += bar.h / 2 - 1;
      bar.h = bar.h / 2 + 1;
      bar.w = armorPercentage * 190 + 1;
      SDL_FillRect(surface, &bar, SDL_MapRGB(surface->format, rFill, gFill, bFill));

      ++bar.y;
      --bar.h;
      --bar.w;
      SDL_FillRect(surface, &bar, SDL_MapRGB(surface->format, armorColor.r,
        armorColor.g, armorColor.b));
    }

    int val = healthPercentage * 255;
    if(val < 0) val = 0;
    if(val > 255) val = 255;
    textColor.g = textColor.b = val;

    std::ostringstream healthSS;
    if(player->getHealth() >= 0) healthSS << plHealth;
    else healthSS << NEG_HEALTH_VAL;

    SDL_Surface *value = TTF_RenderText_Solid(font, healthSS.str().c_str(), textColor);
    int fontX = (surface->w - value->w) / 4;
    int fontY = (surface->h - (bar.y+bar.h) - value->h) / 2 + (bar.y+bar.h);
    applySurface(fontX, fontY, value, surface, NULL);

    std::ostringstream armorSS;
    armorSS << plArmor;

    value = TTF_RenderText_Solid(font, armorSS.str().c_str(), armorColor);
    fontX = (surface->w - value->w) * 0.75;
    applySurface(fontX, fontY, value, surface, NULL);
  }
}