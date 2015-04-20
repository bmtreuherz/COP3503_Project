#include <SDL/SDL.h>
#include "Sprite.h"
#include "Player.h"
#include "Map.h"
#include "Goal.h"
#include "Ball.h"
#include <iostream>

SDL_Surface* Map::updateDisplay(Player players[], Ball ball, Goal goals[]){
	//update screen
	Sprite surrounder(64,64);
	surrounder.Load("lib/Circle.png");
	//blank slate
	this->Draw(surface, background, 0,0);

	bool hasBall;

	//Display all goals
	for(int i = 0; i < 4; i++){
		this->Draw(this->surface, goals[i]);

		for(int j=goals[i].getX(); j<=goals[i].getFillGoal()->getX(); j+=goals[i].getFillGoal()->getWidth()){
			for(int k=goals[i].getY(); k<=goals[i].getFillGoal()->getY(); k+=goals[i].getFillGoal()->getHeight()){
				if(k < goals[i].getFillGoal()->getY()){
					for(int x=goals[i].getX(); x<goals[i].getX() + goals[i].getWidth(); x+=goals[i].getFillGoal()->getWidth()){
						this->Draw(this->surface, goals[i].getFillGoal()->getSurface(), x, k);
					}
				}
				if(k< goals[i].getY() + goals[i].getHeight()){
					this->Draw(this->surface, goals[i].getFillGoal()->getSurface(), j,k);
				}
			}	
		}

	}
	
	//Display all the players
	for(int i=0; i < 4; i++){
		if(players[i].getBall()){
			Draw(this->surface, surrounder.getSurface(), (players[i].getX() + players[i].getWidth()/2) - surrounder.getWidth()/2, (players[i].getY() + players[i].getHeight()/2) - surrounder.getHeight()/2);
		}
		this->Draw(this->surface, players[i]);
	}
	this->Draw(this->surface, ball);
	//testing

	return this->surface;	
}
