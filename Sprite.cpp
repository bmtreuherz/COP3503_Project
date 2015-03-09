#include <SDL/SDL.h>
#include "Sprite.h"
#include <iostream>

//Constructor
Sprite::Sprite(){
}
<<<<<<< HEAD
//Overload this method to create rectagles
=======

<<<<<<< HEAD
//Overload this method to create rectagles
=======
>>>>>>> 9a289092e58439612a755c1c6e6377699ab95fa4
>>>>>>> 4246eb03f323f5da4c103d196e69f53bf45dff2b
SDL_Surface* Sprite::Load(char* File){
	//Create two temporary pointers to surfaces
	SDL_Surface* temp = NULL;
	SDL_Surface* optimized = NULL;


	//Make sure that the file exists
	if((temp = SDL_LoadBMP(File)) == NULL){
		std::cout << "The file path does not exist" << std::endl;
		return NULL;
	}

	//convert the image to an optimize form 
	optimized = SDL_DisplayFormatAlpha(temp);

	//free temp
	SDL_FreeSurface(temp);

	return optimized;
}

bool Sprite::Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y)
{
  if(dest == NULL || src == NULL)
   {
			  return false;
   }

   SDL_Rect  destR;

   destR.x = x;
   destR.y = y;

   SDL_BlitSurface(src, NULL, dest, &destR);
   
	return true;
}

