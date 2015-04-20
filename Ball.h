#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "Music.h"
#include "Sprite.h"
#include "Player.h"


#ifndef BALL_H
#define BALL_H

class Ball : public Sprite{
	double speedMax;
	double speedX;
	double speedY;
	Player* captor;
	double theta;
	bool capturable;
	int count;

public:
	Ball(double speed, int width, int height) : Sprite(width, height){
		this->speedMax = speed;
		this->speedX = 0;
		this->speedY = 0;
		captor = NULL;
		theta = 0;
		capturable = true;
		count = 0;


	}

	void move(double dt, int screenWidth, int screenHeight, Mix_Chunk* hitWall);
	void getCaptured(Player* captor);
	Player* getCaptor();
	void getShot(double theta);
	bool isCapturable();
};
#endif