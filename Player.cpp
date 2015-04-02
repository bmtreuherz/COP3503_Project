#include <SDL/SDL.h>
#include "Sprite.h"
#include "Constants.h"
#include "Player.h"
#include <iostream>



/*
void Player::shootBall(Ball b){

}

void Player::captureBall(){
	hasBall = true;
	//more stuff
}
*/

//Change the movement a lot
//Change boolean values of whether or not to move in that direction based on key input

//Once per loop this is called to move in the directions it's supposed to
void Player::move(float dt){
	std::cout<<"X: "<<this->x<<" Y: " << this->y << std::endl;

	if(this->y >= Constants::SCREEN_HEIGHT - this->height){
		this->y--;
	}
	if(this->x >= Constants::SCREEN_WIDTH - this->width){
		this->x++;
	}


	if(moveDown){
		if(this->y >= Constants::SCREEN_HEIGHT - this->height){
			this->y = Constants::SCREEN_HEIGHT - this->height*2;
		}
		else{
			this->y+= Constants::SPEED_Y * dt;
		}
	}
	else if(moveUp){
		if(this->y <= 0){
			this->y = 0;
		}
		else{
			this->y-=Constants::SPEED_Y * dt;
		}
	}
	if(moveRight){
		if(this->x >= Constants::SCREEN_WIDTH - this->width){
			this->x = Constants::SCREEN_WIDTH - this->width*2;
		}
		else{
			this -> x += Constants::SPEED_X * dt;
		}
	}
	else if(moveLeft){
		if(this->x <= 0){
			this->x = 0;
		}
		else{
			this->x-= Constants::SPEED_X * dt;
		}
	}
}