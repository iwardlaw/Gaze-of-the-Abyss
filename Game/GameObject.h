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
   GameObject.h -- Header file defining 'GameObject', which is an abstract
   class used to provide the central members and methods used by its children.
   Using this parent class allows the game engine to construct a vector of
   'GameObject' pointers and assign those pointers to instances of descendent
   classes.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   'string' and 'int' passed into loadImage(). 2 'int's, 2 'SDL_Surface'
   pointers, and an 'SDL_Rect' pointer passed into applySurface(). Four 'float'
   references each to convertRectToPolar() and convertPolarToRect(). Two
   'SDL_Surface' pointers, an 'SDL_Rect' pointer, and an 'int' passed to the
   constructor. 'SDL_Event' passed to update(). 'SDL_Surface' pointer and
   'Radar' pointer passed to draw(). 'float's for setPositionX() and
   setPositionY(). 'int' passed to setSpriteID().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   'SDL_Surface' pointer returned from loadImage(). 'float's and 'int's
   returned as appropriate from the getter methods. Effectively outputs changes
   to third and fourth agruments in convertRectToPolar() and
   convertPolarToRect(), though this ability is not used.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include"ArtAsset.h"
#include"enums.h"
#include"Radar.h"
#include"SDL.h"
#include"SDL_image.h"
#include<string>
#include<vector>

class ResourceManager;

class GameObject {
  protected:
    //Game State
    float absoluteAngle;
    float relativeX, relativeY;
    float positionX, positionY;
    float velocityX, velocityY;
    float thrustX, thrustY;
    float newPosX, newPosY, newVelX, newVelY;
    float initPosX, initPosY, initVelX, initVelY;
    float prevPosX, prevPosY, prevVelX, prevVelY;
    float mass;
    bool removed;

    //Object Attributes
    int health, maxHealth;
    int damageCaused;
    bool damageable;
    bool colliding;
    Alignment alignment;
    Material material;
    std::string objectType;

    //Intermediate (Engine/Art interface)
    int spriteID;
    int spriteHeight;
    int spriteWidth;
    int rSpriteID;

    //Art Assets
    SDL_Surface *sheet;   //source of object's art
    SDL_Surface *radarImage;
    int numSprites;
    SDL_Rect *sprites;
    ArtAsset *artAsset;
    ArtAsset *radarAsset;

    ResourceManager *manager;

    float boundingRadius;
    bool fastObject;
    bool collided;

    //Helper Functions
    float getGrav(GameObject*);

    void checkCollisions(float deltaT, std::vector<GameObject*> &objects);

    void adjustPosition();

    std::string collisionSound(GameObject*);

  public:
    GameObject(ArtAsset*, ArtAsset*, ResourceManager*);
    /* Constructor. Sets sprite sheet, sprite array, number of sprites, and
         radar image for the object based on the args; defaults absolute and
         relative positions and sprite ID to 0 and absolute angle to PI/2
         (north).
       Postcondition: Object intialized to center of game space, facing north.
       */
    virtual ~GameObject();
    /* Destructor.
       */
    virtual void update(SDL_Event, std::vector<GameObject*>&);
    /* Updates attributes of object's internal state, like absolute position.
       Postcondition: Object's internal state updated.
       */
    virtual void draw(SDL_Surface*, Radar*) = 0;
    /* NOTE: THIS IS AN ABSTRACT METHOD.
       Draws object's sprite to the game window.
       Postcondition: Object's sprite is blit to the game window with respect
                      to player position and angle as well as own state; its
                      radar image is blit to the radar per the same guidelines.
       */
    void findNewPosition(float deltaT, float posX, float posY, float velX, float velY, /*float &newPosX, float &newPosY, float &newVelX, float &newVelY,*/ std::vector<GameObject*> &objects);

    void getLambda(GameObject* obj, float &lambdaX, float &lambdaY, float &damageMultiplier);

    void prepareStateInfo();

    void storeStateInfo();

    void remove();

    bool dead();

    bool fast();

    bool collides();

    void heal(int hp);

    virtual void damage(int dmg);

