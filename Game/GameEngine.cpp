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
   GameEngine.cpp -- Implementation file for the 'GameEngine' class.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Two 'int's, two 'SDL_Surface' pointers, and an 'SDL_Rect' pointer passed to
   applySurface(). SDL event queue is processed in run().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#include"GameEngine.h"
#include"Bullet.h"
#include"constants.h"
#include"Asteroid.h"
#include"ExternalObject.h"
#include"Factory.h"
#include"GameObject.h"
#include"globals.h"
#include"NPC.h"
#include"Timer.h"
#include"utilities.h"
#include"SDL.h"
#include"SDL_mixer.h"
#include<cstddef>
#include<iterator>
#include<fstream>
#include<iostream>
#include<iomanip>

#define START_LVL 1

GameEngine::GameEngine()
{
  playing = true;
  gameOver = false;

  collisionOn = true;
  damageOn = true;
  defenderRadiiVisible = false;
  friendlyFireOn = false;
  gravityOn = false;
  inertiaOn = true;
  rapidFireOn = false;
  rk4On = false;

  difficulty = DEFAULT_DIFFICULTY;

  keys[SDLK_UP] = keys[SDLK_DOWN] = keys[SDLK_LEFT] = keys[SDLK_RIGHT] =
    keys[SDLK_SPACE] = keys[SDLK_b] = keys[SDLK_RCTRL] = keys[SDLK_e] = false;

  screenWidth = resourceManager.getInventoryInt(SCREEN, WIDTH);
  screenHeight = resourceManager.getInventoryInt(SCREEN, HEIGHT);
  screenBPP = resourceManager.getInventoryInt(SCREEN, BPP);
  frameDelay = resourceManager.getInventoryInt(SCREEN, FRAMEDELAY);
  windowTitle = resourceManager.getInventoryStr(SCREEN, NAME);
  screen = resourceManager.getScreen();
  telemetry = new Telemetry(resourceManager.getTelemetrySurface(),
                    resourceManager.getInventoryMap(TELEMETRY),
                    resourceManager.getInventoryInt(SCREEN, WIDTH),
                    resourceManager.getInventoryInt(SCREEN, HEIGHT));
  radar = new Radar(resourceManager.getRadarSurface(),
                resourceManager.getInventoryMap(RADAR),
                resourceManager.getInventoryInt(SCREEN, WIDTH),
                resourceManager.getInventoryInt(SCREEN, HEIGHT));
  healthbar = new Healthbar(resourceManager.getHealthbarSurface(),
    resourceManager.getInventoryMap(HEALTHBAR),
    resourceManager.getInventoryInt(SCREEN, WIDTH),
    resourceManager.getInventoryInt(SCREEN, HEIGHT));

  createPlayer();
  
  //player = new SpaceShip(screen->w, screen->h, radar, resourceManager.getArtAsset(SS),
  //  resourceManager.getArtAsset(SS + RADAREXT), &resourceManager);

  font = TTF_OpenFont("./fonts/impact.ttf", 60);
  smallFont = TTF_OpenFont("./fonts/impact.ttf", 30);
  textColor.r = 255;
  textColor.g = 255;
  textColor.b = 255;

  gameOverMsg = TTF_RenderText_Solid(font, GAMEOVER_MSG.c_str(), textColor);
  restartMsg = TTF_RenderText_Solid(smallFont, RESTART_MSG.c_str(), textColor);
  gameOverOffset.x = (screen->w - gameOverMsg->w) / 2;
  gameOverOffset.y = (screen->h - (gameOverMsg->h + restartMsg->h)) / 2;  
  restartOffset.x = (screen->w - restartMsg->w) / 2;
  restartOffset.y = gameOverOffset.y + gameOverMsg->h;

  pauseMsg = TTF_RenderText_Solid(font, PAUSE_MSG.c_str(), textColor);
  pauseMsgOffset.x = (screen->w - pauseMsg->w) / 2;
  pauseMsgOffset.y = (screen->h - pauseMsg->h) / 2;

  bulletLife = BULLET_START_LIFE;

  objects.push_back(player);
  
  nextLevel = START_LVL;

  while(playing) {
    level = nextLevel;
    //if(gameOver) {
    //  //createPlayer();
    //  //objects.push_back(player);
    //}
    resourceManager.buildLevel(level, player, objects);
    resolveOverlap();
    run();
    resourceManager.clearLevel(player, objects);
  }
}

