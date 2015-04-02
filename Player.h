#include <SDL/SDL.h>
#include "Sprite.h"
#include "Constants.h"


#ifndef PLAYER_H
#define PLAYER_H

class Player : public Sprite{
	double speed;
	bool hasBall;
	bool team;

	//Remove these eventually (maybe)
	bool mUp, mDown, mLeft, mRight;


public:
	Player(double speed, bool team, int width, int height) : Sprite(width, height){
		//Set  values for x,y and set default movement to not move
		this->speed = speed;
		this->team = team;
		this->hasBall = false;

		mUp=false;
		mDown=false;
		mLeft=false;
		mRight=false;
	}
	/*
	void shootBall(Ball b);

	void captureBall();
	*/

	//Change the movement a lot
	//Change boolean values of whether or not to move in that direction based on key input
	void moveUp(bool m);

	void moveDown(bool m);
	void moveLeft(bool m);
	void moveRight(bool m);
	//Once per loop this is called to move in the directions it's supposed to
	void move(float dt);
};
#endif