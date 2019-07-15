/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"Telemetry.h"
#include"constants.h"
#include"globals.h"
#include"utilities.h"
#include<map>
#include<sstream>
#include<string>

#include<iomanip>

#define INIT_POS "(0,0)"
#define INIT_VEL "(0,0)"
#define INIT_DIR '0'

Telemetry::Telemetry(SDL_Surface *_surface, std::map<std::string,
  std::string>& attributes, int screenWidth, int screenHeight)
{
  surface = _surface;
  width = atoi(attributes[WIDTH].c_str());
  height = atoi(attributes[HEIGHT].c_str());
  borderThickness = atoi(attributes[BDRTHICKNESS].c_str());

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

  font = TTF_OpenFont(attributes[FONTPATH].c_str(),
           atoi(attributes[FONTSIZE].c_str()));
  textColor.r = atoi(attributes[FONTR].c_str());
  textColor.g = atoi(attributes[FONTG].c_str());
  textColor.b = atoi(attributes[FONTB].c_str());
  healthColor = textColor;

  positionMsg =
    TTF_RenderText_Solid(font, (POSITION_MSG + INIT_POS).c_str(), textColor);
  velocityMsg =
    TTF_RenderText_Solid(font, (VELOCITY_MSG + INIT_VEL).c_str(), textColor);
  directionMsg =
    TTF_RenderText_Solid(font, (DIRECTION_MSG + INIT_DIR).c_str(), textColor);

  fontOffsetX = atoi(attributes[FONTOFFSETX].c_str());
  fontOffsetY = atoi(attributes[FONTOFFSETY].c_str());

  onscreen = false;
}

Telemetry::~Telemetry()
{
  SDL_FreeSurface(velocityMsg);
  SDL_FreeSurface(directionMsg);
  TTF_CloseFont(font);
  surface = NULL;
}

SDL_Surface* Telemetry::getVelocityMsg() {return velocityMsg;}

SDL_Surface* Telemetry::getDirectionMsg() {return directionMsg;}

SDL_Surface* Telemetry::getSurface() {return surface;}

SDL_Rect Telemetry::getOffset() {return offset;}

SDL_Rect Telemetry::getSurfaceClipRect() {return surfaceClipRect;}

int Telemetry::getBorderThickness() {return borderThickness;}

int Telemetry::getFontOffsetX() {return fontOffsetX;}

int Telemetry::getFontOffsetY() {return fontOffsetY;}

void Telemetry::toggle() {onscreen = !onscreen;}

bool Telemetry::active() {return onscreen;}

