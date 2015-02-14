#include <SDL/SDL.h>

class Player{
private:
	int x;
	int y;
	SDL_Surface* surface;
	bool mUp, mDown, mLeft, mRight;
	//TODO: add more stuff like health, lifes, whatever

public:
	Player(int x, int y, SDL_Surface* surface);

	int getX();

	int getY();

	SDL_Surface* getSurface();


	//implement this with speed and framerate
	void moveUp(bool m);

	void moveDown(bool m);

	void moveLeft(bool m);

	void moveRight(bool m);

	void move();

	//TODO: add more functionality

};