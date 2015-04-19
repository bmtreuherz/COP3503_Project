#include <SDL/SDL.h>

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class GameEngine{
	int screenHeight;
	int screenWidth;
	SDL_Surface* screen;
	SDL_Joystick** joysticks;

public:
	GameEngine(int screenWidth, int screenHeight);
	void teamSelection();
	bool startMenu();
	void gameLoop(int teams[4]);
	bool winScreen(int winner, SDL_Surface* bg);
};

#endif