GameEngine::~GameEngine()
{
  for(oiter=objects.begin();oiter!=objects.end();oiter++)
    delete (*oiter);
  delete radar;
  delete telemetry;
  screen =  NULL;

  SDL_FreeSurface(gameOverMsg);
  SDL_FreeSurface(restartMsg);
  SDL_FreeSurface(pauseMsg);
  TTF_CloseFont(font);
  TTF_CloseFont(smallFont);

  if(Mix_PlayingMusic()) Mix_HaltMusic();
}

void GameEngine::createPlayer()
{
  player = new SpaceShip(screen->w, screen->h, radar, resourceManager.getArtAsset(SS),
    resourceManager.getArtAsset(SS + RADAREXT), &resourceManager);
}

void GameEngine::resolveOverlap()
{
  std::vector<GameObject*>::iterator oiter2;
  float dist, sumOfRadii, maxRadius;
  bool overlap;
  int dir;

  do {
    overlap = false;
    for(oiter=objects.begin()+1; oiter!=objects.end(); ++oiter)
      if((*oiter)->collides())
        for(oiter2=objects.begin(); oiter2!=objects.end(); ++oiter2)
          if(*oiter != *oiter2 && (*oiter2)->collides()) {
            dist = getDist((*oiter)->getPositionX(), (*oiter)->getPositionY(),
              (*oiter2)->getPositionX(), (*oiter2)->getPositionY());
            sumOfRadii = (*oiter)->getBoundingRadius() +
              (*oiter2)->getBoundingRadius();
            maxRadius = std::max((*oiter)->getBoundingRadius(),
              (*oiter2)->getBoundingRadius());
            if(dist < sumOfRadii) {
              dir = rand() % 2;
              if(dir == 0) dir = -1;
              (*oiter)->setPositionX((*oiter)->getPositionX() + dir * 2 * maxRadius + 0);

              dir = rand() % 2;
              if(dir == 0) dir = -1;
              (*oiter)->setPositionY((*oiter)->getPositionY() + dir * 2 * maxRadius + 0);

              overlap = true;
            }
          }
  } while(overlap);
}