void Telemetry::update(SDL_Event event, SpaceShip *player)
{
  if(onscreen) {
    int fontX = borderThickness + fontOffsetX;
    int fontY = borderThickness + fontOffsetY;

    SDL_FillRect(surface, &surface->clip_rect,
      SDL_MapRGB(surface->format, borderR, borderG, borderB));

    SDL_FillRect(surface, &surfaceClipRect,
      SDL_MapRGB(surface->format, r, g, b));

    std::ostringstream helSS;
    helSS << player->getHealth();

    int healthValue = ((float)player->getHealth() / player->getMaxHealth()) * 255;
    if(healthValue < 0) healthValue = 0;
    if(healthValue > 255) healthValue = 255;
    healthColor.g = healthColor.b = healthValue;

    healthMsg = TTF_RenderText_Solid(font, HEALTH_MSG.c_str(), textColor);
    applySurface(fontX, fontY, healthMsg, surface, NULL);
    
    fontX += healthMsg->w;

    healthMsg = TTF_RenderText_Solid(font, helSS.str().c_str(), healthColor);
    applySurface(fontX, fontY, healthMsg, surface, NULL);

    fontX = borderThickness + fontOffsetX;
    fontY += healthMsg->h;

    std::ostringstream livSS;
    livSS << LIVES_MSG << player->getLives();
    livesMsg = TTF_RenderText_Solid(font, livSS.str().c_str(), textColor);
    applySurface(fontX, fontY, livesMsg, surface, NULL);

    fontY += livesMsg->h;
    

    std::ostringstream dirSS;
    int dir = int((player->getAbsoluteAngle() - PI/2) *
           (player->getNumSprites() / (2 * PI)));
    if(dir < 0) dir += player->getNumSprites();
    dirSS << DIRECTION_MSG << dir;

    directionMsg = TTF_RenderText_Solid(font, dirSS.str().c_str(), textColor);
    applySurface(fontX, fontY, directionMsg, surface, NULL);

    fontY += directionMsg->h;

    std::ostringstream posSS;
    posSS << POSITION_MSG << '(' << (int)player->getPositionX() << ','
          << (int)player->getPositionY() << ')';

    positionMsg = TTF_RenderText_Solid(font, posSS.str().c_str(), textColor);
    applySurface(fontX, fontY, positionMsg, surface, NULL);

    fontY += positionMsg->h;

    std::ostringstream velSS;
    velSS << std::fixed << std::setprecision(4) << VELOCITY_MSG << '('
          << player->getVelocityX() << ','
          << player->getVelocityY() << ')';

    velocityMsg = TTF_RenderText_Solid(font, velSS.str().c_str(), textColor);
    applySurface(fontX, fontY, velocityMsg, surface, NULL);

    fontY += velocityMsg->h;

    std::ostringstream colSS;
    colSS << COLLISION_MSG;
    if(collisionOn) colSS << ON;
    else colSS << OFF;

    collisionMsg = TTF_RenderText_Solid(font, colSS.str().c_str(), textColor);
    applySurface(fontX, fontY, collisionMsg, surface, NULL);

    fontY += collisionMsg->h;

    /*std::ostringstream damSS;
    damSS << DAMAGE_MSG;
    if(damageOn) damSS << ON;
    else damSS << OFF;

    damageMsg = TTF_RenderText_Solid(font, damSS.str().c_str(), textColor);
    applySurface(fontX, fontY, damageMsg, surface, NULL);

    fontY += damageMsg->h;*/

    std::string ffStr = FF_MSG;
    if(friendlyFireOn) ffStr += ON;
    else ffStr += OFF;

    ffMsg = TTF_RenderText_Solid(font, ffStr.c_str(), textColor);
    applySurface(fontX, fontY, ffMsg, surface, NULL);

    fontY += ffMsg->h;

    //std::ostringstream gravSS;
    //gravSS << GRAVITY_MSG;
    //if(gravityOn) gravSS << ON;
    //else gravSS << OFF;

    //gravityMsg = TTF_RenderText_Solid(font, gravSS.str().c_str(), textColor);
    //applySurface(fontX, fontY, gravityMsg, surface, NULL);

    //fontY += gravityMsg->h;

    std::string diffStr = DIFF_MSG + difficultyToString(difficulty);
    diffMsg = TTF_RenderText_Solid(font, diffStr.c_str(), textColor);
    applySurface(fontX, fontY, diffMsg, surface, NULL);

    //fontY += gravityMsg->h;

    //std::ostringstream inerSS;
    //inerSS << INERTIA_MSG;
    //if(inertiaOn) inerSS << ON;
    //else inerSS << OFF;

    //inertiaMsg = TTF_RenderText_Solid(font, inerSS.str().c_str(), textColor);
    //applySurface(fontX, fontY, inertiaMsg, surface, NULL);

    //fontY += inertiaMsg->h;

    //std::ostringstream rkSS;
    //rkSS << RK4_MSG;
    //if(rk4On) rkSS << ON;
    //else rkSS << OFF;

    //rk4Msg = TTF_RenderText_Solid(font, rkSS.str().c_str(), textColor);
    //applySurface(fontX, fontY, rk4Msg, surface, NULL);
  }
}

void Telemetry::applySurface(int x, int y, SDL_Surface *source,
                   SDL_Surface *destination, SDL_Rect *clip)
{
  //Holds offsets
  SDL_Rect offset;

  //Get offsets
  offset.x = x;
  offset.y = y;

  //Blit
  SDL_BlitSurface(source, clip, destination, &offset);
}