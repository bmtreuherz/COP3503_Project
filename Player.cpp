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
	
	if(moveY>0){
		if(this->y >= SCREEN_HEIGHT - this->height){
			this->y = SCREEN_HEIGHT - this->height;
		}
		else{
			this->y += speed * dt;
		}
	}
	else if(moveY <0){
		if(this->y <=0){
			this->y = 0;
		}
		else{
			this->y -= speed * dt;
		}
	}

	if(moveX >0){
		if(this->x >= SCREEN_WIDTH - this->width){
			this->x = SCREEN_WIDTH - this->width;
		}
		else{
			this->x += speed * dt;
		}
	}
	else if(moveX < 0){
		if(this->x <=0){
			this->x = 0;
		}
		else{
			this->x -= speed * dt;
		}
	}

}