#include <SDL/SDL.h>
#include "Sprite.h"
#include "Player.h"
#include "Map.h"
#include "Goal.h"
#include "Ball.h"
#include <iostream>

SDL_Surface* Map::updateDisplay(Player players[], Ball ball, Goal goals[]){
	//update screen
	Sprite surrounder(38,38);
	surrounder.Load("lib/surrounder.bmp");
	//blank slate
	this->Draw(surface, background, 0,0);

	bool hasBall;

	//Display all goals
	for(int i = 0; i < 4; i++){
		this->Draw(this->surface, goals[i]);

		if(goals[i].getFillGoal()->getY()){

		}

		for(int j=goals[i].getX(); j<=goals[i].getFillGoal()->getX(); j+=goals[i].getFillGoal()->getWidth()){
			for(int k=goals[i].getY(); k<=goals[i].getFillGoal()->getY(); k+=goals[i].getFillGoal()->getHeight()){
				if(k < goals[i].getFillGoal()->getY()){
					for(int x=goals[i].getX(); x<goals[i].getX() + goals[i].getWidth(); x+=goals[i].getFillGoal()->getWidth()){
						this->Draw(this->surface, goals[i].getFillGoal()->getSurface(), x, k);
					}
				}

				this->Draw(this->surface, goals[i].getFillGoal()->getSurface(), j,k);
			}	
		}

	}
	
	//Display all the players
	for(int i=0; i < 4; i++){
		if(players[i].getBall()){
			Draw(this->surface, surrounder.getSurface(), players[i].getX()- 3, players[i].getY() - 3);
		}
		this->Draw(this->surface, players[i]);
	}
	this->Draw(this->surface, ball);
	//testing

	return this->surface;	
}
