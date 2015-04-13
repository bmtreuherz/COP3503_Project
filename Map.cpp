#include <SDL/SDL.h>
#include "Sprite.h"
#include "Player.h"
#include "Map.h"
#include "Goal.h"
#include "Ball.h"
#include <iostream>

SDL_Surface* Map::updateDisplay(Player players[], Ball ball, Goal goals[]){
	//update screen
	
	//blank slate
	this->Draw(surface, background, 0,0);

	bool hasBall;
	//Display all goals
	for(int i = 0; i < 2; i++){
		this->Draw(this->surface, goals[i], goals[i].getX(), goals[i].getY());
		
	}


	//Display the ball
	
	//Display all the players
	for(int i=0; i < 4; i++){
		this->Draw(this->surface, players[i], players[i].getX(), players[i].getY());
	}
	this->Draw(this->surface, ball, ball.getX(), ball.getY());

	return this->surface;	
}
