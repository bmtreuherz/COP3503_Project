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

    if(score % 12 == 0){
        this->fillGoal->setX(this->fillGoal->getX() + this->fillGoal->getWidth());
    }
    if(this->fillGoal->getX() >= this->getX()+this->getWidth()){
        this->fillGoal->setX(this->getX());
        this->fillGoal->setY(this->fillGoal->getY() + this->fillGoal->getHeight());
    }    
}

int Goal::getScore(){
    return score;
}

void Goal::setScore(int score){
    this->score = score;

}

Sprite* Goal::getFillGoal(){
    return fillGoal;
}

int Goal::getFillX(){
    return fillGoal->getX();
}
int Goal::getFillY(){
    return fillGoal->getY();
}

