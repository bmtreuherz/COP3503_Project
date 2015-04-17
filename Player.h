#include <SDL/SDL.h>
#include "Sprite.h"


#ifndef PLAYER_H
#define PLAYER_H

class Player : public Sprite{
	double speed;
	bool hasBall;
	bool team;
	double speedMult;




public:
	Player(double speed, bool team, int width, int height) : Sprite(width, height){
		//Set  values for x,y and set default movement to not move
		this->speed = speed;
		this->team = team;
		this->hasBall = false;
		speedMult = 1;

		moveX=0;
		moveY=0;
	}

	//MAKE THESE PRIVATE AFTER TESTING

	double moveX, moveY;
	/*
	void shootBall(Ball b);
*/
	void captureBall(bool cap);
	
	bool getBall();
	//Once per loop this is called to move in the directions it's supposed to
	void move(float dt);
};
#endif