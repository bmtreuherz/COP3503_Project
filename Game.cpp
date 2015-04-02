#include <SDL/SDL.h>
#include "Sprite.h"
#include <iostream>
#include "Player.h"
#include "Constants.h"
#include "Timer.h"
#include "Ball.h"
#include "Goal.h"
#include "Map.h"

/*
To compile 

	just go to the directory 
	enter

	make

	then 
	./Game to run

	DO NOT DO THIS HERE

	g++ -c Sprite.cpp -w -lSDL
	g++ -c Player.cpp -w -lSDL
	g++ -c Ball.cpp -w -lSDL
	g++ -c Goal.cpp -w -lSDL
	g++ -c Map.cpp -w -lSDL
	g++ Game.cpp Player.cpp Sprite.cpp Ball.cpp Goal.cpp Map.cpp -w -lSDL -o Game
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

	//Create Players
	//create Players
	Player P1(100, 1, 50, 50);
	P1.Load("lib/green.bmp");
	Player P2(100 , 1, 50, 50);
	P2.Load("lib/green.bmp");
	Player P3(100, 0, 50, 50);
	P3.Load("lib/red.bmp");
	Player P4(100, 0, 50, 50);
	P4.Load("lib/red.bmp");

	//Remove later
	P1.setX(50);
	P1.setY(50);

	P2.setX(150);
	P2.setY(150);

	P3.setX(200);
	P3.setY(200);

	P4.setX(250);
	P4.setY(250);

	Player players[4] = {P1, P2, P3, P4};
	std::cout<< (sizeof(players)/sizeof(*players)) <<std::endl;

	//create ball
	Ball ball(100, 50, 50);
	ball.setX(300);
	ball.setY(300);
	ball.Load("lib/purple.bmp");	

	//create goals
	Goal goal(1, 100, 100);
	Goal goals[] = {goal};
	//create map
	Map map(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "lib/background.bmp", goals);

	/*
	//create player object
	Player hero(100, 1, 50, 50);
	hero.Load("lib/green.bmp");
	


	//create object for collision testing
	Sprite b(50, 50);
	b.setX(50);
	b.setY(50);
	b.Load("lib/purple.bmp");
	
	*/
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
				/*
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
				*/
			}
					
		}

		/* draw the background */
		bg=map.updateDisplay(players, ball);



		SDL_BlitSurface(bg, NULL, screen, NULL);

		
		/*
		//Draw the sprite and update his position
		ball.Draw(screen, ball, ball.getX(), ball.getY());
		hero.move(timer->getDT());
		hero.Draw(screen, hero, hero.getX(),hero.getY());
		b.Draw(screen, b, b.getX(), b.getY());
		*/



		/* update the screen */
		SDL_UpdateRect(screen, 0, 0, 0, 0);


		/*
		//collision
		//collision detection
		if(hero.checkCollision(hero, b)){
			std::cout<<"collided!"<<std::endl;
		}
		else{
			std::cout<<"Not"<<std::endl;
		}
		*/
	}

	/* free the background surface */
	SDL_FreeSurface(bg);

	/* cleanup SDL */
	SDL_Quit();


	delete timer;

	return 0;
}