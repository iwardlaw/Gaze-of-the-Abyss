/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   ResourceManager.cpp -- Implementation file for the 'ResourceManager' class,
   which handles all configuration, stores config values in maps, creates and
   destroys the overall GUI, and contains object factories.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   'string' and three 'int's passed to loadImage(); single 'string' to
   getConfigPath(), getInventoryMap(), getSpriteSheet(), getSpriteSet(), and
   getRadarImage(); two 'string's to getInventoryInt(), getInventoryFloat(),
   getInventoryStr(), and readln(); 'string', three 'int's, and a 'SpaceShip'
   pionter to create().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   'SDL_Surface' pointer returned from loadImage(), getSpriteSheet(),
   getRadarImage(), getScreen(), getRadar(), and getTelemetry(); 'string'
   returned from getConfigPath() and getInventoryStr(); 'int' from
   getInventoryInt(); 'float' from getInventoryFloat(); a 'map' from a 'string'
   to a 'string' returned from getInventoryMap(); and a 'GameObject' pointer
   from create().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#include"ResourceManager.h"
#include"Bullet.h"
#include"constants.h"
#include"Explosion.h"
#include"Factory.h"
#include"Missile.h"
#include"utilities.h"
#include"SDL.h"
#include"SDL_ttf.h"
#include<algorithm>
#include<fstream>
#include<map>
#include<sstream>
#include<string>

#include<iostream>

ResourceManager::ResourceManager()
{
  screen = NULL;
  factory = new Factory;
  levelObjective = "";

  parseConfig();
  initializeSystems();
  mapSprites();
  mapRadarImages();
  mapArtAssets();
  mapSFX();
  mapSongs();
}

ResourceManager::~ResourceManager()
{
  std::map<std::string, SDL_Surface*>::iterator sheetIter;
  for(sheetIter=spriteSheets.begin(); sheetIter!=spriteSheets.end();
    ++sheetIter)
    SDL_FreeSurface(sheetIter->second);

  std::map<std::string, SDL_Rect*>::iterator setIter;
  for(setIter=spriteSets.begin(); setIter!=spriteSets.end(); ++setIter)
    delete [] setIter->second;

  std::map<std::string, ArtAsset*>::iterator artIter;
  for(artIter=artAssets.begin(); artIter!=artAssets.end(); ++artIter)
    delete artIter->second;

  std::map<std::string, Mix_Chunk*>::iterator sfxIter;
  for(sfxIter=sfx.begin(); sfxIter!=sfx.end(); ++sfxIter)
    Mix_FreeChunk(sfxIter->second);

  std::map<std::string, Mix_Music*>::iterator musIter;
  for(musIter=songs.begin(); musIter!=songs.end(); ++musIter)
    Mix_FreeMusic(musIter->second);

  delete factory;

  boss = NULL;

  cleanSystems();
}

std::string ResourceManager::getConfigPath(std::string specifier)
{
  if(configPaths.find(specifier) != configPaths.end())
    return configPaths[specifier];
  return "";
}

int ResourceManager::getInventoryInt(std::string type,
              std::string specifier)
{
  if(inventory.find(type) != inventory.end() &&
     inventory[type].find(specifier) != inventory[type].end())
    return atoi(inventory[type][specifier].c_str());
  return 0;
}

float ResourceManager::getInventoryFloat(std::string type,
              std::string specifier)
{
  if(inventory.find(type) != inventory.end() &&
     inventory[type].find(specifier) != inventory[type].end())
    return atof(inventory[type][specifier].c_str());
  return 0.0;
}

std::string ResourceManager::getInventoryStr(std::string type,
              std::string specifier)
{
  if(inventory.find(type) != inventory.end() &&
     inventory[type].find(specifier) != inventory[type].end())
    return inventory[type][specifier];
  return "";
}

std::map<std::string, std::string>
  ResourceManager::getInventoryMap(std::string specifier)
{
  if(inventory.find(specifier) != inventory.end())
    return inventory[specifier];
  
  std::map<std::string, std::string> nullMap;
  nullMap[""] = "";
  return nullMap;
}

std::set<std::string> ResourceManager::getObjectGrouping(std::string specifier)
{
  if(objectGroupings.find(specifier) != objectGroupings.end())
    return objectGroupings[specifier];

  std::set<std::string> nullSet;
  nullSet.insert("");
  return nullSet;
}