void GameEngine::run()
{
  //bool quit = false;
  bool changeLevel = false;
  std::ostringstream levelSS;

  levelSS << LEVEL << level;
  levelName = levelSS.str();
  bossLevel = resourceManager.checkBossLevel();
  musicIntro = true;
  levelClear = gameOver = false;
  int musicVolume; /* Used for makeshift mute functionality. */

  objectiveCounter = livesIndicatorCounter = 0;

  initObjectiveMsg();
  //initLivesIndicator();

  Mix_PlayMusic(resourceManager.getSong(BLANK), 0);

  //while(quit == false) {
  while(playing && !changeLevel) {

    //Start the frame timer
    fps.start();

    if(!Mix_PlayingMusic() && !(bossLevel && levelClear))
      if(musicIntro && Mix_PlayMusic(resourceManager.getSong(levelName +
         INTROEXT), 0) != -1)
        musicIntro = false;
      else
        Mix_PlayMusic(resourceManager.getSong(levelName + LOOPEXT), -1);

    inBattle = false;

    if(player->dead() && !gameOver) {
      Mix_HaltMusic();
      Mix_PlayMusic(resourceManager.getSong(GAMEOVER), -1);
      gameOver = true;
    }
    else // if(!player->dead())
      while(SDL_PollEvent(&event)) {
        if(event.type == SDL_KEYDOWN) {
          keys[event.key.keysym.sym] = true;
          switch(event.key.keysym.sym) {
            case SDLK_c: collisionOn = !collisionOn; break;
            case SDLK_d: damageOn = !damageOn; break;
            case SDLK_f: friendlyFireOn = !friendlyFireOn; break;
            case SDLK_g: gravityOn = !gravityOn; break;
            case SDLK_i: inertiaOn = !inertiaOn; break;
            case SDLK_k: rk4On = !rk4On; break;
            case SDLK_r: radar->toggle(); break;
            case SDLK_t: telemetry->toggle(); break;
            case SDLK_1: defenderRadiiVisible = !defenderRadiiVisible; break;
            case SDLK_2: healthbar->toggle(); break;
            case SDLK_3: rapidFireOn = !rapidFireOn; break;
            case SDLK_4: destroyEnemies(); break;
            case SDLK_5: clearLevel(COLLECT); break;
            case SDLK_6: clearLevel(CLEAR); break;
            case SDLK_SPACE:
              if(gameOver)
                changeLevel = true;
              else if(!rapidFireOn)
                resourceManager.makeBullet(BULLET, player, player, objects, bulletLife);
              break;
            case SDLK_s:
              resourceManager.makeBullet(SCANBULLET, player, player, objects, bulletLife);
              break;
            case SDLK_v:
              if(!gameOver && player->getNumMissiles() > 0)
                resourceManager.makeMissile(player, NULL, player, objects, MISSILE_START_LIFE);
              break;
            case SDLK_h:
              switch(difficulty) {
                case EASY: difficulty = MEDIUM; break;
                case MEDIUM: difficulty = HARD; break;
                case HARD: difficulty = EXTREME; break;
                case EXTREME: difficulty = EASY; break;
                default: difficulty = DEFAULT_DIFFICULTY;
              }
              break;
            case SDLK_m: /* Used for makeshift mute functionality. */
              if(Mix_VolumeMusic(-1) != 0) {
                musicVolume = Mix_VolumeMusic(-1);
                Mix_VolumeMusic(0);
              }
              else
                Mix_VolumeMusic(musicVolume);
              break;
            case SDLK_a: if(!gameOver) pause(); break;
            case SDLK_LSHIFT: if(levelClear) changeLevel = true; break;
            case SDLK_ESCAPE:
              //quit = true;
              playing = false;
              break;
            case SDLK_BACKQUOTE:
              player->remove();
              break;
          }
        }
        if(event.type == SDL_KEYUP)
          keys[event.key.keysym.sym] = false;

        if(event.type == SDL_QUIT) {
          //quit = true; 
          playing = false;
        }
      }

    changeGameState();

    deleteDeadObjects();

    //Render the game state
    displayGameState();

    if(!levelClear && (difficulty < HARD || !inBattle)) {
      levelClear = resourceManager.checkObjectives();
      if(levelClear)
        if(!bossLevel)
          resourceManager.playSound(CLEAR_LEVEL, 0.0, 1000, 1000);
        else {
          Mix_HaltMusic();
          resourceManager.playSound(VICTORY, 0.0, 1000, 1000);
          destroyEnemies();
        }
    }

    if(objectiveCounter < OBJECTIVE_MSG_DELAY)
      ++objectiveCounter;

    if(livesIndicatorCounter < LIVES_INDICATOR_DELAY)
      ++livesIndicatorCounter;

    //Frame rate equalizer
    if(fps.get_ticks() < frameDelay)
      SDL_Delay(frameDelay - fps.get_ticks());
  }

  if(playing && !gameOver) {
    resourceManager.playSound(TELEPORT);
    ++nextLevel;
  }

  SDL_FreeSurface(objectiveMsg);
  //SDL_FreeSurface(livesIndicator);
  Mix_FadeOutMusic(1000);
}

