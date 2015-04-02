#include <SDL/SDL.h>
#include "Sprite.h"
#include "Player.h"

#ifndef BALL_H
#define BALL_H

class Ball : public Sprite{
	float speedX;
	float speedY;
	//Player* captor;

public:
	Ball(float speed, int width, int height) : Sprite(width, height){
		this->speedX = speed;
		this->speedY = speed;
		//captor = NULL;

	}
	~Ball(){
		//delete[] captor;
	}

	void move(double dt);
	//void getcaptures(Player capture);
	void getshot(double theta);
};
#endif