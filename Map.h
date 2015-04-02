#include <SDL/SDL.h>
#include "Sprite.h"
#include "Goal.h"
#include "Player.h"
#include "Ball.h"

class Map : public Sprite{
private:
	SDL_Surface* background;
	Goal* goals;

public:
	Map(int width, int height, char* File, Goal* goals) : Sprite(width, height){
		
		//load the background image
		//This is probably not going to work so figure it out later
		this->Load(File);
		background = returnASurface(File);
		this->goals = goals;
	}

	SDL_Surface* updateDisplay(Player players[], Ball ball);
};