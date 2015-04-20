#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Sprite.h"
#include <SDL/SDL_mixer.h>
#include <iostream>
#include "Player.h"
#include "Timer.h"
#include "Ball.h"
#include "Goal.h"
#include "Map.h"
#include <math.h>
#include "GameEngine.h"
#include "Music.h"

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




	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
    {
        std::cout<<"MIXER DID NOT OPEN"<<std::endl;   
    }




	GameEngine game(screenWidth, screenHeight);

	
	
	//initialize the SDL_Mixer
	//game.initAudio("lib/gamesong.wav");

	if(game.startMenu()){
		game.teamSelection();
	}

	
   // Mix_FreeMusic( music );
	Mix_CloseAudio();



	/* cleanup SDL */
	SDL_Quit();

	return 0;
}