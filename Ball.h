#include <SDL/SDL.h>
#include "Sprite.h"
#include "Player.h"


#ifndef BALL_H
#define BALL_H

class Ball : public Sprite{
	double speedX;
	double speedY;
	Player* captor;

public:
	Ball(double speed, int width, int height) : Sprite(width, height){
		this->speedX = speed;
		this->speedY = speed;
		captor = NULL;

	}
	~Ball(){
		//delete[] captor;
	}

	void move(double dt);
	void getCaptured(Player* captor);
	Player* getCaptor();
	void getshot(double theta);
};
#endif