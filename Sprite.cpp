#include <SDL/SDL.h>
#include "Sprite.h"
#include <iostream>

//Constructor
Sprite::Sprite(int width, int height){
	this->width = width;
	this->height = height;
}

int Sprite::getX(){
	return x;
}

int Sprite::getY(){
	return y;
}

void Sprite::setX(int x){
	this->x = x;
}

void Sprite::setY(int y){
	this->y = y;
}

int Sprite::getWidth(){
	return width;
}

int Sprite::getHeight(){
	return height;
}

SDL_Surface* Sprite::getSurface(){
	return surface;
}

//Overload to return a surface or set it as a class attribute
void Sprite::Load(char* File){
	//Create two temporary pointers to surfaces
	SDL_Surface* temp = NULL;
	SDL_Surface* optimized = NULL;

	//Make sure that the file exists
	if((temp = SDL_LoadBMP(File)) == NULL){
		std::cout << "The file path does not exist" << std::endl;
		this->surface = NULL;
	}

	//convert the image to an optimize form 
	optimized = SDL_DisplayFormatAlpha(temp);
	this->surface = optimized;

	//free temp
	SDL_FreeSurface(temp);
}
//returns a surface
SDL_Surface* Sprite::returnASurface(char* File){
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

void Sprite::Draw(SDL_Surface* dest, Sprite sprite, int x, int y){

   SDL_Surface* src = sprite.getSurface();
   SDL_Rect  destR;

   destR.x = sprite.getX();
   destR.y = sprite.getY();

   SDL_Rect srcR;

   srcR.x = sprite.getX();
   srcR.y = sprite.getY();
   srcR.w = sprite.getWidth();
   srcR.h = sprite.getHeight();

   SDL_BlitSurface(src, &srcR, dest, &destR);
}
void Sprite::Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y){

   SDL_Rect  destR;

   destR.x = x;
   destR.y = y;


   SDL_BlitSurface(src, NULL, dest, &destR);
}

bool Sprite::checkCollision(Sprite s1, Sprite s2){
	//initialize variables for the rectangle
	int left1, right1, up1, bottom1;
	int left2, right2, up2, bottom2;

	//Calculate the bounds for the first sprite
	left1 = s1.x;
	right1 = s1.x + s1.width;
	up1 = s1.y;
	bottom1 = s1.y + s1.height;

	//Calculate the bounds for the second sprite
	left2 = s2.x;
	right2 = s2.x + s2.width;
	up2 = s2.y;
	bottom2 = s2.y + s2.height;

	//determine if any collosions are happending
	if(left1 >= right2){
		return false;
	}
	if(right1 <= left2){
		return false;
	}
	if(up1 >= bottom2){
		return false;
	}
	if(bottom1 <= up2){
		return false;
	}
	return true;
}