void GameEngine::displayGameState()
{
  //Fill screen black
  SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format,
    resourceManager.getInventoryInt(SCREEN, RFILLKEY),
    resourceManager.getInventoryInt(SCREEN, GFILLKEY),
    resourceManager.getInventoryInt(SCREEN, BFILLKEY)));

  if(radar->active())
    radar->drawRects();

  for(oiter=objects.begin(); oiter!=objects.end(); ++oiter)
    (*oiter)->draw(screen, radar);

  if(radar->active())
    SDL_BlitSurface(radar->getSurface(), NULL, screen, &(radar->getOffset()));

  if(telemetry->active())
    SDL_BlitSurface(telemetry->getSurface(), NULL, screen,
      &(telemetry->getOffset()));

  if(healthbar->active())
    SDL_BlitSurface(healthbar->getSurface(), NULL, screen,
      &(healthbar->getOffset()));

  if(player->dead()) {
    SDL_BlitSurface(gameOverMsg, NULL, screen, &gameOverOffset);
    SDL_BlitSurface(restartMsg, NULL, screen, &restartOffset);
  }
  else {
    if(objectiveCounter < OBJECTIVE_MSG_DELAY)
      SDL_BlitSurface(objectiveMsg, NULL, screen, &objectiveOffset);
    //if(livesIndicatorCounter < LIVES_INDICATOR_DELAY)
    //  SDL_BlitSurface(livesIndicator, NULL, screen, &livesIndicatorOffset);
  }

  //Render all blitted images
  SDL_Flip(screen);
}

void GameEngine::changeGameState()
{
  size_t initCapacity;
  int i, n = 0;
  std::string type;

  for(oiter=objects.begin(); oiter!=objects.end(); ++oiter)
    (*oiter)->prepareStateInfo();

  for(oiter=objects.begin(); oiter!=objects.end(); ++oiter) {
    initCapacity = objects.capacity();
    (*oiter)->update(event, objects);
    type = (*oiter)->getObjectType();
    if(type == "ATK" || type == "DEF" || type == "BOSS")
      if(((NPCDefender*)(*oiter))->getState() == ATTACK)
        inBattle = true;
    if(objects.capacity() > initCapacity) {
      oiter = objects.begin() /* - 1 */;    // <-- Check this if encountering out-of-bounds errors.
      for(i=0; i<n; ++i)
        ++oiter;
    }
    ++n;
  }

  if(telemetry->active())
    telemetry->update(event, player);

  if(healthbar->active())
    healthbar->update(player);

  for(oiter=objects.begin(); oiter!=objects.end(); ++oiter)
    (*oiter)->storeStateInfo();
}

void GameEngine::deleteDeadObjects()
{
  std::string objective = resourceManager.getLevelObjective();
  std::set<std::string> group;
  for(oiter=objects.begin(); oiter!=objects.end(); ++oiter)
    if((*oiter)->dead() && *oiter != player) {
      //std::string type = (*oiter)->getObjectType();
      group = resourceManager.getObjectGrouping(objective);
      //if(level == 1 && (type == AST || type == DEF || type == ATK))
      if(group.find((*oiter)->getObjectType()) != group.end()) {
        if(objective == CLEAR)
          resourceManager.countObject();
        if(objective == KILL)
          resourceManager.countEnemy();
        if(objective == COLLECT)
          resourceManager.collectItem();
      }
      delete *oiter;
      if(oiter!=objects.begin()) oiter-- = objects.erase(oiter);
      else oiter = objects.erase(oiter);
    }
}

void GameEngine::destroyEnemies()
{
  for(oiter=objects.begin(); oiter!=objects.end(); ++oiter)
    if((*oiter)->getAlignment() == ENEMY)
      (*oiter)->remove();
}

void GameEngine::clearLevel(std::string objective)
{
  std::set<std::string> group = resourceManager.getObjectGrouping(objective);
  for(oiter=objects.begin(); oiter!=objects.end(); ++oiter)
    if(group.find((*oiter)->getObjectType()) != group.end())
      (*oiter)->remove();
}

void GameEngine::initObjectiveMsg()
{
  std::string objective = resourceManager.getLevelObjective();
  if(objective == CLEAR) objective = OBJECTIVE_CLEAR_MSG;
  else if(objective == KILL) objective = OBJECTIVE_KILL_MSG;
  else if(objective == COLLECT) objective = OBJECTIVE_COLLECT_MSG;
  else if(objective == BOSS) objective = OBJECTIVE_BOSS_MSG;
  else objective = " ";
  objectiveMsg = TTF_RenderText_Solid(smallFont, objective.c_str(), textColor);

  objectiveOffset.x = (screen->w - objectiveMsg->w) / 2;
  objectiveOffset.y = (screen->h - objectiveMsg->h) / 4;
}

