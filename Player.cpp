#include <SDL/SDL.h>
#include "Player.h"

//Constructor
Player::Player(int x, int y, SDL_Surface* surface){
	//Set  values for x,y and set default movement to not move
	this->x = x;
	this ->y =y;

	mUp=false;
	mDown=false;
	mLeft=false;
	mRight=false;

	this-> surface = surface;
}

//Get the X and Y position of the player
int Player::getX(){
	return this->x;
}

int Player::getY(){
	return this->y;
}

//Return the surface that represents the player
SDL_Surface* Player::getSurface(){
	return this->surface;
}

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
void Player::move(){
	if(mRight){
		this->x+=1;
	}
	else if(mLeft){
		this->x-=1;
	}
	if(mUp){
		this->y-=1;
	}
	else if(mDown){
		this->y+=1;

	}
}
