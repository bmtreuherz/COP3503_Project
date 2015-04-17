#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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
	if((temp = IMG_Load(File)) == NULL){
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

void Sprite::Draw(SDL_Surface* dest, Sprite sprite){

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

//return -1 if kno collission, 0 for top, 1 for right, 2 for bottom, 3 for left
int Sprite::checkCollision(Sprite other){
	//initialize variables for the rectangle
	int left1, right1, up1, bottom1;
	int left2, right2, up2, bottom2;

	//Calculate the bounds for the first sprite
	left1 = this->x;
	right1 = this->x + this->width;
	up1 = this->y;
	bottom1 = this->y + this->height;

	//Calculate the bounds for the second sprite
	left2 = other.x;
	right2 = other.x + other.width;
	up2 = other.y;
	bottom2 = other.y + other.height;


	//determine if any collosions are happending
	if(left1 >= right2){
		return -1;
	}
	if(right1 <= left2){
		return -1;
	}
	if(up1 >= bottom2){
		return -1;
	}
	if(bottom1 <= up2){
		return -1;
	}

	//determine where the collision occured

	//collision with the left side
	if(left1 > left2){
		//collision with the bottom
		if(up1 < up2){
			//whichever direction has the smallest differece indicates the direction the user was trying to go
			//user was moving down. 
			if((bottom1-up2)<(right2-left1)){
				return 2;
			}
			//user was moving left 
			else{
				return 3;
			}

		}
		//collision with the top or 
		else if(up1 > up2){
			//user was moving up
			if((bottom2-up1)<(right2-left1)){
				return 0;
			}

			//user was moving left
			else{
				return 3;
			}
		}
		//rare case that it is only a side collision
		else{
			return 3;
		}
	}
	//collision with the right side
	else if(left1 < left2){
		//collision with the bottom
		if(up1 < up2){

			//player was moving down
			if((bottom1-up2)<(right1-left2)){
				return 2;
			}
			//player was moving right
			else{
				return 1;
			}
		}
		//collision with the top or 
		else if(up1 > up2){

			//user was moving up
			if((bottom2-up1)<(right1-left2)){
				return 0;
			}

			//user was moving right 
			else{
				return 1;
			}
		}
		//rare case that it is only a side collision
		else{
			return 1;
		}
	}

	//rare case where the collision occurs only with the top
	else{
		//bottom collision
		if(up1 < up2){
			return 2;
		}
		//top collision
		else{
			return 0;
		}	
	}
}
