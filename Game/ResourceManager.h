/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   ResourceManager.h -- Header file defining the 'ResourceManager' class, which
   handles all configuration, stores config values in maps, creates and
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

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include"ArtAsset.h"
#include"GameObject.h"
#include"SpaceShip.h"
#include"SDL.h"
#include"SDL_mixer.h"
#include"SDL_ttf.h"
#include<list>
#include<map>
#include<set>
#include<string>
#include<vector>

class Factory;

class ResourceManager {
  private:
    Factory *factory;
    std::map<std::string, std::string> configPaths;
    std::map<std::string, std::map<std::string, std::string>> inventory;
    std::map<std::string, std::set<std::string>> objectGroupings;
    std::map<std::string, SDL_Surface*> spriteSheets;
    std::map<std::string, SDL_Rect*> spriteSets;
    std::map<std::string, SDL_Surface*> radarImages;
    std::map<std::string, ArtAsset*> artAssets;
    std::map<std::string, Mix_Chunk*> sfx;
    std::map<std::string, Mix_Music*> songs;
    std::set<std::string> infoLog;
    std::set<GameObject*> inv;
    SDL_Surface *screen;
    SDL_Surface *radarSurface;
    SDL_Surface *telemetrySurface;
    SDL_Surface *healthbarSurface;
    SDL_Surface *livesIndicatorSurface;
    TTF_Font *screenFont;
    SDL_Color screenFontColor;
    SDL_Surface *missionMsgSurface, *missionMsg;

    // Level Data
    std::string levelObjective;
    int numObjects;
    int numEnemies;
    int itemsCollected, totalItems;
    GameObject *boss;

    void parseConfig();
    /* Reads all configuration files and fills the member maps according to the
         data that are found.
       Precondition: The file referred to by 'CONFIG_PATH_FILE' must include
                     paths to configuration files for all game objects, GUI
                     elements, fonts, and levels; the contetns of all of these
                     files must conform to the <name>=<value> format.
       Postcondition: All configuration parsed, filling the maps 'configPaths',
                      and 'inventory'.
       */
    void initializeSystems();
    /* Sets up GUI and sound elements.
       Precondition: parseConfig() must have executed.
       Postcondition: Screen, radar surface, and telemetry surface all
                      created according to their config files.
         */
    void mapSprites();
    /* Creates and maps sprite sheet surfaces and sprite arrays for each type
         of game object.
       Precondition: parseConfig() must have executed.
       Postcondition: Each type of game object listed in the config files has a
                      sprite sheet and a sprite array; pointers to these can
                      then be used in construction.
       */         
    void mapRadarImages();
    /* Creates and maps surfaces for radar images.
       Precondition: parseConfig() must have executed.
       Postcondition: Each type of game object listed in the config files has
                      a (probably small) radar image.
       */
    void mapArtAssets();

    void mapSFX();

    void mapSongs();

    void dispLevelBuildError(int, int);

    void cleanSystems();
    /* Closes, quits, or frees each GUI/sound element.
       PostCondition: Mixer, TTF, and SDL quit.
       */
  public:
    ResourceManager();
    /* Constructor.
       Postcondition: Sets 'screen' to 'NULL', then runs parseConfig(),
                      initializeGUI(), mapSprites(), and mapRadarImages().
       */
    virtual ~ResourceManager();
    /* Destructor.
       Postcondition: Deletes all pointers and runs cleanGUI().
       */
    std::string getConfigPath(std::string);
    /* Getter for an element of 'configPaths'.
       Postcondition: Returns element of 'configPaths' indicated by the arg.
       */
    int getInventoryInt(std::string, std::string);
    /* Getter for an integer in 'inventory'.
       Postcondition: Returns integer at 'inventory[1st arg][2nd arg]'.
       */
    float getInventoryFloat(std::string, std::string);
    /* Getter for a floating-point value in 'inventory'.
       Postcondition: Returns float at 'inventory[1st arg][2nd arg]'.
       */
    std::string getInventoryStr(std::string, std::string);
    /* Getter for a string in 'inventory'.
       Postcondition: Returns string at 'inventory[1st arg][2nd arg]'.
       */
    std::map<std::string, std::string> getInventoryMap(std::string);
    /* Getter for a map in 'inventory'.
       Postcondition: Returns the map located at 'inventory[arg]'.
       */
    std::set<std::string> getObjectGrouping(std::string);
    /* Getter for a set in 'objectGroupings'.
       Postcondition: Returns the set located at 'objectGrouping[arg]'.
       */
    SDL_Surface* getSpriteSheet(std::string);
    /* Getter for an element in 'spriteSheets'.
       Postcondition: Returns 'spriteSheets[arg]'.
       */
    SDL_Rect* getSpriteSet(std::string);
    /* Getter for an element in 'spriteSets'.
       Postcondition: Returns 'spriteSets[art]'.
       */
    SDL_Surface* getRadarImage(std::string);
    /* Getter for an element in 'radarImages'.
       Postcondition: Returns 'radarImages[arg]'.
       */
    ArtAsset* getArtAsset(std::string);
    /* Getter for an element in 'artAssets'.
       Postcondition: Returns 'artAssets[arg]'.
       */
    Mix_Chunk* getSFX(std::string);
    /* Getter for an element in 'sfx'.
       Postcondition: Returns 'sfx[arg]'.
       */
    Mix_Music* getSong(std::string);
    /* Getter for an element in 'songs'.
       Postcondition: Returns 'songs[arg]'.
       */
    SDL_Surface* getScreen();
    /* Getter for 'screen'.
       Postcondition: Returns 'screen'.
       */
    SDL_Surface* getRadarSurface();
    /* Getter for the 'radar' surface.
       Postcondition: Returns 'radar'.
       */
    SDL_Surface* getTelemetrySurface();
    /* Getter for the 'telemetry' surface.
       Postcondition: Returns 'telemetry'.
       */
    SDL_Surface* getHealthbarSurface();
    /* Getter for the 'healthbar' surface.
       Postcondition: Returns 'healthbar'.
       */
    SDL_Surface* getLivesIndicatorSurface();
    /* Getter for the 'livesIndicator' surface.
       Postcondition: Returns 'livesIndicatorSurface'.
       */
    std::string getLevelObjective();
    /* Getter for the current level objective.
       Postcondition: Returns 'levelObjective'.
       */
    void buildLevel(int, SpaceShip*, std::vector<GameObject*>&);

    void clearLevel(SpaceShip*, std::vector<GameObject*>&);

    void makeBullet(std::string, GameObject*, SpaceShip*, std::vector<GameObject*>&, int);

    void makeMissile(GameObject*, GameObject*, SpaceShip*, std::vector<GameObject*>&, int);

    void makeExplosion(GameObject*, SpaceShip*, std::vector<GameObject*>&);

    void dropHealth(HealthSize, GameObject*, SpaceShip*, std::vector<GameObject*>&);

    void dropArmor(GameObject*, SpaceShip*, std::vector<GameObject*>&);

    void setChunkVolume(std::string, GameObject*, SpaceShip*, int, int);

    void playSound(std::string name, float playerDist = 0.0, int volDist = 0,
      int amplitude = 1000);

    bool addToInfoLog(std::string);

    bool addToInv(GameObject*);

    bool checkObjectives();
    /* See if the level's objectives are completed and advance to next level if
         so.
       */

    void assignNumObjects(int);

    void countObject();

    void assignNumEnemies(int);

    void countEnemy();

    void assignTotalItems(int);

    void collectItem();

    void assignBoss(GameObject*);

    bool checkBossLevel();
};

#endif