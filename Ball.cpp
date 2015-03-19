#include "SDL/SDL.h"
#include "Sprite.cpp"

class Ball : public Sprite{
	double speed;
	Player captor;

public:
	Ball(double speed, int width, int height) : Sprite(width, height){
		this->speed = speed;
	}
	void move(){
		//TODO: implement
	}
	void getCaptures(Player capture){

	}

	void getShot(double theta){
		//TODO: implement
	}
};
