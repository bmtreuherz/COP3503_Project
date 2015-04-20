#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "Music.h"
#include "Ball.h"
#include <iostream>
#include "Sprite.h"
#include <math.h>

void Ball::move(double dt, int screenWidth, int screenHeight, Mix_Chunk* hitWall){


	if(captor==NULL){

		count++; 

		this->x += 0.3 * speedX * dt;
		this->y += 0.3 * speedY * dt;

	

		if((this->x > screenWidth - this->width) || this->x < 0){
			Mix_PlayChannel(-1, hitWall, 0);
			speedX *=-1;
			
		}

		if((this->y > screenHeight - this->height) || this->y < 0){
			Mix_PlayChannel(-1, hitWall, 0);
			speedY *=-1;
			
		}

		if(count > 1){
			capturable = true;
		}

		if(count % 10 == 0){
			speedX *= 0.95;
			speedY *= 0.95;
		}

	}

	else{

		count++;

		this->x = captor->getX() + captor->getWidth()/2 - this->getWidth()/2;
		this->y = captor->getY() + captor->getHeight()/2 - this->getHeight()/2;

		if(count >10){
			capturable = true;
		}
	}

}

void Ball::getCaptured(Player* captor){
	this->captor = captor;
	capturable = false;
	count = 0;
}
bool Ball::isCapturable(){
	return capturable;
}

void Ball::getShot(double theta){
	this->captor = NULL;
	this->speedX = speedMax * cos(theta);
	this->speedY = speedMax * sin(theta);

	this->theta = theta; 
	capturable = false;
	count = 0;
}

Player* Ball::getCaptor(){
	return this->captor;
}