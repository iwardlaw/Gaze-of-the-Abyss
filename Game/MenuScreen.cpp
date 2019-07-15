/*
   Isaac Wardlaw
   18 Dec 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"MenuScreen.h"
#include"constants.h"
#include"utilities.h"

MenuScreen::MenuScreen(std::map<std::string, std::string> &commonAttributes,
  std::map<std::string, std::string> &uniqueAttributes,
  ResourceManager *_manager)
{
  /*
  SDL_Surface *scr = manager->getScreen();

  int w = scr->w;
  int h = scr->h;
  int bpp = manager->getInventoryInt(SCREEN, BPP);
  Uint32 rMask = scr->format->Rmask;
  Uint32 gMask = scr->format->Gmask;
  Uint32 bMask = scr->format->Bmask;
  Uint32 aMask = scr->format->Amask;
  int opacity = atoi(commonAttributes[OPACITY].c_str());
  opacity = median(0, opacity, 255);

  masterSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, bpp, rMask, gMask,
    bMask, aMask);
  SDL_SetAlpha(masterSurface, SDL_SRCALPHA, opacity);

  w = atoi(commonAttributes[MENUWIDTH].c_str());
  h = atoi(commonAttributes[MENUHEIGHT].c_str());

  menuSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, bpp, rMask, gMask,
    bMask, aMask);
  SDL_SetAlpha(menuSurface, SDL_SRCALPHA, opacity);

  w = atoi(commonAttributes[IMAGEWIDTH].c_str());
  h = atoi(commonAttributes[IMAGEHEIGHT].c_str());

  imageSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, bpp, rMask, gMask,
    bMask, aMask);
  SDL_SetAlpha(imageSurface, SDL_SRCALPHA, opacity);

  w = atoi(commonAttributes[TEXTWIDTH].c_str());
  h = atoi(commonAttributes[TEXTHEIGHT].c_str());

  textSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, bpp, rMask, gMask,
    bMask, aMask);
  SDL_SetAlpha(textSurface, SDL_SRCALPHA, opacity);

  title = uniqueAttributes[TITLE];

  if(uniqueAttributes[SHOWTITLE] == TRUE)
    showsTitle = true;
  else //if(uniqueAttributes[SHOWTITLE] == FALSE)
    showsTitle = false;

  parentTitle = uniqueAttributes[PARENT];

  //if(uniqueAttributes[PARENT] == CONFIG_NULL)
  //  parent = NULL;
  //else
  //  parent = uniqueAttributes[PARENT];
  */
}