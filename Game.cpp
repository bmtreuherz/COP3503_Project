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

bool winScreen(int winner, SDL_Surface* bg){
	//Define necessary constants 
	const SDL_VideoInfo* info = SDL_GetVideoInfo();   //<-- calls SDL_GetVideoInfo();   
	int screenWidth = info->current_w;
	int screenHeight = info->current_h;
	SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 0, SDL_FULLSCREEN);

	//get the joysticks
	SDL_Joystick* C1 = SDL_JoystickOpen(0);
	SDL_Joystick* C2 = SDL_JoystickOpen(1);
	SDL_Joystick* C3 = SDL_JoystickOpen(2);
	SDL_Joystick* C4 = SDL_JoystickOpen(3);
	SDL_Joystick* joysticks[] = {C1, C2, C3, C4};

	//load all the sprites
	Sprite redTeam(418, 73);
	Sprite blueTeam(461, 73);
	Sprite wins(247, 67);
	Sprite playAgain(273, 64);
	Sprite playAgainGlow(277, 70);
	Sprite quit(136, 57);
	Sprite quitGlow(140, 63);
	
	

	redTeam.Load("lib/redteam.png");
	blueTeam.Load("lib/blueteam.png");
	wins.Load("lib/WINS.png");
	playAgain.Load("lib/Play-Again.png");
	playAgainGlow.Load("lib/Play-AgainGlow.png");
	quit.Load("lib/Quit.png");
	quitGlow.Load("lib/QuitGlow.png");


	//Getting numbers to make formatting nicely
	redTeam.setX(screenWidth/2 - (350));
	redTeam.setY(screenHeight/3);
	blueTeam.setX(screenWidth/2 - (350));
	blueTeam.setY(screenHeight/3);

	wins.setX(redTeam.getX() + redTeam.getWidth()+20);
	wins.setY(screenHeight/3);

	playAgain.setX(screenWidth/2 - (216));
	playAgain.setY(2*screenHeight/3);
	playAgainGlow.setX(screenWidth/2 - (216));
	playAgainGlow.setY(2*screenHeight/3);

	quit.setX(playAgain.getX()+ playAgain.getWidth() +20);
	quit.setY(2*screenHeight/3);
	quitGlow.setX(playAgain.getX()+ playAgain.getWidth() +20);
	quitGlow.setY(2*screenHeight/3);


	int endLoop = 0;
	SDL_Event event;

	//make the default choice play again
	bool play = true;

	while (!endLoop){

		//look for an event
		while (SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					endLoop = 1;
					break;
				//button pressed
				case SDL_JOYBUTTONDOWN:
					if(event.jbutton.button==0){
						endLoop = 1;
						if(play){
							return true;
						}
						else{
							return false;
						}
					}
				//handle movement
				case SDL_JOYAXISMOTION:
					if(event.jaxis.value < -11000 && event.jaxis.axis==0){
						play = true;
					}
					if(event.jaxis.value > 11000 && event.jaxis.axis==0){
						play = false;
					}
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
						case SDLK_q:
							endLoop = 1;
							break;
					}
			}
		}
		//TODO::Blit all the assets
		if(winner){
			redTeam.Draw(bg, redTeam.getSurface(), redTeam.getX(), redTeam.getY());
		}
		else{
			blueTeam.Draw(bg, redTeam.getSurface(), blueTeam.getX(), blueTeam.getY());
		}

		wins.Draw(bg, wins.getSurface(), wins.getX(), wins.getY());

		//make these switch depending on which is selected

		if(play){
			playAgainGlow.Draw(bg, playAgainGlow.getSurface(), playAgainGlow.getX(), playAgainGlow.getY());
			quit.Draw(bg, quit.getSurface(), quit.getX(), quit.getY());
		}
		else{
			playAgain.Draw(bg, playAgain.getSurface(), playAgain.getX(), playAgain.getY());
			quitGlow.Draw(bg,quitGlow.getSurface(), quitGlow.getX(), quitGlow.getY()); 
		}

		SDL_BlitSurface(bg, NULL, screen, NULL);
		SDL_UpdateRect(screen, 0, 0, 0, 0);

	}

}

