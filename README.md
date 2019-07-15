# Gaze-of-the-Abyss

This is my Advanced Game Programming project from Spring 2013. Building it was one of the most challenging and rewarding experiences of my scholastic career and is, to this day, probably the single most enjoyable project I’ve worked on.

## Gameplay

_Gaze of the Abyss_ is an arcade-style space shooter in which you pilot a ship through a 2D, top-down open world.

### Controls
#### General
- **Up arrow:** forward thruster
- **Down arrow:** reverse thruster
- **Left arrow:** rotate left
- **Right arrow:** rotate right
- **Space:** shoot
- **A:** pause
- **B:** brake
- **E:** attract collectibles
- **M:** mute/unumte music
- **R:** toggle radar
- **2:** toggle healthbar
- **Left shift:** next level (after objective complete)

#### For Testing
- **C:** toggle collisions
- **D:** toggle damage
- **T:** toggle telemetry

#### Partially Developed
- **F:** toggle friendly fire (not implemented)
- **G:** toggle gravity (broken)
- **H:** toggle difficulty (preliminary)
- **S:** fire scanning bullet (preliminary)
- **V:** fire missile (preliminary)

### Objectives

Each level has one of the following objectives:
- Clear the map
- Destroy enemies
- Collect items
- Defeat a boss

I built the game to show these objectives in this order, so Level 1 is a Clear level, Level 2 is a Destory level, etc. There is also one final level without an objective if you win; you must quit the game to leave this level, as objectives are currently the only way to progress.

## How to Play

Download the repository and launch `GazeOfTheAbyss.exe` within the `Game` folder. The project is currently structured to rely on configuration files, assets, and DLLs at that level.

## Credits
### Sprites

Health/armor sprites – originals created by ZeroInfections at <http://charas-project.net/>; modified by Isaac Wardlaw

Item sprite – ripped from Illusion of Gaia by Meiscool at <http://charas-project.net/>

Explosion sprite – ripped from Golden Sun by Zirdec, recovered at <http://www.spriters-resource.com>

Boss sprite – created by dgbaumgart at <http://fractalsoftworks.com/2010/11/29/art-ship-design-the-onslaught/>; modified by Isaac Wardlaw

### Music

bgm0 – [_Appleseed_] "Bringing Home the Appleseed" by DigiE at <http://www.animeremix.org/>; modified by Isaac Wardlaw

bgm1 – [_Naruto_] "Alone" by Electric Concerto at <http://www.animeremix.org/>; modified by Isaac Wardlaw

bgm2 – [_Mario Paint_] "Intense Color" by sephire and SuperGreenX at <http://ocremix.org/>; modified by Isaac Wardlaw

bgm3 – [_Tetris_] "Thirty-Plus Mix" by R3FORGED at <http://ocremix.org/>; modified by Isaac Wardlaw

bgm4 – [_Final Fantasy VII_] "Deliverance of the Heart" by pixietricks and zircon at <http://ocremix.org/>

gameOver – untitled by Isaac Wardlaw

### Sounds

All sounds composed of elements from the libraries of RPG Maker 2003 and FruityLoops 3 and mixed by Isaac Wardlaw.

### Production

Visual editing – Microsoft Paint, GraphicsGale, and Microsoft Office 2010

Audio editing – FruityLoops 3 and Audacity

Coding – Microsoft Visual C++ Express 2010 and Microsoft Visual Studio 2010

GUI – Simple DirectMedia Layer

### Source Media

Source media that were modified and that are freely available are included the [Source Media folder](./Source%20Media).

* * *

[_Return to personal portfolio page._](https://iwardlaw.github.io/portfolio)
