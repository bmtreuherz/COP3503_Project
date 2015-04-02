#include <SDL/SDL.h>
#include "Player.h"
#include "Controller.h"
#include <iostream>

Controller::Controller(Player* player){
	this->player = player;
	this->stick = NULL;
}
Controller::~Controller(){
	//SDL_JoystickClose(stick);
}

void Controller::loadController(SDL_Joystick* stick){
	this->stick = stick;
}

//takes in the event if ths is the joystick that moved
void Controller::handleEvent(SDL_Event &event){
	//If the x axis changes

	if(event.jaxis.axis==0){
		
		//Must be greater than a certain threshold
		if((event.jaxis.value < -11000) || (event.jaxis.value > 11000)){
			//mverify this later
			if(event.jaxis.value < 0){
				player->moveLeft= true;
			}
			else{
				player->moveRight= true;
			}

		}
		else{
			player->moveLeft= false;
			player->moveRight= false;
		}
	}
	else{
		//Must be greater than a certain threshold
		if((event.jaxis.value < -11000) || (event.jaxis.value > 11000)){
			//move down i think
			if(event.jaxis.value < 0){
				player->moveUp= true;
			}
			else{
				player->moveDown= true;
			}

		}
		else{
			player->moveUp= false;
			player->moveDown= false;
		}

	}

	//handle button pressing later
}
