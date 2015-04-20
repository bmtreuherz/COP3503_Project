#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "Music.h"

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class GameEngine{
	int screenHeight;
	int screenWidth;
	SDL_Surface* screen;
	SDL_Joystick** joysticks;

	Music *music;


public:
	GameEngine(int screenWidth, int screenHeight);
	void teamSelection();
	bool startMenu();
	void gameLoop(int teams[4]);
	bool winScreen(int winner, SDL_Surface* bg);
};

#endif