SDL_Surface* ResourceManager::getSpriteSheet(std::string specifier)
{
  if(spriteSheets.find(specifier) != spriteSheets.end())
    return spriteSheets[specifier];
  return NULL;
}

SDL_Rect* ResourceManager::getSpriteSet(std::string specifier)
{
  if(spriteSets.find(specifier) != spriteSets.end())
    return spriteSets[specifier];
  return NULL;
}

ArtAsset* ResourceManager::getArtAsset(std::string specifier)
{
  if(artAssets.find(specifier) != artAssets.end())
    return artAssets[specifier];
  return NULL;
}

Mix_Chunk* ResourceManager::getSFX(std::string specifier)
{
  if(sfx.find(specifier) != sfx.end())
    return sfx[specifier];
  return NULL;
}

Mix_Music* ResourceManager::getSong(std::string specifier)
{
  if(songs.find(specifier ) != songs.end())
    return songs[specifier];
  return NULL;
}

SDL_Surface* ResourceManager::getScreen() {return screen;}

SDL_Surface* ResourceManager::getRadarSurface() {return radarSurface;}

SDL_Surface* ResourceManager::getTelemetrySurface() {return telemetrySurface;}

SDL_Surface* ResourceManager::getHealthbarSurface() {return healthbarSurface;}

SDL_Surface* ResourceManager::getLivesIndicatorSurface() {return livesIndicatorSurface;}

std::string ResourceManager::getLevelObjective() {return levelObjective;}

void ResourceManager::buildLevel(int level, SpaceShip *player,
       std::vector<GameObject*> &objects)
{
  std::stringstream fileSS, introSS, loopSS;
  std::ifstream in;
  bool bossLevel = false;
  bool allObjective = false;
  int objectiveObjects = 0;

  player->initialize();
  assignNumEnemies(0);
  assignTotalItems(0);
  assignBoss(NULL);

  fileSS << configPaths[LEVELPATH] << level << configPaths[LEVELEXT];
  in.open(fileSS.str());

  std::string resource, attribute;
  int num, x, y, spread;

  readln(in, resource);
  readln(in, attribute);

  while(in) {
    if(resource == BGM + INTROEXT) {
      introSS << LEVEL << level << INTROEXT;
      songs[introSS.str()] = Mix_LoadMUS(attribute.c_str());
    }
    else if(resource == BGM + LOOPEXT) {
      loopSS << LEVEL << level << LOOPEXT;
      songs[loopSS.str()] = Mix_LoadMUS(attribute.c_str());
    }
    else if(resource == OBJECTIVE) {
      levelObjective = attribute;
      if(levelObjective == CLEAR) {
        readln(in, attribute);
        if(attribute == ALL)
          allObjective = true;
        else if(isdigit(attribute[0]))
          assignNumObjects(atoi(attribute.c_str()));
        else {
          dispLevelBuildError(level, 0);
          exit(1);
        }
      }
      else if(levelObjective == KILL) {
        readln(in, attribute);
        if(attribute == ALL)
          allObjective = true;
        else if(isdigit(attribute[0]))
          assignNumEnemies(atoi(attribute.c_str()));
        else {
          dispLevelBuildError(level, 0);
          exit(1);
        }
      }
      else if(levelObjective == COLLECT) {
        readln(in, attribute);
        if(attribute == ALL)
          allObjective = true;
        else if(isdigit(attribute[0]))
          assignTotalItems(atoi(attribute.c_str()));
        else {
          dispLevelBuildError(level, 0);
          exit(1);
        }
        itemsCollected = 0;
      }
      else // if(levelObjective == BOSS)
        bossLevel = true;
    }
    else {
      num = atoi(attribute.c_str());

      if(allObjective && objectGroupings[levelObjective].find(resource) !=
          objectGroupings[levelObjective].end())
        for(int i=0; i<num; ++i)
          ++objectiveObjects;

      readln(in, attribute);
      x = atoi(attribute.c_str());

      readln(in, attribute);
      y = atoi(attribute.c_str());

      readln(in, attribute);
      spread = atoi(attribute.c_str());

      if(resource.find(HEALTH) != resource.npos)
        for(int i=0; i<num; ++i)
          objects.push_back(factory->create(HEALTH, x, y, spread, player,
            artAssets[resource], artAssets[resource + RADAREXT], this));
      else if(bossLevel && resource == BOSS) {
        GameObject *boss = factory->create(BOSS, x, y, spread, player,
          artAssets[BOSS], artAssets[BOSS + RADAREXT], this);
        assignBoss(boss);
        objects.push_back(boss);
      }
      else
        for(int i=0; i<num; ++i)
          objects.push_back(factory->create(resource, x, y, spread, player,
            artAssets[resource], artAssets[resource + RADAREXT], this));
    }

    readln(in, resource);
    readln(in, attribute);
  }
  in.close();

  if(allObjective)
    if(levelObjective == CLEAR) assignNumObjects(objectiveObjects);
    else if(levelObjective == KILL) assignNumEnemies(objectiveObjects);
    else if(levelObjective == COLLECT) assignTotalItems(objectiveObjects);

  // DEBUGGING PRINTOUT OF OBJECTIVE OBJECTS //
  //std::cerr << "Level " << level << " objective objects: " << objectiveObjects << std::endl;
}

