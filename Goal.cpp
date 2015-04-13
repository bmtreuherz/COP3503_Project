#include <SDL/SDL.h>
#include "Sprite.h"
#include "Goal.h"
#include <stdint.h>
#include <iostream>


void Goal::incrementScore(){	
    score++;

    if(fillGoal->getX() == -1){
        fillGoal->setX(this->getX());
        fillGoal->setY(this->getY());
    }

    std::cout<<"GOAL "<<this->team <<"SCORE: "<<score<<std::endl;

    if(score % 10 == 0){
        this->fillGoal->setX(this->fillGoal->getX() + this->fillGoal->getWidth());
    }
    if(this->fillGoal->getX() >= this->getX()+this->getWidth()){
        this->fillGoal->setX(this->getX());
        this->fillGoal->setY(this->fillGoal->getY() + this->fillGoal->getHeight());
    }

    Draw(this->surface, *this->fillGoal, 0,0);
    

}

int Goal::getScore(){
    return score;
}