    float getPositionX();
    /* Getter for 'positionX'.
       Postcondition: Returns 'positionX'.
       */
    float getPositionY();
    /* Getter for 'positionY'.
       Postcondition: Returns 'positionY'.
       */
    float getAbsoluteAngle();
    /* Getter for 'absoluteAngle'.
       Postcondition: Returns 'absoluteAngle'.
       */
    float getRelativeX();
    /* Getter for 'relativeX'.
       Postcondition: Returns 'relativeX'.
       */
    float getRelativeY();
    /* Getter for 'relativeY'.
       Postcondition: Returns 'relativeY'.
       */
    float getVelocityX();
    /* Getter for 'velocityX'.
       Postcondition: Returns 'velocityX'.
       */
    float getVelocityY();
    /* Getter for 'velocityY'.
       Postcondition: Returns 'velocityY'.
       */
    float getVelocity();
    /* Getter for total velocity.
       Postcondition: Returns magnitude of velocity vector.
       */
    float getMass();
    /* Getter for 'mass'.
       Postcondition: Returns 'mass'.
       */
    int getSpriteID();
    /* Getter for 'spriteID'.
       Postcondition: Returns 'spriteID'.
       */
    int getSpriteHeight();
    /* Getter for sprite height.
       Postcondition: Returns 'artAsset->height'.
       */
    int getSpriteWidth();
    /* Getter for sprite width.
       Postcondition: Returns 'artAsset->width'.
       */
    int getNumSprites();
    /* Getter for 'numSprites'.
       Postcondition: Returns 'numSprites'.
       */
    int getRadarWidth();
    /* Getter for radar sprite width.
       Postcondition: Returns 'radarAsset->width'.
       */
    int getRadarHeight();
    /* Getter for radar sprite height.
       Postcondition: Returns 'radarAsset->height'.
       */
    float getBoundingRadius();
    /* Getter for 'boundingRadius'.
       Postcondition: Returns 'boundingRadius'.
       */
    float getInitPosX();
    /* Getter for 'initPosX'.
       Postcondition: Returns 'initPosX'.
       */
    float getInitPosY();
    /* Getter for 'initPosY'.
       Postcondition: Returns 'initPosY'.
       */
    float getNewPosX();
    /* Getter for 'newPosX'.
       Postcondition: Returns 'newPosX'.
       */
    float getNewPosY();
    /* Getter for 'newPosY'.
       Postcondition: Returns 'newPosY'.
       */
    float getInitVelX();
    /* Getter for 'initVelX'.
       Postcondition: Returns 'initVelX'.
       */
    float getInitVelY();
    /* Getter for 'initVelY'.
       Postcondition: Returns 'initVelY'.
       */
    float getNewVelX();
    /* Getter for 'newVelX'.
       Poscondition: Returns 'newVelX'.
       */
    float getNewVelY();
    /* Getter for 'newVelY'.
       Postcondition: Returns 'newVelY'.
       */
    int getHealth();
    /* Getter for 'health'.
       Postcondition: Returns 'health'.
       */
    int getMaxHealth();
    /* Getter for 'maxHealth'.
       Postcondition: Returns 'maxHealth'.
       */
    int getDamageCaused();
    /* Getter for 'damageCaused'.
       Postcondition: Returns 'damageCaused'.
       */
    Alignment getAlignment();
    /* Getter for 'alignment'.
       Postcondition: Returns 'alignment'.
       */
    std::string getObjectType();
    /* Getter for 'objectType'.
       Postcondition: Returns 'objectType'.
       */
    Material getMaterial();
    /* Getter for 'material'.
       Postcondition: Returns 'material'.
       */
    void setPositionX(float);
    /* Setter for 'positionX'.
       Precondition: Arg must be castable to 'float'.
       Postcondition: 'float' value of arg assigned to 'positionX'.
       */
    void setPositionY(float);
    /* Setter for 'positionY'.
       Precondition: Arg must be castable to 'float'.
       Postcondition: 'float' value of arg assigned to 'positionY'.
       */
    void setVelocityX(float);
    /* Setter for 'velocityX'.
       Precondition: Arg must be castable to 'float'.
       Postcondition: 'float' value of arg assigned to 'velocityX'.
       */
    void setVelocityY(float);
    /* Setter for 'velocityY'.
       Precondition: Arg must be castable to 'float'.
       Postcondition: 'float' value of arg assigned to 'velocityY'.
       */
    void setSpriteID(int);
    /* Setter for 'spriteID'.
       Precondition: Arg must be castable to 'int'.
       Postcondition: 'int' value of arg assigned to 'spriteID'.
       */
    void setNewVelX(float);
    /* Setter for 'newVelX'.
       Precondition: Arg must be castable to 'float'.
       Postcondition: 'float' value of arg assigned to 'newVelX'.
       */
    void setNewVelY(float);
    /* Setter for 'newVelY'.
       Precondition: Arg must be castable to 'float'.
       Postcondition: 'float' value of arg assigned to 'newVelY'.
       */
};

#endif