void ResourceManager::clearLevel(SpaceShip *player, std::vector<GameObject*> &objects)
{
  //std::vector<GameObject*>::iterator objIter, start = objects.begin();
  //if(!player->dead()) ++start;

  //for(objIter=start; objIter!=objects.end(); ++objIter)
  //  delete *objIter;
  //objects.erase(start, objects.end());

  std::vector<GameObject*>::iterator objIter;
  for(objIter=++objects.begin(); objIter!=objects.end(); ++objIter)
    delete *objIter;
  objects.erase(++objects.begin(), objects.end());

  levelObjective = "";
}

void ResourceManager::makeBullet(std::string type, GameObject *source,
  SpaceShip *player, std::vector<GameObject*> &objects, int life)
{
  //ArtAsset *artAsset, *radarAsset;

  //artAsset = artAssets[type];
  //radarAsset = artAssets[type + RADAREXT];

  objects.push_back(new Bullet(source, player, artAssets[type],
    artAssets[type + RADAREXT], life, this));
}

void ResourceManager::makeMissile(GameObject *source, GameObject *target,
  SpaceShip *player, std::vector<GameObject*> &objects, int life)
{
  objects.push_back(new Missile(source, target, player, artAssets[MISSILE],
    artAssets[MISSILE + RADAREXT], life, this));
}

void ResourceManager::makeExplosion(GameObject *source, SpaceShip *player,
  std::vector<GameObject*> &objects)
{
  objects.push_back(new Explosion(-source->getPositionX(), -source->getPositionY(),
    player, artAssets[EXPLOSION], this));
}

void ResourceManager::dropHealth(HealthSize size, GameObject *source,
  SpaceShip *player, std::vector<GameObject*> &objects)
{
  std::string resource;
  if(size == SMALL) resource = HEALTH_SM;
  else if(size == MED) resource = HEALTH_MD;
  else if(size == LARGE) resource = HEALTH_LG;
  else resource = HEALTH_FL;

  objects.push_back(new Health(-source->getPositionX(), -source->getPositionY(), 0,
    player, artAssets[resource], artAssets[resource + RADAREXT], this));
}

void ResourceManager::dropArmor(GameObject *source, SpaceShip *player,
  std::vector<GameObject*> &objects)
{
  objects.push_back(new Armor(-source->getPositionX(), -source->getPositionY(), 0,
    player, artAssets[ARMOR], artAssets[ARMOR + RADAREXT], this));
}

void ResourceManager::setChunkVolume(std::string s, GameObject *obj,
  SpaceShip *player, int volDist, int amplitude)
{
  int relDist = round(getDist(obj->getPositionX(), obj->getPositionY(),
    player->getPositionX(), player->getPositionY()) - volDist) / amplitude;
  if(relDist == 0) relDist = 1;

  Mix_VolumeChunk(sfx[s], MIX_MAX_VOLUME / relDist);
}

void ResourceManager::playSound(std::string name, float playerDist, int volDist,
  int amplitude)
{
  if(playerDist <= MAX_SOUND_DIST) {
    int volDividend = (playerDist - volDist) / amplitude;
    if(volDividend == 0) volDividend = 1;

    Mix_VolumeChunk(sfx[name], MIX_MAX_VOLUME / volDividend);
    Mix_PlayChannel(-1, sfx[name], 0);
  }
}

bool ResourceManager::addToInfoLog(std::string objType)
{
  return (infoLog.insert(objType)).second;
}

bool ResourceManager::addToInv(GameObject *obj)
{
  return (inv.insert(obj)).second;
}

