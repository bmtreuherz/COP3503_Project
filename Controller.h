#include <SDL/SDL.h>
#include "Player.h"

class Controller{
	Player* player;
	SDL_Joystick* stick;

public:
	Controller(Player* player);
	~Controller();
	void loadController(SDL_Joystick* stick);
	void handleEvent(SDL_Event &event);
};