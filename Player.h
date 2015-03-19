#include <SDL/SDL.h>
#include "Sprite.h"

class Player : public Sprite{
	double speedX;
	double speedY;
	bool hasBall;
	bool team;

	//Remove these eventually (maybe)
	bool mUp, mDown, mLeft, mRight;


public:
	Player(double speed, bool team, int width, int height) : Sprite(width, height){
		//Set  values for x,y and set default movement to not move
		this->speed = speed;
		this->team = team;

		mUp=false;
		mDown=false;
		mLeft=false;
		mRight=false;
	}


	//Change boolean values of whether or not to move in that direction based on key input
	void moveUp(bool m){
		mUp = m;
	}

	void moveDown(bool m){
		mDown = m;
	}

	void moveLeft(bool m){
		mLeft = m;
	}

	void moveRight(bool m){
		mRight =m;
	}

	//Once per loop this is called to move in the directions it's supposed to

	void move(float dt){

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


};