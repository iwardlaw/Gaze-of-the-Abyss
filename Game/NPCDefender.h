/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef NPCDEFENDER_H
#define NPCDEFENDER_H

#include"NPC.h"
#include"enums.h"
#include<queue>

#define NUM_STATES 2
#define NUM_STIMULI 3

class NPCDefender : public NPC {
  protected:
    NPCState state;
    NPCStimulus stimulus;
    NPCState matrix[NUM_STATES][NUM_STIMULI];
    float sightRadius, baseRadius;
    float baseX, baseY;
    float targetPosX, targetPosY;
    float targetVelX, targetVelY;

    PathDirection prevDir;
    PathThrust prevThr;
    int prevHealth;

    int shootClock, shootDelay;
    int attackMemClock;

    // Helper Functions
    NPCStimulus getStimulus();
    virtual void pursueTarget();
    void shoot(std::vector<GameObject*>&);
    void initializeMatrix();
    void drawBase(SDL_Surface*);

  public:
    NPCDefender(int, int, int, SpaceShip*, ArtAsset*, ArtAsset*, ResourceManager*);
    /* Constructor.
       Postcondition: Defender Class NPC created according to its art assets
                      passed in and constructor of NPC;
                      baseX = first arg;
                      baseY = second arg.
       */
    virtual ~NPCDefender();
    virtual void update(SDL_Event, std::vector<GameObject*>&);
    virtual void draw(SDL_Surface*, Radar*);
    NPCState getState();
};

#endif