bool ResourceManager::checkObjectives()
{
  //switch(level) {
  //  case 1:
  //    return numObjects == 0;
  //  case 2:
  //    return numEnemies == 0;
  //  case 3:
  //    return itemsCollected == totalItems;
  //  case 4:
  //    if(boss != NULL) return boss->dead();
  //    else return false;
  //  default:
  //    return false;
  //}

  if(levelObjective == CLEAR)
    return numObjects == 0;

  if(levelObjective == KILL)
    return numEnemies == 0;

  if(levelObjective == COLLECT)
    return itemsCollected == totalItems;

  if(levelObjective == BOSS)
    if(boss != NULL) return boss->dead();
    return false;

  return false;
}

void ResourceManager::assignNumObjects(int n) {numObjects = n;}

void ResourceManager::countObject() {--numObjects;}

void ResourceManager::assignNumEnemies(int n) {numEnemies = n;}

void ResourceManager::countEnemy() {--numEnemies;}

void ResourceManager::assignTotalItems(int n) {totalItems = n;}

void ResourceManager::collectItem() {++itemsCollected;}

void ResourceManager::assignBoss(GameObject *b) {boss = b;}

bool ResourceManager::checkBossLevel() {return boss != NULL;}

void ResourceManager::parseConfig()
{
  std::ifstream in (CONFIG_PATH_FILE);
  std::string line;
  std::map<std::string, std::string>::iterator pathIter;
  std::string radarResource, iconResource, objectGroup;

  while(in.good()) {
    readln(in, line);
    if(line != "")
      configPaths[line.substr(0, line.find('='))] =
        line.substr(line.find('=') + 1, std::string::npos);
  }

  in.close();

  for(pathIter=configPaths.begin(); pathIter!=configPaths.end(); ++pathIter)
    if(pathIter->first != LEVELPATH && pathIter->first != LEVELEXT)
      if(pathIter->first != GROUPINGS) {
        in.open(pathIter->second);
        while(in.good()) {
          readln(in, line);
          if(line != "")
            inventory[pathIter->first][line.substr(0, line.find('='))] =
            line.substr(line.find('=') + 1, std::string::npos);
        }
        in.close();
        if(inventory[pathIter->first].find(RADARRESOURCEPATH) !=
           inventory[pathIter->first].end()) {
          in.open(inventory[pathIter->first][RADARRESOURCEPATH]);
          radarResource = pathIter->first + RADAREXT;
          while(in.good()) {
            readln(in, line);
            if(line != "") {
              inventory[radarResource][line.substr(0, line.find('='))] = 
                line.substr(line.find('=') + 1, std::string::npos);
            }
          }
          in.close();
        }
        if(inventory[pathIter->first].find(ICONPATH) !=
           inventory[pathIter->first].end()) {
          in.open(inventory[pathIter->first][ICONPATH]);
          iconResource = pathIter->first + ICONEXT;
          while(in.good()) {
            readln(in, line);
            if(line != "") {
              inventory[iconResource][line.substr(0, line.find('='))] =
                line.substr(line.find('=') + 1, std::string::npos);
            }
          }
          in.close();
        }
      }
      else { // if(pathIter->first == GROUPINGS)
        in.open(pathIter->second);

        std::set<std::string> objectSet;
        while(in.good()) {
          readln(in, line);
          if(line != "") {
            objectGroup = line;
            while(in.good() && in.peek() != '\n') {
              while(isspace(in.peek()) && in.peek() != '\n') in.get();
              if(in.peek() != '\n') {
                readln(in, line);
                if(line != "") objectSet.insert(line);
              }
            }
            objectGroupings[objectGroup] = objectSet;
            objectSet.clear();
          }
        }
        in.close();
      }

    // DEBUGGING PRINTOUT OF 'inventory' //
    std::map<std::string, std::map<std::string, std::string>>::iterator invIter,
      startOffset = inventory.begin(), stopOffset = inventory.end();
    unsigned startOffsetValue = 0; // <-- Specify how far into 'inventory' to start.
    unsigned stopOffsetValue  = 12; // <-- Specify how far before the end of 'inventory' to stop.
    if(startOffsetValue < inventory.size())
      for(int i=0; i<startOffsetValue; ++i) ++startOffset;
    if(startOffsetValue + stopOffsetValue <= inventory.size())
      for(int i=0; i<stopOffsetValue; ++i) --stopOffset;
    for(invIter=startOffset; invIter!=stopOffset; ++invIter) {
      for(pathIter=invIter->second.begin(); pathIter!=invIter->second.end(); ++pathIter)
        std::cerr << invIter->first << '[' << pathIter->first << "] = " << pathIter->second << std::endl;
      std::cerr << std::endl;
    }

    // DEBUGGING PRINTOUT OF OBJECT GROUPS //
    //std::map<std::string, std::set<std::string>>::iterator gpIter;
    //std::set<std::string>::iterator setIter;
    //std::cerr << "Object Groupings:\n" << std::endl;
    //for(gpIter=objectGroupings.begin(); gpIter!=objectGroupings.end(); ++gpIter) {
    //  std::cerr << gpIter->first << "  ";
    //  for(setIter=gpIter->second.begin(); setIter!=gpIter->second.end(); ++setIter)
    //    std::cerr << *setIter << " ";
    //  std::cerr << std::endl;
    //}

  if(in) in.close();
}

