#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Sprite.h"
#include <iostream>
#include "Player.h"
#include "Timer.h"
#include "Ball.h"
#include "Goal.h"
#include "Map.h"
#include <math.h>
#include "GameEngine.h"

int main( int argc, char* argv[] )
{
	/* initialize SDL */
	SDL_Init(SDL_INIT_EVERYTHING);

	/* set the title bar */
	SDL_WM_SetCaption("Zone", "Zone");

	//Define necessary constants 
	const SDL_VideoInfo* info = SDL_GetVideoInfo();   //<-- calls SDL_GetVideoInfo();   
	int screenWidth = info->current_w;
	int screenHeight = info->current_h;

	GameEngine game(screenWidth, screenHeight);

	if(game.startMenu()){
		game.teamSelection();
	}

	/* cleanup SDL */
	SDL_Quit();

	return 0;
}