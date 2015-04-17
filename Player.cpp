#include <SDL/SDL.h>
#include "Sprite.h"
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

	if(hasBall){
		speedMult = 0.8;
	}
	else{
		speedMult = 1;
	}

	if(moveY>0){
		this->y += speedMult * speed * dt;
	}
	else if(moveY <0){
		this->y -= speedMult * speed * dt;
	}

	if(moveX >0){
		this->x += speedMult * speed * dt;
}
	else if(moveX < 0){
		this->x -= speedMult * speed * dt;
	}

}
void Player::captureBall(bool cap){
	hasBall = cap;
}

bool Player::getBall(){
	return hasBall;
}