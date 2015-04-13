#include <SDL/SDL.h>
#include "Sprite.h"
#include <iostream>
#include "Player.h"
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

	//Define necessary constants 
	const SDL_VideoInfo* info = SDL_GetVideoInfo();   //<-- calls SDL_GetVideoInfo();   
	int screenWidth = info->current_w;
	int screenHeight = info->current_h;
	float speed = 0.001 * screenWidth;
	double speedBall = 0.01 * screenWidth;


	/* create window */
	SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 0, SDL_FULLSCREEN);


	/* load bitmap to temp surface */
	SDL_Surface* temp = SDL_LoadBMP("lib/background.bmp");

	/* convert bitmap to display format */
	SDL_Surface* bg = SDL_DisplayFormat(temp);

	/* free the temp surface */
	SDL_FreeSurface(temp);

	//create Players
	Player P1(speed, 1, 50, 50);
	P1.Load("lib/green.bmp");
	Player P2(speed , 1, 50, 50);
	P2.Load("lib/green.bmp");
	Player P3(speed, 0, 50, 50);
	P3.Load("lib/red.bmp");
	Player P4(speed, 0, 50, 50);
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
	Ball ball(speedBall, 15, 15);
	ball.Load("lib/cyan.bmp");	
	ball.setX(screenWidth/2);
	ball.setY(screenHeight/2);

	//create goals
	Goal goalFalse(0, 100, screenHeight/2, "lib/red.bmp");
	Goal goalTrue(1, 100, screenHeight/2, "lib/red.bmp");
	goalFalse.setX(0);
	goalFalse.setY(screenHeight/4);
	goalTrue.setX(screenWidth-goalTrue.getWidth());
	goalTrue.setY(screenHeight/4);
	goalTrue.Load("lib/cyan.bmp");
	goalFalse.Load("lib/cyan.bmp");
	Goal goals[] = {goalFalse, goalTrue};



	//create map
	Map map(screenWidth, screenHeight, "lib/background.bmp", goals);

	//Create timer
	///Ball timer is necessary to prevent ball from constantly switchng back and forth
	Timer* timer = new Timer();
	Timer* ballTimer = new Timer();
	float ballDT=0;
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

		//player and ball movement
		dt= timer->getDT();
		
		for(int i=0; i<4; i++){
			players[i].move(dt);

			if(ball.getCaptor()==NULL){
				if(ball.checkCollision(players[i]) !=-1){
					ball.getCaptured(&players[i]);
					players[i].captureBall(true);
				}	
			}
		}

		ball.move(dt);

		//check to see if the ball collides with a player


		//testing new collission detectoin
		int dif;
		for(int i=0; i<3; i++){
			for(int j=1; j<4; j++){
				if(i!=j){
					int side = players[i].checkCollision(players[j]);
					switch (side){
						case 0:
							ballDT= ballTimer->getDT();
							dif = players[i].getHeight() - (players[i].getY()-players[j].getY());
							players[i].setY(players[i].getY()+dif/2);
							players[j].setY(players[j].getY()-dif/2);

							//players[i].setY(players[j].getY()+players[j].getHeight());
							break;
						case 1:
							ballDT= ballTimer->getDT();
							dif = players[i].getWidth() - (players[j].getX()-players[i].getX());
							players[i].setX(players[i].getX()-dif/2);
							players[j].setX(players[j].getX()+dif/2);

							//players[i].setX(players[j].getX()-players[j].getWidth());
							break;
						case 2:	
							ballDT= ballTimer->getDT();
							dif = players[i].getHeight() - (players[j].getY()-players[i].getY());
							players[i].setY(players[i].getY()-dif/2);
							players[j].setY(players[j].getY()+dif/2);
							
							//players[i].setY(players[j].getY()-players[j].getHeight());
							break;
						case 3:
							ballDT= ballTimer->getDT();
							dif = players[i].getWidth() - (players[i].getX()-players[j].getX());
							players[i].setX(players[i].getX()+dif/2);
							players[j].setX(players[j].getX()-dif/2);

							//players[i].setX(players[j].getX()+players[j].getWidth());
							break;

					}
					//ball stealing
					if(side!=-1 && (ballDT==0 || ballDT > 20)){
						if(players[i].getBall()){
							
							players[i].captureBall(false);
							players[j].captureBall(true);
							ball.getCaptured(&players[j]);
						}
						else if(players[j].getBall()){
					

							players[j].captureBall(false);
							players[i].captureBall(true);
							ball.getCaptured(&players[i]);
						}
					}
				}
			}
		}


		//make sure that the players cant go off the map
		for(int i=0; i<4; i++){
			if(players[i].getX()<0){
				players[i].setX(0);
			}
			else if(players[i].getX()>screenWidth-players[i].getWidth()){
				players[i].setX(screenWidth-players[i].getWidth());
			}
			if(players[i].getY()<0){
				players[i].setY(0);
			}
			else if(players[i].getY()>screenHeight-players[i].getHeight()){
				players[i].setY(screenHeight-players[i].getHeight());
			}
		}

		//increment score
		
		for(int i=0; i<2; i++){
			if(ball.checkCollision(goals[i]) !=-1){
				goals[i].incrementScore();
				if(goals[i].getScore() >=1000){
					std::cout<<"Team "<<i<<" Wins!"<< std::endl;
					gameover =1;

				}
			}
		}
		


		/* draw the background */
		bg=map.updateDisplay(players, ball, goals);


		SDL_BlitSurface(bg, NULL, screen, NULL);



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