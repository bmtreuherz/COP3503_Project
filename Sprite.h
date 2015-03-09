#include <SDL/SDL.h>

class Sprite {

public:
	Sprite();

	static SDL_Surface* Load(char* pFile);

	static bool Draw(SDL_Surface* dest, SDL_Surface* src, int x,int y );;


};