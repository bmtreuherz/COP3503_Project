#include <SDL/SDL.h>

class Timer{
	float lastTime;
	float currentTime;
public:
	Timer(){
		float lastTime = SDL_GetTicks();
	}

	float getDT(){
		currentTime = SDL_GetTicks();
		float dt = (currentTime - lastTime);
		lastTime = currentTime;
		return dt;
	}
};