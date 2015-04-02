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
	Goal(bool team, int width, int height) : Sprite(width, height){
		this->team = team;
		if (team){
			Sprite s(width / 10, height / 10);
			s.Load("lib/red.bmp");
			fillGoal = &s;
		}
		else{
			Sprite s(width / 10, height / 10);
			s.Load("lib/purple.bmp");
			fillGoal = &s;
		}
	}
	void incrementScore(bool hasBall);

};
#endif