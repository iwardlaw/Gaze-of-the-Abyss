/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   NPC.h -- Header file defining the 'NPC' class, which represents nonplayer
   ships. Child of 'ExternalObject'.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Four 'int's, two 'SDL_Surface' pointers, and an 'SDL_Rect' pointer passed to
   the constructor; 'SDL_Event' passed to update().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#ifndef NPC_H
#define NPC_H

#include"ExternalObject.h"
#include"SpaceShip.h"
#include<string>

class NPC : public ExternalObject {
  protected:
    float thrust;
    int thrustCounter, thrustDuration, coastCounter, coastDuration;
  public:
    NPC(int, int, int, SpaceShip*, ArtAsset*, ArtAsset*, ResourceManager*);
    /* Constructor. Does nothing but pass args to constructor of
         'ExternalObject'. Penultimate 4 args are art assets.
       Postcondition: NPC created according to its art assets passed in and
                      constructor of ExternalObject.
       */
    virtual ~NPC();
    /* Destructor. Does nothing.
       */
    virtual void update(SDL_Event, std::vector<GameObject*>&);
    /* Updates NPC's state based on arg.
       Postcondition: NPC flies forward indefinitely at a constant velocity.
       */
};

#endif