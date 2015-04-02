#include <SDL/SDL.h>
#include "Sprite.h"
#include "Player.h"

#ifndef BALL_H
#define BALL_H

class Ball : public Sprite{
	double speed;
	//Player* captor;

public:
	Ball(double speed, int width, int height) : Sprite(width, height){
		this->speed = speed;
		//captor = NULL;

	}
	~Ball(){
		//delete[] captor;
	}

	void move();
	//void getcaptures(Player capture);
	void getshot(double theta);
};
#endif