void ResourceManager::initializeSystems()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS, CHUNK_SIZE);

  Mix_AllocateChannels(MAX_CHANNELS);

  int width = atoi(inventory[SCREEN][WIDTH].c_str());
  int height = atoi(inventory[SCREEN][HEIGHT].c_str());
  int bpp = atoi(inventory[SCREEN][BPP].c_str());
  int frameDelay = atoi(inventory[SCREEN][FRAMEDELAY].c_str());
  std::string windowTitle = inventory[SCREEN][NAME];

  //Construct Game Window (screen)
  screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);

  //Set Window Title
  SDL_WM_SetCaption(windowTitle.c_str(), NULL);

  // Screen Text
  screenFont = TTF_OpenFont(inventory[SCREEN][FONTPATH].c_str(), 
    atoi(inventory[SCREEN][FONTSIZE].c_str()));
  screenFontColor.r = atoi(inventory[SCREEN][FONTR].c_str());
  screenFontColor.g = atoi(inventory[SCREEN][FONTG].c_str());
  screenFontColor.b = atoi(inventory[SCREEN][FONTB].c_str());

  // Radar
  width = atoi(inventory[RADAR][WIDTH].c_str());
  height = atoi(inventory[RADAR][HEIGHT].c_str());

  Uint32 rMask = screen->format->Rmask;
  Uint32 gMask = screen->format->Gmask;
  Uint32 bMask = screen->format->Bmask;
  Uint32 aMask = screen->format->Amask;

  int opacity;
  if(getInventoryStr(SCREEN, SETMASTERHUDOPACITY) == TRUE) {
    opacity = atoi(inventory[SCREEN][MASTERHUDOPACITY].c_str());
  }

  radarSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, bpp, rMask, gMask,
            bMask, aMask);

  if(getInventoryStr(SCREEN, SETMASTERHUDOPACITY) == FALSE)
    opacity = atoi(inventory[RADAR][OPACITY].c_str());
  SDL_SetAlpha(radarSurface, SDL_SRCALPHA, median(0, opacity, 255));

  // Telemetry
  width = atoi(inventory[TELEMETRY][WIDTH].c_str());
  height = atoi(inventory[TELEMETRY][HEIGHT].c_str());

  telemetrySurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, bpp, rMask,
                gMask, bMask, aMask);

  if(getInventoryStr(SCREEN, SETMASTERHUDOPACITY) == FALSE)
    opacity = atoi(inventory[TELEMETRY][OPACITY].c_str());
  SDL_SetAlpha(telemetrySurface, SDL_SRCALPHA, median(0, opacity, 255));

  // Healthbar
  width = atoi(inventory[HEALTHBAR][WIDTH].c_str());
  height = atoi(inventory[HEALTHBAR][HEIGHT].c_str());

  healthbarSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, bpp, rMask,
    gMask, bMask, aMask);

  if(getInventoryStr(SCREEN, SETMASTERHUDOPACITY) == FALSE)
    opacity = atoi(inventory[HEALTHBAR][OPACITY].c_str());
  SDL_SetAlpha(healthbarSurface, SDL_SRCALPHA, median(0, opacity, 255));

  // Lives Indicator
  //width = 100;
  //height = atoi(inventory[LIVESICON][HEIGHT].c_str());

  //livesIndicatorSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, bpp, rMask,
  //  gMask, bMask, aMask);
}

