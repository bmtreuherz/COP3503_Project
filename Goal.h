#include <SDL/SDL.h>
#include "Sprite.h"

#ifndef GOAL_H
#define GOAL_H

class Goal: public Sprite{
protected:
	bool team;
	int score;
	Sprite* fillGoal;

public:
	Goal(bool team, int width, int height, char* File) : Sprite(width, height){
		score = 0;
		this->team = team;
		Sprite* temp = new Sprite(width/10, height/10);
		temp->Load(File);
		temp->setX(-1);
		temp->setY(-1);
		fillGoal = temp;

	}

	void incrementScore();

	int getScore();

};
#endif