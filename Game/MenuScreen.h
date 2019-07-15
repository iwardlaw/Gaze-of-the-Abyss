/*
   Isaac Wardlaw
   18 Dec 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include"MenuItem.h"
#include"ResourceManager.h"
#include"SDL.h"
#include"SDL_image.h"
#include<map>
#include<string>
#include<vector>

class MenuScreen {
  private:
    SDL_Surface *masterSurface, *menuSurface, *imageSurface, *textSurface;
    std::string title, parentTitle;
    MenuScreen *parent;
    std::vector<MenuItem*> items;
    bool showsTitle;
    ResourceManager *manager;
  public:
    MenuScreen(std::map<std::string, std::string> &commonAttributes,
      std::map<std::string, std::string> &uniqueAttributes,
      ResourceManager *_manager);
    std::string getTitle();
};