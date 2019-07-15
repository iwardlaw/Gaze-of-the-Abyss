/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Portions by Keith Bush, PhD
   26 Jan 2012
   ========================
   File Description:
   GameEngine.h -- Header file defining the 'GameEngine' class. Manages all
   game functionality and preserves screen, timer, and event parameters. The
   vector contained herein comprises pointers to all objects in the game.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Two 'int's, two 'SDL_Surface' pointers, and an 'SDL_Rect' pointer passed to
   applySurface().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include"Factory.h"
#include"GameObject.h"
#include"Healthbar.h"
#include"Radar.h"
#include"ResourceManager.h"
#include"SpaceShip.h"
#include"Telemetry.h"
#include"Timer.h"
#include"SDL.h"
#include<sstream>
#include<string>
#include<vector>

class GameEngine{
  private:
    //GUI/Engine Constructs
    int level, nextLevel;
    bool bossLevel;
    int screenHeight;
    int screenWidth;
    int screenBPP;
    int frameDelay;
    std::string windowTitle;
    SDL_Event event;
    SDL_Surface *screen;
    Radar *radar;
    Telemetry *telemetry;
    Healthbar *healthbar;
    SpaceShip *player;
    Timer fps;
    ResourceManager resourceManager;

    //Onscreen Messages
    SDL_Surface *gameOverMsg, *restartMsg, *pauseMsg, *objectiveMsg, *livesIndicator;
    //SDL_Surface *livesIcon;
    SDL_Rect gameOverOffset, restartOffset, pauseMsgOffset, objectiveOffset, livesIndicatorOffset;
    TTF_Font *font, *smallFont;
    SDL_Color textColor;
    int objectiveCounter, livesIndicatorCounter;

    int bulletLife;

    bool playing;

    int debugR, debugG, debugB;

    //Game Elements
    std::vector<GameObject*> objects;  
    std::vector<GameObject*>::iterator oiter; 

    //Level Data
    std::string levelName;
    bool musicIntro, inBattle, levelClear, gameOver;
    int numEnemies;
    int itemsCollected, totalItems;
    GameObject *boss;

    //Major helper functions
    void createPlayer();

    void resolveOverlap();

    void run();
    /* Performs main game loop: handles events, updates all objects, draws all
         objects, and manages timer.
       Postcondition: Game changes according to user's command: all objects are
                      updated and drawn and rendered to the screen and, if
                      active, radar at an appropriate rate; closes window if
                      user exits it or pushes ESC.
       */

    //State update
    void changeGameState();
    /* Changes the state of every game object by iterating through 'objects'
         and calling the update() method of each object pointed to. Also
         updates the telemetry, if active, based on player's stats.
       Postcondition: All game objects' internal states are updated and
                      telemetry will reflect player's velocity, direction, and
                      position.
       */

    //State presentation
    void displayGameState();
    /* Clears the screen and redraws all sprites according to player's position
         and absolute angle to give the illusion of movement; uses each
         object's draw() method similarly to update() in changeGameState();
         also draws radar and telemetry to the screen, if they are active.
       Postcondition: All objects change position on the screen in accordance
                      with player's or their own movement; radar and telemetry
                      shown if activated.
       */
    void deleteDeadObjects();
    /* Removes any dead objects from the game.
       Postcondition: All objects for whom dead() is true are erased from
                      'objects'.
       */
    void destroyEnemies();
    /* Destroys all enemies in the current level. Primarily a tool for boss
         levels.
       */
    void clearLevel(std::string objective);
    /* A function to facilitate testing. Obtains all collectibles in a level.
       */

    //Display helper functions
    void initObjectiveMsg();

    void initLivesIndicator();

    // Pause Functions
    void pause();

    void displayPauseScreen();

  public:
    GameEngine();
    /* Constructor. Initializes game objects and runs. In tandem with its
         'resourceManager' member, contains all functionality necessary to play
         the game without any extra steps.
       Postcondition: Game is initiated and run until closed.
       */
    virtual ~GameEngine();
    /* Destructor.
       Postcondition: 'radar', 'telemetry', and all elements within 'objects'
                      are deallocated; 'screen' set to 'NULL'.
       */
};

#endif