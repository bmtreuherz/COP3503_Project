#include <SDL/SDL.h>

class Sprite {

public:
	Sprite();

	static SDL_Surface* Load(char* pFile);

	static bool Draw(SDL_Surface* dest, SDL_Surface* src, int x,int y );

	static bool Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y, int x2, int y2, int width, int height);


};