void gameLoop(){

	//Define necessary constants 
	const SDL_VideoInfo* info = SDL_GetVideoInfo();   //<-- calls SDL_GetVideoInfo();   
	int screenWidth = info->current_w;
	int screenHeight = info->current_h;

	//int screenWidth = 1920/2;
	//int screenHeight = 1080/2;

	float speed = 0.0005 * screenWidth;
	double speedBall = 0.005 * screenWidth;

	
	/* create window */
	SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 0, SDL_FULLSCREEN);

	/*
	SDL_Surface* temp = SDL_LoadBMP("lib/background.bmp");

	SDL_Surface* bg = SDL_DisplayFormat(temp);

	
	SDL_FreeSurface(temp);
	*/

	Sprite background(screenWidth, screenHeight);
	background.Load("lib/background.bmp");
	SDL_Surface* bg = background.getSurface();

	//create Players
	Player P1(speed, 1, 30, 30);
	P1.Load("lib/lightGreen.bmp");
	Player P2(speed , 1, 30, 30);
	P2.Load("lib/lightGreen.bmp");
	Player P3(speed, 0, 30, 30);
	P3.Load("lib/lightRed.bmp");
	Player P4(speed, 0, 30, 30);
	P4.Load("lib/lightRed.bmp");

	//starting points
	P1.setX(screenWidth/2 - 3*P1.getWidth());
	P1.setY(screenHeight/2 - 3 * P1.getHeight());

	P2.setX(screenWidth/2 - 3 * P2.getWidth());
	P2.setY(screenHeight/2 + 2 * P2.getHeight());

	P3.setX(screenWidth/2 + 2 * P3.getWidth());
	P3.setY(screenHeight/2 - 3 * P3.getHeight());

	P4.setX(screenWidth/2 + 2 * P4.getWidth());
	P4.setY(screenHeight/2 + 2 * P4.getHeight());

	Player players[4] = {P1, P2, P3, P4};

	//Load Joysticks
	
	SDL_Joystick* C1 = SDL_JoystickOpen(0);
	SDL_Joystick* C2 = SDL_JoystickOpen(1);
	SDL_Joystick* C3 = SDL_JoystickOpen(2);
	SDL_Joystick* C4 = SDL_JoystickOpen(3);
	SDL_Joystick* joysticks[] = {C1, C2, C3, C4};


	//create ball
	Ball ball(speedBall, 15, 15);
	ball.Load("lib/cyan.bmp");	
	ball.setX(screenWidth/2);
	ball.setY(screenHeight/2);

	//create goals
	Goal goalFalse(0, screenWidth/10, screenHeight/2, "lib/lightRed.bmp");
	Goal goalTrue(1, screenWidth/10, screenHeight/2, "lib/lightGreen.bmp");
	goalFalse.setX(0);
	goalFalse.setY(screenHeight/4);
	goalTrue.setX(screenWidth-goalTrue.getWidth());
	goalTrue.setY(screenHeight/4);
	goalTrue.Load("lib/darkGreen.bmp");
	goalFalse.Load("lib/darkRed.bmp");
	Goal goals[] = {goalFalse, goalTrue};

	//create map
	Map map(screenWidth, screenHeight, "lib/gameBG.bmp", goals);

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
					break;

				case SDL_JOYBUTTONDOWN:
					//a button pressed
					if(event.jbutton.button==0){
						if(players[event.jbutton.which].getBall()){
							double x = SDL_JoystickGetAxis(joysticks[event.jbutton.which],0);
							double y = SDL_JoystickGetAxis(joysticks[event.jbutton.which],1);
							double theta = atan(y/x);

							if(x < 0){
								theta += 3.14;
							}

							ball.getShot(theta);
							players[event.jbutton.which].captureBall(false);
						}
					}				
					//determine which button is which 0:a 9:start
					break;

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
				if(ball.checkCollision(players[i]) !=-1 && ball.isCapturable()){
					ball.getCaptured(&players[i]);
					players[i].captureBall(true);
				}	
			}
		}

		ball.move(dt, screenWidth, screenHeight);

		//check to see if the ball collides with a player


		//testing new collission detectoin
		int dif;
		for(int i=0; i<3;i++){
			for(int j=1; j<4; j++){
				if(i!=j){
					int side = players[i].checkCollision(players[j]);
					switch (side){
						case 0:
							ballDT= ballTimer->getDT();
							dif = players[i].getHeight() - (players[i].getY()-players[j].getY());
							players[i].setY(players[i].getY()+dif/2 + 1);
							players[j].setY(players[j].getY()-dif/2 -1 );

							//players[i].setY(players[j].getY()+players[j].getHeight());
							break;
						case 1:
							ballDT= ballTimer->getDT();
							dif = players[i].getWidth() - (players[j].getX()-players[i].getX());
							players[i].setX(players[i].getX()-dif/2 - 1);
							players[j].setX(players[j].getX()+dif/2 + 1);

							//players[i].setX(players[j].getX()-players[j].getWidth());
							break;
						case 2:	
							ballDT= ballTimer->getDT();
							dif = players[i].getHeight() - (players[j].getY()-players[i].getY());
							players[i].setY(players[i].getY()-dif/2 - 1);
							players[j].setY(players[j].getY()+dif/2 + 1);
							
							//players[i].setY(players[j].getY()-players[j].getHeight());
							break;
						case 3:
							ballDT= ballTimer->getDT();
							dif = players[i].getWidth() - (players[i].getX()-players[j].getX());
							players[i].setX(players[i].getX()+dif/2 + 1);
							players[j].setX(players[j].getX()-dif/2 - 1);

							//players[i].setX(players[j].getX()+players[j].getWidth());
							break;

					}
					//ball stealing
					ballDT = ballTimer->getDT();
					std::cout<<ballDT<<std::endl;

					if(side!=-1 && ball.isCapturable()){
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
				std::cout<<goals[1].getScore()<<std::endl;

				if(goals[i].getFillY() >= goals[i].getY() + goals[i].getHeight()){
					std::cout<<"Team "<<i<<" Wins!"<< std::endl;
					
					if(winScreen(i, map.getSurface())){
						gameLoop();
					}
					gameover = 1;
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


	delete timer;
	delete ballTimer;

}

void startMenu(){
	//Define necessary constants 
	const SDL_VideoInfo* info = SDL_GetVideoInfo();   //<-- calls SDL_GetVideoInfo();   
	int screenWidth = info->current_w;
	int screenHeight = info->current_h;

	//int screenWidth = 1920/2;
	//int screenHeight = 1080/2;

	float speed = 0.0005 * screenWidth;
	double speedBall = 0.005 * screenWidth;

	
	/* create window */
	SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 0, SDL_FULLSCREEN);

	/* load bitmap to temp surface */
	SDL_Surface* temp = SDL_LoadBMP("lib/background.bmp");

	/* convert bitmap to display format */
	SDL_Surface* bg = SDL_DisplayFormat(temp);

	/* free the temp surface */
	SDL_FreeSurface(temp);

	SDL_Joystick* C1 = SDL_JoystickOpen(0);
	SDL_Joystick* C2 = SDL_JoystickOpen(1);
	SDL_Joystick* C3 = SDL_JoystickOpen(2);
	SDL_Joystick* C4 = SDL_JoystickOpen(3);
	SDL_Joystick* joysticks[] = {C1, C2, C3, C4};


	//display the "press start and logo"
	Sprite titlebg(1920, 1080);
	Sprite gamename(403, 132);
	Sprite startbutton(253, 60);

	titlebg.Load("lib/titleBG.jpg");
	gamename.Load("lib/Zone.png");
	startbutton.Load("lib/PRESS-START.png");

	int startGame = 0;
	SDL_Event event;

	while (!startGame){


		//look for an event
		while (SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					startGame = 1;
					break;
				//button pressed
				case SDL_JOYBUTTONDOWN:
					if(event.jbutton.button==9){
						std::cout<<"STARTING GAME\n";
						startGame = 1;

						for (int i = 0; i < 7; i++) {
							SDL_Delay(90);
							startbutton.Load("lib/PRESS-START(1).png");
							startbutton.Draw(bg, startbutton.getSurface(),screenWidth/2 - startbutton.getWidth()/2,screenHeight*3/4 - startbutton.getHeight()/2);
							
							SDL_BlitSurface(bg, NULL, screen, NULL);
							SDL_UpdateRect(screen, 0, 0, 0, 0);

							SDL_Delay(90);
							startbutton.Load("lib/PRESS-START.png");
							startbutton.Draw(bg, startbutton.getSurface(),screenWidth/2 - startbutton.getWidth()/2,screenHeight*3/4 - startbutton.getHeight()/2);

							SDL_BlitSurface(bg, NULL, screen, NULL);
							SDL_UpdateRect(screen, 0, 0, 0, 0);
						}
						gameLoop();
						break;
					}
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
						case SDLK_q:
							startGame = 1;
							break;
					}
			}
		}

		titlebg.Draw(bg, titlebg.getSurface(), 0 ,0);
		gamename.Draw(bg, gamename.getSurface(),screenWidth/2 - gamename.getWidth()/2, screenHeight/4 - gamename.getHeight()/2);
		startbutton.Draw(bg, startbutton.getSurface(),screenWidth/2 - startbutton.getWidth()/2,screenHeight*3/4 - startbutton.getHeight()/2);

		SDL_BlitSurface(bg, NULL, screen, NULL);
		SDL_UpdateRect(screen, 0, 0, 0, 0);

	}

	SDL_FreeSurface(bg);
}

int main( int argc, char* argv[] )
{
	/* initialize SDL */
	SDL_Init(SDL_INIT_EVERYTHING);

	/* set the title bar */
	SDL_WM_SetCaption("Zone", "Zone");

	startMenu();

	/* cleanup SDL */
	SDL_Quit();

	return 0;
}