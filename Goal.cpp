#include <SDL/SDL.h>
#include "Sprite.h"
#include "Goal.h"

void Goal::incrementScore(bool hasBall){
	if(hasBall){
		score++;
		if(score % 10 == 1){
			Sprite::Draw(this->surface, fillGoal->getSurface(), 0, this->height/10 * (score / 10));
		}
		else{
			Sprite::Draw(this->surface, fillGoal->getSurface(), this->width/10 * (score % 10), this->height * (score / 10));
		}
	}	
}
