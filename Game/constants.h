/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ========================
   File Description:
   constants.h -- Header file containing constant values used in the game.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   I'm not sure if all of these strings is what the assignment called for. I've
   tried to keep them intuitive, using names as identical as possible to the
   names value names in the configuration files.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   ========================
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include"enums.h"
#include<string>

const float PLAYER_SCREEN_X_RATIO = 0.5;
const float PLAYER_SCREEN_Y_RATIO = 0.75;
const float PI = 3.141592654;
const float PLAYER_THRUST = 0.5;
const float DEF_THRUST = 0.5;
const float MIN_NPC_THRUST = 0.1;
const float MAX_NPC_THRUST = 0.3;
const int MIN_NPC_THRUST_DURATION = 2;
const int MAX_NPC_THRUST_DURATION = 4;
const int MIN_NPC_COAST_DURATION = 30;
const int MAX_NPC_COAST_DURATION = 100;
const int DEF_ATTACK_MEMORY = 66;
const int PLAYER_INIT_SHOOT_DELAY = 10;
const int BULLET_START_LIFE = 50;
const int MISSILE_START_LIFE = 100;
const int START_MISSILES = 3;
const int DEFAULT_MAX_MISSILES = 3;
const int FREQUENCY = 44100;
const int AUDIO_CHANNELS = 2;
const int CHUNK_SIZE = 1024;
const int MAX_CHANNELS = 512;
const int MIN_HEALTH_SM = 25;
const int MAX_HEALTH_SM = 50;
const int MIN_HEALTH_MD = 50;
const int MAX_HEALTH_MD = 100;
const int MIN_HEALTH_LG = 100;
const int MAX_HEALTH_LG = 200;
const int ARMOR_DROP_VAL = 20;
const int COLLECTIBLE_FLASH_IDLE = 60;
const int COLLECTIBLE_FLASH_DELAY = 3;
const int COLLECTIBLE_R_FLASH_IDLE = 30;
const int COLLECTIBLE_R_FLASH_DELAY = 15;
const int HEALTH_FLASH_DELAY = 7;
const int HEALTH_R_FLASH_IDLE = 35;
const int HEALTH_R_FLASH_DELAY = 7;
const int EXPLOSION_LATENCY = 3;
const int MAX_FULL_VOL_EXPLOSIONS = 3;
const int EXPLOSION_SOUND_DURATION = 33;
const int MENU_OFFSET_X = 100;
const int MENU_OFFSET_Y = 100;
const int MAX_ARMOR = 100;
const int START_LIVES = 3;
const int DEFAULT_MAX_LIVES = 100;
const int MIN_BOSS_MISSILE_DELAY = 66;
const int MAX_BOSS_MISSILE_DELAY = 330;
//const int MISSION_MSG_FONT_SIZE = 18;
const int OBJECTIVE_MSG_DELAY = 165;
const int LIVES_INDICATOR_DELAY = 205;
const float BULLET_VEL = 10.0;
const float MISSILE_VEL = 5.0;
const float MISSILE_THRUST = 20.0;
const int MISSILE_THRUST_DURATION = 100;
const int MISSILE_COAST_DURATION = 0;
const float MAX_PLAYER_VEL = 40.0;
const float MAX_NPC_VEL = 30.0;
const float MAX_BULLET_VEL = MAX_PLAYER_VEL + BULLET_VEL;
const float MAX_MISSILE_VEL = MAX_PLAYER_VEL + 10.0;
const float MAX_AST_VEL = 30.0;
const float G = 9.8;
const float EPSILON = 1.0;
const float DAMAGE_DIVIDEND = 10.0;
const float MAX_SOUND_DIST = 2500.0;
const float COLLECTIBLE_GRAB_DIST = 1500.0;
const float COLLECTIBLE_GRAB_VEL = 3.0;
const int MAX_AST_SPIN_DELAY = 5;
const DifficultyLevel DEFAULT_DIFFICULTY = MEDIUM;
const char COMMENT_CHAR = '#';
const char DELIMITER_CHAR = ',';
const std::string RADAREXT = "_RADAR";
const std::string CONFIG_PATH_FILE = "./config/pathConfig.txt";
const std::string SCREEN = "SCREEN";
const std::string RADAR = "RADAR";
const std::string HEALTHBAR = "HEALTHBAR";
const std::string TELEMETRY = "TELEMETRY";
const std::string LIVESINDICATOR = "LIVESINDICATOR";
const std::string LEVELPATH = "LEVELPATH";
const std::string LEVELEXT = "LEVELEXT";
const std::string SFX = "SFX";
const std::string GROUPINGS = "GROUPINGS";
const std::string SS = "SS";
const std::string _NPC = "NPC";
const std::string AST = "AST";
const std::string DEF = "DEF";
const std::string ATK = "ATK";
const std::string BOSS = "BOSS";
const std::string BULLET = "BULLET";
const std::string REDBULLET = "REDBULLET";
const std::string SCANBULLET = "SCANBULLET";
const std::string MISSILE = "MISSILE";
const std::string HEALTH = "HEALTH";
const std::string HEALTH_SM = "HEALTH_SM";
const std::string HEALTH_MD = "HEALTH_MD";
const std::string HEALTH_LG = "HEALTH_LG";
const std::string HEALTH_FL = "HEALTH_FL";
const std::string ARMOR = "ARMOR";
const std::string ITEM = "ITEM";
const std::string EXPLOSION = "EXPLOSION";
const std::string GAMEOVER = "GAMEOVER";
const std::string BLANK = "BLANK";
const std::string WIDTH = "WIDTH";
const std::string HEIGHT = "HEIGHT";
const std::string BPP = "BPP";
const std::string FRAMEDELAY = "FRAMEDELAY";
const std::string NAME = "NAME";
const std::string RFILLKEY = "RFILLKEY";
const std::string GFILLKEY = "GFILLKEY";
const std::string BFILLKEY = "BFILLKEY";
const std::string SETMASTERHUDOPACITY = "SETMASTERHUDOPACITY";
const std::string TRUE = "TRUE";
const std::string FALSE = "FALSE";
const std::string MASTERHUDOPACITY = "MASTERHUDOPACITY";
const std::string OPACITY = "OPACITY";
const std::string BDRTHICKNESS = "BDRTHICKNESS";
const std::string BDRR = "BDRR";
const std::string BDRG = "BDRG";
const std::string BDRB = "BDRB";
const std::string SCALE = "SCALE";
const std::string OFFSETX = "OFFSETX";
const std::string OFFSETY = "OFFSETY";
const std::string FONTPATH = "FONTPATH";
const std::string FONTSIZE = "FONTSIZE";
const std::string FONTR = "FONTR";
const std::string FONTG = "FONTG";
const std::string FONTB = "FONTB";
const std::string FONTOFFSETX = "FONTOFFSETX";
const std::string FONTOFFSETY = "FONTOFFSETY";
const std::string FONTLNDIFF = "FONTLNDIFF";
const std::string IMAGEPATH = "IMAGEPATH";
const std::string NUMSPRITES = "NUMSPRITES";
const std::string NROWS = "NROWS";
const std::string NCOLS = "NCOLS";
const std::string RMAPKEY = "RMAPKEY";
const std::string GMAPKEY = "GMAPKEY";
const std::string BMAPKEY = "BMAPKEY";
const std::string FULLR = "FULLR";
const std::string FULLG = "FULLG";
const std::string FULLB = "FULLB";
const std::string EMPTYR = "EMPTYR";
const std::string EMPTYG = "EMPTYG";
const std::string EMPTYB = "EMPTYB";
const std::string ARMORR = "ARMORR";
const std::string ARMORG = "ARMORG";
const std::string ARMORB = "ARMORB";
const std::string BGOPACITY = "BGOPACITY";
const std::string ICONPATH = "ICONPATH";
const std::string ICONEXT = "_ICON";
const std::string RADARRESOURCEPATH = "RADARRESOURCEPATH";
const std::string RADARIMAGEPATH = "RADARIMAGEPATH";
const std::string RADARWIDTH = "RADARWIDTH";
const std::string RADARHEIGHT = "RADARHEIGHT";
const std::string RADARRMAPKEY = "RADARRMAPKEY";
const std::string RADARGMAPKEY = "RADARGMAPKEY";
const std::string RADARBMAPKEY = "RADARBMAPKEY";
const std::string VELOCITY_MSG = "Vel: ";
const std::string DIRECTION_MSG = "Dir: ";
const std::string POSITION_MSG = "Pos: ";
const std::string COLLISION_MSG = "Collision: ";
const std::string GRAVITY_MSG = "Gravity: ";
const std::string HEALTH_MSG = "Health: ";
const std::string DAMAGE_MSG = "Damage: ";
const std::string LIVES_MSG = "Lives: ";
const std::string FF_MSG = "Friendly Fire: ";
const std::string DIFF_MSG = "Difficulty: ";
const std::string ON = "ON";
const std::string OFF = "OFF";
const std::string EASY_MSG = "EASY";
const std::string MEDIUM_MSG = "MEDIUM";
const std::string HARD_MSG = "HARD";
const std::string EXTREME_MSG = "EXTREME";
const std::string LEVEL = "LEVEL";
const std::string BGM = "BGM";
const std::string INTROEXT = "_INTRO";
const std::string LOOPEXT = "_LOOP";
const std::string COL_METAL_METAL = "COL_METAL_METAL";
const std::string COL_METAL_ROCK = "COL_METAL_ROCK";
const std::string COL_ROCK_ROCK = "COL_ROCK_ROCK";
const std::string COL_PROJECTILE = "COL_PROJECTILE";
const std::string SHOOT = "SHOOT";
const std::string FIRE_MISSILE = "FIRE_MISSILE";
const std::string HEAL = "HEAL";
const std::string ENARMOR = "ENARMOR";
const std::string EXPLODE = "EXPLODE";
const std::string NEG_HEALTH_VAL = "--";
const std::string SCAN = "SCAN";
const std::string SCANSHOOT = "SCANSHOOT";
const std::string COLLECT = "COLLECT";
const std::string TELEPORT = "TELEPORT";
const std::string CLEAR_LEVEL = "CLEAR_LEVEL";
const std::string VICTORY = "VICTORY";
const std::string PAUSE = "PAUSE";
const std::string UNPAUSE = "UNPAUSE";
const std::string OBJECTIVE = "OBJECTIVE";
const std::string KILL = "KILL";
const std::string CLEAR = "CLEAR";
const std::string ALL = "ALL";
const std::string BGMVOLUMEPERCENT = "BGMVOLUMEPERCENT";
const std::string ROOTMENUPATH = "ROOTMENUPATH";
const std::string ITEMDIRECTORY = "ITEMDIRECTORY";
const std::string MENUTITLESIZE = "MENUTITLESIZE";
const std::string MENUTITLEOPACITY = "MENUTITLEOPACITY";
const std::string MENUTITLER = "MENUTITLER";
const std::string MENUTITLEG = "MENUTITLEG";
const std::string MENUTITLEB = "MENUTITLEB";
const std::string MENUITEMSIZE = "MENUITEMSIZE";
const std::string MENUITEMOPACITY = "MENUITEMOPACITY";
const std::string MENUITEMR_NORMAL = "MENUITEMR_NORMAL";
const std::string MENUITEMG_NORMAL = "MENUITEMG_NORMAL";
const std::string MENUITEMB_NORMAL = "MENUITEMB_NORMAL";
const std::string MENUITEMR_HOVER = "MENUITEMR_HOVER";
const std::string MENUITEMG_HOVER = "MENUITEMG_HOVER";
const std::string MENUITEMB_HOVER = "MENUITEMB_HOVER";
const std::string MENUITEMR_SELECT = "MENUITEMR_SELECT";
const std::string MENUITEMG_SELECT = "MENUITEMG_SELECT";
const std::string MENUITEMB_SELECT = "MENUITEMB_SELECT";
const std::string MENUITEMR_UNAVAIL = "MENUITEMR_UNAVAIL";
const std::string MENUITEMG_UNAVAIL = "MENUITEMG_UNAVAIL";
const std::string MENUITEMB_UNAVAIL = "MENUITEMB_UNAVAIL";
const std::string MENUOFFSETX = "MENUOFFSETX";
const std::string MENUOFFSETY = "MENUOFFSETY";
const std::string MENUWIDTH = "MENUWIDTH";
const std::string MENUHEIGHT = "MENUHEIGHT";
const std::string IMAGEOFFSETX = "IMAGEOFFSETX";
const std::string IMAGEOFFSETY = "IMAGEOFFSETY";
const std::string IMAGEWIDTH = "IMAGEWIDTH";
const std::string IMAGEHEIGHT = "IMAGEHEIGHT";
const std::string TEXTOFFSETX = "TEXTOFFSETX";
const std::string TEXTOFFSETY = "TEXTOFFSETY";
const std::string TEXTWIDTH = "TEXTWIDTH";
const std::string TEXTHEIGHT = "TEXTHEIGHT";
const std::string TITLE = "TITLE";
const std::string SHOWTITLE = "SHOWTITLE";
const std::string PARENT = "PARENT";
const std::string ITEMPATHS = "ITEMPATHS";
const std::string TEXTPATH = "TEXTPATH";
const std::string DESTINATIONPATH = "DESTINATIONPATH";
const std::string CONFIG_NULL = "NULL";
const std::string OBJECTIVE_CLEAR_MSG = "Clear the map!";
const std::string OBJECTIVE_KILL_MSG = "Destroy your foes!";
const std::string OBJECTIVE_COLLECT_MSG = "Collect all of the items!";
const std::string OBJECTIVE_BOSS_MSG = "Good luck!";
const std::string GAMEOVER_MSG = "Game Over";
const std::string RESTART_MSG = "[ shoot to restart ]";
const std::string PAUSE_MSG = "Pause";

#endif