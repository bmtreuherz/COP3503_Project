#include <SDL/SDL.h>
#include "Sprite.cpp"
#include <iostream>
#include "Player.cpp"
#include "Constants.h"
#include "Timer.cpp"

/*
To compile 
	g++ Game.cpp -w -lSDL -o Game
	./Game
*/

int main( int argc, char* argv[] )
{
	/* initialize SDL */
	SDL_Init(SDL_INIT_VIDEO);

	/* set the title bar */
	SDL_WM_SetCaption("Game", "Game");

	/* create window */
	SDL_Surface* screen = SDL_SetVideoMode(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, 0, 0);

	/* load bitmap to temp surface */
	SDL_Surface* temp = SDL_LoadBMP("lib/background.bmp");

	/* convert bitmap to display format */
	SDL_Surface* bg = SDL_DisplayFormat(temp);

	/* free the temp surface */
	SDL_FreeSurface(temp);

	SDL_Event event;
	int gameover = 0;

	//create player object
	Player hero(100, 100, Sprite::Load("lib/mario.bmp"));

	//Testing timer
	Timer* timer = new Timer();

	/* message pump */
	while (!gameover)
	{
		/* look for an event */
		if (SDL_PollEvent(&event)) {
			/* an event was found */
			switch (event.type) {
				/* close button clicked */
				case SDL_QUIT:
					gameover = 1;
					break;

				/* handle the keyboard */
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
						case SDLK_q:
							gameover = 1;
							break;

						case SDLK_UP:
							hero.moveUp(true);
							break;
						case SDLK_DOWN:
							hero.moveDown(true);
							break;
						case SDLK_RIGHT:
							hero.moveRight(true);
							break;
						case SDLK_LEFT:
							hero.moveLeft(true);
							break;	
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym){
						case SDLK_UP:
							hero.moveUp(false);
							break;
						case SDLK_DOWN:
							hero.moveDown(false);
							break;
						case SDLK_RIGHT:
							hero.moveRight(false);
							break;
						case SDLK_LEFT:
							hero.moveLeft(false);
							break;	
					}
			}
		}

		/* draw the background */
		SDL_BlitSurface(bg, NULL, screen, NULL);

		//Draw the sprite and update his position

		hero.move(timer->getDT());
		Sprite::Draw(screen, hero.getSurface(), hero.getX(),hero.getY());

		/* update the screen */
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}

	/* free the background surface */
	SDL_FreeSurface(bg);

	/* cleanup SDL */
	SDL_Quit();


	delete timer;

	return 0;
}