#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "Sprite.h"
#include <iostream>
#include "Player.h"
#include "Timer.h"
#include "Ball.h"
#include "Goal.h"
#include "Map.h"
#include <math.h>
#include "GameEngine.h"
#include "Music.h"

GameEngine::GameEngine(int screenWidth, int screenHeight){
	//initialize the screen
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	screen = SDL_SetVideoMode(screenWidth, screenHeight, 0, SDL_FULLSCREEN);

	//initialize the joysticks
	SDL_Joystick* C1 = SDL_JoystickOpen(0);
	SDL_Joystick* C2 = SDL_JoystickOpen(1);
	SDL_Joystick* C3 = SDL_JoystickOpen(2);
	SDL_Joystick* C4 = SDL_JoystickOpen(3);
	SDL_Joystick* joys[4] = {C1, C2, C3, C4};

	for(int i=0; i<4; i++){
		this->joysticks[i] = joys[i];
	}

	//audio files
	Music *temp = new Music();
	music = temp;
	music->initAudio();
	temp = NULL;
	delete temp;

}

void GameEngine::teamSelection(){

	/* load bitmap to temp surface */
	SDL_Surface* temp = SDL_LoadBMP("lib/background.bmp");

	/* convert bitmap to display format */
	SDL_Surface* bg = SDL_DisplayFormat(temp);

	/* free the temp surface */
	SDL_FreeSurface(temp);

	//load the sprites
	Sprite player1(178, 101);
	Sprite player2(185, 101);
	Sprite player3(185, 101);
	Sprite player4(185, 101);
	Sprite chooseSides(727, 166);
	Sprite redTeam(418, 73);
	Sprite blueTeam(461, 73);
	Sprite ready(178, 56);
	Sprite titlebg(1920, 1080);


	titlebg.Load("lib/titleBG.jpg");
	player1.Load("lib/1.png");
	player2.Load("lib/2.png");
	player3.Load("lib/3.png");
	player4.Load("lib/4.png");


	chooseSides.Load("lib/choose.png");
	redTeam.Load("lib/redteam.png");
	blueTeam.Load("lib/blueteam.png");
	ready.Load("lib/ready.png");

	//format Set X and Ys
	int xBlue = screenWidth/6 - player1.getWidth()/2;
	int xMiddle = screenWidth/2 - player1.getWidth()/2;
	int xRed = 5 * screenWidth/6 - player1.getWidth()/2;

	player1.setX(xMiddle);
	player2.setX(xMiddle);
	player3.setX(xMiddle);
	player4.setX(xMiddle);

	player1.setY(2*screenHeight/7);
	player2.setY(player1.getY()+1.5*player2.getHeight());
	player3.setY(player2.getY()+1.5*player3.getHeight());
	player4.setY(player3.getY()+1.5*player4.getHeight());

	chooseSides.setX(screenWidth/2 - chooseSides.getWidth()/2);
	chooseSides.setY(screenHeight/12);

	blueTeam.setX(blueTeam.getWidth()/8);
	redTeam.setX(screenWidth- redTeam.getWidth() - redTeam.getWidth()/8);

	redTeam.setY(screenHeight/5);
	blueTeam.setY(screenHeight/5);


	Sprite players[] = {player1, player2, player3, player4};

	int endLoop = 0;
	SDL_Event event;


	//timer needed to slow the moving from side to side
	Timer* timer1 = new Timer();
	Timer* timer2 = new Timer();
	Timer* timer3 = new Timer();
	Timer* timer4 = new Timer();

	int dt1 = 1000;
	int dt2 = 1100;
	int dt3 = 1100;
	int dt4 = 1010;


	//If there is no music playing
    if( Mix_PlayingMusic() == 0 ){
    	Mix_PlayMusic(music->getTitleScreen(), -1);
    }

	//make the default choice play again
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
						if(players[event.jbutton.which].getX() == xRed ||players[event.jbutton.which].getX() == xBlue){
							
							if(players[event.jbutton.which].isReady()){
								players[event.jbutton.which].setReady(false);
								Mix_PlayChannel(-1, music->getDeselectTeam(), 0);
							}
							else{
								players[event.jbutton.which].setReady(true);
								Mix_PlayChannel(-1, music->getSelectTeam(), 0);

							}
						}
					}

				//handle movement
				case SDL_JOYAXISMOTION:
					if(!players[event.jaxis.which].isReady()){
						if(event.jaxis.value < -11000 && event.jaxis.axis==0){
							switch (event.jaxis.which){
								case 0:
									if(players[0].getX() == xMiddle && timer1->getDT() > 85){
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
										players[0].setX(xBlue);
									}

									else if (players[0].getX()==xRed){
										players[0].setX(xMiddle);
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
										dt1 = timer1->getDT();
									}
									break;
								case 1:
									if(players[1].getX() == xMiddle && timer2->getDT() >85){
										players[1].setX(xBlue);
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									else if (players[1].getX()==xRed){
										players[1].setX(xMiddle);
										dt2 = timer2->getDT();
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}								
									break;
								case 2:
									if(players[2].getX() == xMiddle && timer3->getDT()>85){
										players[2].setX(xBlue);
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									else if (players[2].getX()==xRed){
										players[2].setX(xMiddle);
										dt3 = timer3->getDT();
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									break;
								case 3:
									if(players[3].getX() == xMiddle && timer4->getDT()>85){
										players[3].setX(xBlue);
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									else if (players[0].getX()==xRed){
										players[3].setX(xMiddle);
										dt4 = timer4->getDT();
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
										
									}
									break;
							}
							
						}
						if(event.jaxis.value > 11000 && event.jaxis.axis==0){
							switch (event.jaxis.which){
								case 0:
									if(players[0].getX() == xMiddle && timer1->getDT() > 85){
										players[0].setX(xRed);	
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									else if (players[0].getX()==xBlue){
										dt1 = timer1->getDT();
										players[0].setX(xMiddle);
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									break;
								case 1:
									if(players[1].getX() == xMiddle && timer2->getDT() > 85){
										players[1].setX(xRed);
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									else if (players[1].getX()==xBlue){
										players[1].setX(xMiddle);
										timer2->getDT();
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									break;							

								case 2:
									if(players[2].getX() == xMiddle && timer3->getDT() > 85){
										players[2].setX(xRed);
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									else if (players[2].getX()==xBlue){
										players[2].setX(xMiddle);
										timer3->getDT();
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									break;
								case 3:
									if(players[3].getX() == xMiddle && timer4->getDT() > 85){
										players[3].setX(xRed);
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									else if (players[0].getX()==xBlue){
										players[3].setX(xMiddle);
										timer4->getDT();
										Mix_PlayChannel(-1, music->getSwitchTeam(), 0);
									}
									break;
							}
						}
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

		titlebg.Draw(bg, titlebg.getSurface(), 0, 0);

		//TODO::Blit all the assets

		int teams[4];
		int readyCount = 0;
		for(int i=0; i<4; i++){
			players[i].Draw(bg, players[i]);
			if(players[i].isReady()){
				readyCount++;
				if(players[i].getX() == xBlue){
					ready.Draw(bg, ready.getSurface(), players[i].getX()+players[i].getWidth(), players[i].getY());
					teams[i] = 0;
				}
				else{
					ready.Draw(bg, ready.getSurface(), players[i].getX() - players[i].getWidth()/6 - ready.getWidth(), players[i].getY());
					teams[i] = 1;
				}
			}
		}

		chooseSides.Draw(bg, chooseSides);
		redTeam.Draw(bg, redTeam);
		blueTeam.Draw(bg, blueTeam);

		//make these switch depending on which is selected

		SDL_BlitSurface(bg, NULL, screen, NULL);
		SDL_UpdateRect(screen, 0, 0, 0, 0);



		if(readyCount ==2){
			endLoop = 1;
			this->gameLoop(teams);
		}

	}
}


bool GameEngine::startMenu(){

	/* load bitmap to temp surface */
	SDL_Surface* temp = SDL_LoadBMP("lib/background.bmp");

	/* convert bitmap to display format */
	SDL_Surface* bg = SDL_DisplayFormat(temp);

	/* free the temp surface */
	SDL_FreeSurface(temp);

	//display the "press start and logo"
	Sprite titlebg(1920, 1080);
	Sprite gamename(403, 132);
	Sprite startbutton(253, 60);

	titlebg.Load("lib/titleBG.jpg");
	gamename.Load("lib/Zone.png");
	startbutton.Load("lib/PRESS-START.png");

	int startGame = 0;
	SDL_Event event;

	Mix_PlayMusic(music->getTitleScreen(), -1);

	while (!startGame){

		//look for an event
		while (SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					startGame = 1;
					return false;
					break;
				//button pressed
				case SDL_JOYBUTTONDOWN:
					if(event.jbutton.button==9){
						std::cout<<"STARTING GAME\n";
						startGame = 1;
						Mix_PlayChannel(-1, music->getStartSound(), 0);

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
						return true;
					}
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
						case SDLK_q:
							startGame = 1;
							return false;
							
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

void GameEngine::gameLoop(int teams[4]){

	float speed = 0.0003 * screenWidth;
	double speedBall = 0.003 * screenWidth;	

	Sprite background(screenWidth, screenHeight);
	background.Load("lib/background.bmp");
	SDL_Surface* bg = background.getSurface();


	//create Players	
	Player P1(speed, teams[0], 30, 30);
	if(teams[0]==0){
		P1.Load("lib/1blue.bmp");
	}
	else{
		P1.Load("lib/1red.bmp");
	}

	Player P2(speed , teams[1], 30, 30);
	if(teams[1]==0){
		P2.Load("lib/2blue.bmp");
	}
	else{
		P2.Load("lib/2red.bmp");
	}

	Player P3(speed, teams[2], 30, 30);
	if(teams[2]==0){
		P3.Load("lib/3blue.bmp");
	}
	else{
		P3.Load("lib/3red.bmp");
	}

	Player P4(speed, teams[3], 30, 30);
	if(teams[3]==0){
		P4.Load("lib/4blue.bmp");
	}
	else{
		P4.Load("lib/4red.bmp");
	}

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


	//create ball
	Ball ball(speedBall, 15, 15);
	ball.Load("lib/Ball.png");	
	ball.setX(screenWidth/2 -ball.getWidth()/2);
	ball.setY(screenHeight/2 - ball.getHeight()/2);

	//create goals
	Goal redGoal1(0, 150, 150, "lib/RedFill.png");
	Goal redGoal2(0, 150, 150, "lib/RedFill.png");
	Goal blueGoal1(1, 150, 150, "lib/BlueFill.png");
	Goal blueGoal2(1, 150, 150, "lib/BlueFill.png");

//old map
/*
	redGoal1.setX(0);
	redGoal1.setY(0);
	redGoal2.setX(screenWidth/2 - redGoal2.getWidth()/2);
	redGoal2.setY(screenHeight/2);
	blueGoal1.setX(screenWidth-blueGoal1.getWidth());
	blueGoal1.setY(screenHeight-blueGoal1.getHeight());
	blueGoal2.setX(screenWidth/2 - redGoal2.getWidth()/2);
	blueGoal2.setY(screenHeight/2-blueGoal2.getHeight());
	blueGoal1.Load("lib/BlueGoal.png");
	blueGoal2.Load("lib/BlueGoal.png");
	redGoal1.Load("lib/RedGoal.png");
	redGoal2.Load("lib/RedGoal.png");
	Goal goals[4] = { blueGoal1, blueGoal2, redGoal1, redGoal2};
	int highestRed=0;
	int highestBlue=0;
*/

	//new map
	redGoal1.setX(0);
	redGoal1.setY(0);
	redGoal2.setX(screenWidth/2 + redGoal2.getWidth()/4);
	redGoal2.setY(screenHeight/2 - redGoal2.getHeight()/2);
	blueGoal1.setX(screenWidth-blueGoal1.getWidth());
	blueGoal1.setY(screenHeight-blueGoal1.getHeight());
	blueGoal2.setX(screenWidth/2 - blueGoal2.getWidth() - blueGoal2.getWidth()/4);
	blueGoal2.setY(screenHeight/2-blueGoal2.getHeight()/2);
	blueGoal1.Load("lib/BlueGoal.png");
	blueGoal2.Load("lib/BlueGoal.png");
	redGoal1.Load("lib/RedGoal.png");
	redGoal2.Load("lib/RedGoal.png");
	Goal goals[4] = { blueGoal1, blueGoal2, redGoal1, redGoal2};
	int highestRed=0;
	int highestBlue=0;

	//create map
	Map map(screenWidth, screenHeight, "lib/gameBG.bmp", goals);

	//Create timer
	///Ball timer is necessary to prevent ball from constantly switchng back and forth
	Timer* timer = new Timer();
	Timer* ballTimer = new Timer();
	float ballDT=0;
	float dt=0;
	bool isFilling = false;
	int goal = -1;

	SDL_Event event;
	int gameover = 0;

	Mix_PlayMusic(music->getGameSong(), -1);

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

							Mix_PlayChannel(-1, music->getShoot(), 0);
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
		dt = timer->getDT();
		
		for(int i=0; i<4; i++){
			players[i].move(dt);

			if(ball.getCaptor()==NULL){
				if(ball.checkCollision(players[i]) !=-1 && ball.isCapturable()){
					ball.getCaptured(&players[i]);
					players[i].captureBall(true);
					Mix_PlayChannel(-1, music->getSteal(), 0);

				}	
			}
		}

		ball.move(dt, screenWidth, screenHeight, music->getBallCollision());

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

					if(side!=-1 && ball.isCapturable()){
						if(players[i].getBall()){
							Mix_PlayChannel(-1, music->getSteal(), 0);
							players[i].captureBall(false);
							players[j].captureBall(true);
							ball.getCaptured(&players[j]);
						}
						else if(players[j].getBall()){
					
							Mix_PlayChannel(-1, music->getSteal(), 0);
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
		for(int i=0; i<4; i++){
			if(i<2){
				if(goals[i].getScore() > highestBlue){
					highestBlue = goals[i].getScore();
				}
				else{
					while(goals[i].getScore() < highestBlue){
						goals[i].incrementScore();
					}
				}
			}	
			else{
				if(goals[i].getScore()>highestRed){
					highestRed = goals[i].getScore();
				}
				else{
					while(goals[i].getScore() < highestRed){
						goals[i].incrementScore();
					}
				}
			}


			if(ball.checkCollision(goals[i]) !=-1){
				if(goals[i].getFillY() >= goals[i].getY() + goals[i].getHeight()){
					Mix_HaltMusic();
					Mix_PlayChannel(0, music->getStartSound(), 0);
					
					
					if(this->winScreen(i, map.getSurface())){
						//stop music
						
						this->teamSelection();
					}
					gameover = 1;
				}


				if(!isFilling){
					Mix_VolumeChunk(music->getFillGoal(), 128);
					Mix_PlayChannel(-1, music->getFillGoal(), 0);
					goal = i;
				}
				
				goals[i].incrementScore();
				if(i<2){
					highestBlue = goals[i].getScore();
				}
				else{
					highestRed= goals[i].getScore();
				}


				isFilling = true;
			}
			if(ball.checkCollision(goals[i]) ==-1 && i == goal){
				Mix_VolumeChunk(music->getFillGoal(), 0);
			}
			else{
				isFilling = false;
			}
		}

		/* draw the background */
		bg=map.updateDisplay(players, ball, goals);


		SDL_BlitSurface(bg, NULL, screen, NULL);

		/* update the screen */
		SDL_UpdateRect(screen, 0, 0, 0, 0);

	}

	//stop music
	Mix_HaltMusic();

	/* free the background surface */
	SDL_FreeSurface(bg);
	


	delete timer;
	delete ballTimer;

}



bool GameEngine::winScreen(int winner, SDL_Surface* bg){

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
						Mix_PlayChannel(-1, music->getSelectTeam(), 0);

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
						if(play == false){
							Mix_PlayChannel(-1, music->getChooseMenu(), 0);
						}
						play = true;
					}
					if(event.jaxis.value > 11000 && event.jaxis.axis==0){
						if(play == true){
							Mix_PlayChannel(-1, music->getChooseMenu(), 0);
						}
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
		if(winner<2){
			blueTeam.Draw(bg, blueTeam.getSurface(), blueTeam.getX(), blueTeam.getY());

		}
		else{
			redTeam.Draw(bg, redTeam.getSurface(), redTeam.getX(), redTeam.getY());
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