void ResourceManager::mapSprites()
{
  std::map<std::string, std::map<std::string, std::string>>::iterator invIter;
  int numSprites, ncols, spriteWidth, spriteHeight, rKey, gKey, bKey;
  SDL_Rect *sprites = NULL;
  SDL_Surface *spriteSheet = NULL;
  
  for(invIter=inventory.begin(); invIter!=inventory.end(); ++invIter)
    if((invIter->second).find(IMAGEPATH) != (invIter->second).end()) {
      numSprites = atoi((invIter->second)[NUMSPRITES].c_str());
      ncols = atoi((invIter->second)[NCOLS].c_str());
      spriteWidth = atoi((invIter->second)[WIDTH].c_str());
      spriteHeight = atoi((invIter->second)[HEIGHT].c_str());
      rKey = atoi((invIter->second)[RMAPKEY].c_str());
      gKey = atoi((invIter->second)[GMAPKEY].c_str());
      bKey = atoi((invIter->second)[BMAPKEY].c_str());

      sprites = new SDL_Rect[numSprites];
      spriteSheet = loadImage((invIter->second)[IMAGEPATH], rKey, gKey, bKey);

      spriteSheets[invIter->first] = spriteSheet;

      for(int i=0;i<numSprites;i++){
        int row = i/ncols;
        int col = i%ncols;
        sprites[i].x = col*spriteWidth;
        sprites[i].y = row*spriteHeight;
        sprites[i].w = spriteWidth;
        sprites[i].h = spriteHeight;
      }

      spriteSets[invIter->first] = sprites;
      sprites = NULL;
      spriteSheet = NULL;
    }
}

void ResourceManager::mapRadarImages()
{
  std::map<std::string, std::map<std::string, std::string>>::iterator invIter;
  int rKey, gKey, bKey;
  SDL_Surface *radarImage = NULL;
  
  for(invIter=inventory.begin(); invIter!=inventory.end(); ++invIter)
    if((invIter->second).find(RADARIMAGEPATH) != (invIter->second).end()) {
      rKey = atoi((invIter->second)[RADARRMAPKEY].c_str());
      gKey = atoi((invIter->second)[RADARGMAPKEY].c_str());
      bKey = atoi((invIter->second)[RADARBMAPKEY].c_str());

      radarImage = loadImage((invIter->second)[RADARIMAGEPATH], rKey, gKey,bKey);

      radarImages[invIter->first] = radarImage;
    }
}

void ResourceManager::mapArtAssets()
{
  std::map<std::string, std::map<std::string, std::string>>::iterator invIter;
  std::string radarResource;

  for(invIter=inventory.begin(); invIter!=inventory.end(); ++invIter)
    if((invIter->second).find(IMAGEPATH) != (invIter->second).end())
      artAssets[invIter->first] = new ArtAsset(invIter->second);

  // DEBUGGING PRINTOUT //
  //std::map<std::string, ArtAsset*>::iterator artIter;
  //for(artIter=artAssets.begin(); artIter!=artAssets.end(); ++artIter)
  //  std::cerr << "artAssets[" << artIter->first << "] exists ("
  //            << artIter->second->getWidth() << 'x' << artIter->second->getHeight()
  //            << ')' << std::endl;
}

void ResourceManager::mapSFX()
{
  std::map<std::string, std::string>::iterator sfxIter;

  for(sfxIter=inventory[SFX].begin(); sfxIter!=inventory[SFX].end(); ++sfxIter)
    sfx[sfxIter->first] = Mix_LoadWAV(sfxIter->second.c_str());

  // DEBUGGING PRINTOUT //
  //for(sfxIter=inventory[SFX].begin(); sfxIter!=inventory[SFX].end(); ++sfxIter)
  //  std::cerr << "sfx[" << sfxIter->first << "] exists (" << sfxIter->second << ')'
  //            << std::endl;
}

void ResourceManager::mapSongs()
{
  std::map<std::string, std::map<std::string, std::string>>::iterator invIter;

  for(invIter=inventory.begin(); invIter!=inventory.end(); ++invIter)
    if(invIter->second.find(BGM) != invIter->second.end())
      songs[invIter->first] = Mix_LoadMUS(invIter->second[BGM].c_str());
}

void ResourceManager::dispLevelBuildError(int level, int errorCode)
{
  std::cerr << "ERROR: ";
  switch(errorCode) {
    case 0:
      std::cerr << "Unspecified objective parameter in config file for level "
                << level << ".\n  Enter 'ALL' or a positive integer." << std::endl;
      break;
    default:
      std::cerr << "[unidentified error]" << std::endl;
  }
}

void ResourceManager::cleanSystems()
{
  Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();
}