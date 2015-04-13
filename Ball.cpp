#include <SDL/SDL.h>
#include "Ball.h"
#include <iostream>
#include "Sprite.h"

void Ball::move(double dt){



	if(captor==NULL){	
	//problems with dt being too large at program start
		/*
		if (dt > 10000 || dt < -10000){
			return;
		}
		
		this->x += speedX * dt;
		this->y += speedY * dt;

		if(this->x >= Constants::SCREEN_WIDTH - this->width || this-> x <=0){
			speedX *= -1;
		}
		if(this->y >= Constants::SCREEN_HEIGHT - this->height || this-> y <=0){
			speedY *= -1;
		}
		*/	
	}

	else{
		this->x = captor->getX() + captor->getWidth()/2 - this->getWidth()/2;
		this->y = captor->getY() + captor->getHeight()/2 - this->getHeight()/2;
	}



}

void Ball::getCaptured(Player* captor){
	this->captor = captor;
}


void Ball::getshot(double theta){
	//todo: implement
}

Player* Ball::getCaptor(){
	return this->captor;
}