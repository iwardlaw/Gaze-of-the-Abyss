/*
   Isaac Wardlaw
   T00522482
   CPSC 4370
   Project
   13 May 2013
   ~~~~~~~~~~~~~~~~~~~~~~~~
   File and portions of program by Keith Bush, PhD
   26 Jan 2012
   ========================
   Program Description:
   This homework focuses mostly on physics. It's tough.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   File Description:
   Main.cpp -- Main implementation file. Merely randomizes the random number
   seed that will be used and creates an instance of the 'GameEngine' class.
   The constructor of this class delegates all of the real work that this
   program does.
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Inputs:
   Standard 'int argc' and 'char *argv[]' passed into main().
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Outputs:
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Assumptions:
   I've assumed that it's okay to leave a few hard-coded values in the code
   where needed to make some basic calculations, say the doubles and halves of
   certain quantities (such as 2 * PI).
   ~~~~~~~~~~~~~~~~~~~~~~~~
   Special Processing Requirements:
   For the program in general to work, several DLL files must be included
   within the directory containing this file; these were provided as part of
   the assignment download and should always exist in said directory. Also,
   there are a few configuration files, image files, and font files, which must
   be kept in "./config/", "./images/", and "./fonts/", respectively.
   ========================
*/

#include"GameEngine.h"
#include"Explosion.h"
#include <cstdlib>
#include <ctime>
using namespace std;

// Static Members
unsigned Explosion::soundingCount;

int main(int argc, char *argv[])
{
  // Initialize static memebers
  Explosion::initSoundingCount();

  // Seed random number generator
  srand((unsigned)time(0));

  // Construct Engine
  GameEngine engine;

  return 0;
}