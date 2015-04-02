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
	SDL_Init(SDL_INIT_EVERYTHING);

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

	//create Players
	Player P1(Constants::SPEED, 1, 50, 50);
	P1.Load("lib/green.bmp");
	Player P2(Constants::SPEED , 1, 50, 50);
	P2.Load("lib/green.bmp");
	Player P3(Constants::SPEED, 0, 50, 50);
	P3.Load("lib/red.bmp");
	Player P4(Constants::SPEED, 0, 50, 50);
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

	//Load Joysticks
	if(SDL_NumJoysticks >0){
		SDL_Joystick* C1 = SDL_JoystickOpen(0);
		SDL_Joystick* C2 = SDL_JoystickOpen(1);
		SDL_Joystick* C3 = SDL_JoystickOpen(2);
		SDL_Joystick* C4 = SDL_JoystickOpen(3);
	}


	//create ball
	Ball ball(Constants::SPEED, 15, 15);
	ball.setX(300);
	ball.setY(300);
	ball.Load("lib/cyan.bmp");	

	//create goals
	Goal goal(1, 100, 100);
	Goal goals[] = {goal};

	//create map
	Map map(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "lib/background.bmp", goals);


	//Create timer
	Timer* timer = new Timer();
	float dt=0;

	SDL_Event event;
	int gameover = 0;

	/* message pump */
	while (!gameover)
	{	
		/* look for an event */
		while (SDL_PollEvent(&event)) {
			/* an event was found */
			switch (event.type) {
				/* close button clicked */
				case SDL_QUIT:
					gameover = 1;
					break;

				//joystick movement
				case SDL_JOYAXISMOTION:
					if((event.jaxis.value < -11000 || event.jaxis.value > 11000)){
						switch (event.jaxis.which){
							case 0:
								if(event.jaxis.axis==0){
									players[0].moveX = event.jaxis.value;
								}
								else{
									players[0].moveY = event.jaxis.value;
								}
								break;
							case 1:
								if(event.jaxis.axis==0){
									players[1].moveX = event.jaxis.value;
								}
								else{
									players[1].moveY = event.jaxis.value;
								}
								break;
							case 2:
								if(event.jaxis.axis==0){
									players[2].moveX = event.jaxis.value;
								}
								else{
									players[2].moveY = event.jaxis.value;
								}
								break;
							case 3:
								if(event.jaxis.axis==0){
									players[3].moveX = event.jaxis.value;
								}
								else{
									players[3].moveY = event.jaxis.value;
								}
								break;
						}
					}
					else if ((event.jaxis.value > -11000 && event.jaxis.value < 11000)){
						if(event.jaxis.axis==0){
							players[event.jaxis.which].moveX = 0;
						}
						else{
							players[event.jaxis.which].moveY = 0;
						}
					}

				/* handle the keyboard */
				
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
						case SDLK_q:
							gameover = 1;
							break;
					}
			}
					
		}
		std::cout<<"X is: " << ball.getX() << "Y is: " << ball.getY()<<std::endl;
		//fix this to not be hard coded

		dt= timer->getDT();

		

		for(int i=0; i<4; i++){
			players[i].move(dt);
			
		}
		ball.move(dt);
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