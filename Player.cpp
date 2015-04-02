#include <SDL/SDL.h>
#include "Sprite.h"
#include "Constants.h"
#include "Player.h"



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
void Player::moveUp(bool m){
	mUp = m;
}

void Player::moveDown(bool m){
	mDown = m;
}

void Player::moveLeft(bool m){
	mLeft = m;
}

void Player::moveRight(bool m){
	mRight =m;
}

//Once per loop this is called to move in the directions it's supposed to
void Player::move(float dt){

	if(mDown){
		this->y+= Constants::SPEED_Y * dt;
	}
	else if(mUp){
		this->y-=Constants::SPEED_Y * dt;
	}
	if(mRight){
		this -> x += Constants::SPEED_X * dt;
	}
	else if(mLeft){
		this->x-= Constants::SPEED_X * dt;
	}
}