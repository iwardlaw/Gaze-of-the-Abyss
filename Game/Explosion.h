/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include"ExternalObject.h"

class Explosion : public ExternalObject {
  private:
    static unsigned soundingCount;
  protected:
    int counter;
    int soundCounter;
  public:
    static void initSoundingCount();
    Explosion(int, int, SpaceShip*, ArtAsset*, ResourceManager*);
    ~Explosion();
    void incrCount();
    void decrCount();
    virtual void draw(SDL_Surface *screen, Radar *radar);
    virtual void update(SDL_Event, std::vector<GameObject*>&);
};

#endif