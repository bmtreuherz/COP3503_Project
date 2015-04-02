#include <SDL/SDL.h>
#include "Sprite.h"
#include "Constants.h"


#ifndef PLAYER_H
#define PLAYER_H

class Player : public Sprite{
	double speed;
	bool hasBall;
	bool team;




public:
	Player(double speed, bool team, int width, int height) : Sprite(width, height){
		//Set  values for x,y and set default movement to not move
		this->speed = speed;
		this->team = team;
		this->hasBall = false;

		moveUp=false;
		moveDown=false;
		moveLeft=false;
		moveRight=false;
	}

	//MAKE THESE PRIVATE AFTER TESTING

	bool moveUp, moveDown, moveLeft, moveRight;
	/*
	void shootBall(Ball b);

	void captureBall();
	*/

	//Once per loop this is called to move in the directions it's supposed to
	void move(float dt);
};
#endif