void GameEngine::initLivesIndicator()
{
  //SDL_Surface *msg;
  //std::ostringstream msgSS;
  //msgSS << " = " << player->getLives();
  //msg = TTF_RenderText_Solid(smallFont, msgSS.str().c_str(), textColor);

  //livesIndicator = resourceManager.getLivesIndicatorSurface();

  //int msgOffsetX = resourceManager.getInventoryInt(LIVESICON, WIDTH);
  //int iconHeight = resourceManager.getInventoryInt(LIVESICON, HEIGHT);
  //int msgOffsetY = std::abs(iconHeight - msg->h) / 2;
  //
  //applySurface(0, 0, resourceManager.getSpriteSheet(LIVESICON), livesIndicator, NULL);
  //applySurface(msgOffsetX, msgOffsetY, msg, livesIndicator, NULL);

  //SDL_FreeSurface(msg);

  //livesIndicatorOffset.x = screen->w * 0.8;
  //livesIndicatorOffset.y = 10;
}

void GameEngine::pause()
{
  int volume = Mix_VolumeMusic(-1);
  Mix_VolumeMusic(volume / 2);
  resourceManager.playSound(PAUSE);
  displayPauseScreen();
  Mix_VolumeMusic(volume);
}

void GameEngine::displayPauseScreen()
{
  bool paused = true;
  //int musicVolume;
  int width = screen->w;
  int height = screen->h;
  int bpp = resourceManager.getInventoryInt(SCREEN, BPP);
  Uint32 rMask = screen->format->Rmask;
  Uint32 gMask = screen->format->Gmask;
  Uint32 bMask = screen->format->Bmask;
  Uint32 aMask = screen->format->Amask;

  //std::cerr << "Before 'grayout' assignment." << std::endl;
  //SDL_Surface *grayout = new SDL_Surface;
  //std::cerr << '1' << std::endl;
  //SDL_FillRect(grayout, &grayout->clip_rect, SDL_MapRGB(grayout->format, 0, 0, 0));
  //std::cerr << '2' << std::endl;
  //SDL_SetAlpha(grayout, SDL_SRCALPHA, 128);
  //std::cerr << "After 'grayout' assignment." << std::endl;

  SDL_Surface *grayout;
  grayout = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, bpp, rMask, gMask, bMask, aMask);
  SDL_SetAlpha(grayout, SDL_SRCALPHA, 128);

  SDL_Rect grayoutOffset;
  grayoutOffset.x = 0;
  grayoutOffset.y = 0;

  SDL_BlitSurface(grayout, NULL, screen, &grayoutOffset);

  while(paused) {
    if(!Mix_PlayingMusic() && !(bossLevel && levelClear)) {
      if(musicIntro && Mix_PlayMusic(resourceManager.getSong(levelName +
         INTROEXT), 0) != -1)
        musicIntro = false;
      else
        Mix_PlayMusic(resourceManager.getSong(levelName + LOOPEXT), -1);
    }

    SDL_BlitSurface(pauseMsg, NULL, screen, &pauseMsgOffset);
    SDL_Flip(screen);

    while(SDL_PollEvent(&event))
      if(event.type == SDL_KEYDOWN)
        switch(event.key.keysym.sym) {
          case SDLK_a:
            paused = false;
            resourceManager.playSound(UNPAUSE);
            break;
          //case SDLK_m:
          //  if(Mix_VolumeMusic(-1) != 0) {
          //    musicVolume = Mix_VolumeMusic(-1);
          //    Mix_VolumeMusic(0);
          //  }
          //  else
          //    Mix_VolumeMusic(musicVolume);
          //  break;
          case SDLK_ESCAPE: paused = playing = false; break;
        }
      else if(event.type == SDL_QUIT)
        paused = playing = false;
  }

  SDL_FreeSurface(grayout);
}