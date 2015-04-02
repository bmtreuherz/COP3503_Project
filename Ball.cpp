#include <SDL/SDL.h>
#include "Ball.h"
#include "Sprite.h"

void Ball::move(double dt){


	this->x += speedX * dt;
	this->y += speedY * dt;

	if(this->x >= Constants::SCREEN_WIDTH - this->width || this-> x <=0){
		speedX *= -1;
	}
	if(this->y >= Constants::SCREEN_HEIGHT - this->height || this-> y <=0){
		speedY *= -1;
	}	


}
/*
void Ball::getcaptures(Player capture){

}
*/

void Ball::getshot(double theta){
	//todo: implement
}
