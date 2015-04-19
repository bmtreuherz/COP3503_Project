#include <SDL/SDL.h>

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
protected:
	int x;
	int y;
	int width;
	int height;
	SDL_Surface* surface;
	bool ready;

public:
	Sprite(int width, int height);
	
	//Accessor methods
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	int getWidth();
	int getHeight();
	SDL_Surface* getSurface();


	void Load(char* File);
	SDL_Surface* returnASurface(char* File);
	void Draw(SDL_Surface* dest, Sprite s);
	void Draw(SDL_Surface* dest, SDL_Surface* src, int x,int y );
	int checkCollision(Sprite other);
	bool isReady();
	void setReady(bool ready);

};
#endif