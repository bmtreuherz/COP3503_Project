#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "Music.h"

Music::Music(){
	gameSong = NULL;
	titleScreen = NULL;
	startSound = NULL;
	switchTeam = NULL;
	selectTeam = NULL;
	deselectTeam = NULL;
	shoot = NULL;
	steal = NULL;
	ballCollision = NULL;
	fillGoal = NULL;
	chooseMenu = NULL;
}

void Music::initAudio(){
	this->gameSong = Mix_LoadMUS("lib/sounds/gamesong.wav");
	this->titleScreen = Mix_LoadMUS("lib/sounds/titlescreen.wav");
	this->startSound = Mix_LoadWAV("lib/sounds/startsound.wav");
	this->switchTeam = Mix_LoadWAV("lib/sounds/switchteam.wav");
	this->selectTeam = Mix_LoadWAV("lib/sounds/selectteam.wav");
	this->deselectTeam = Mix_LoadWAV("lib/sounds/deselectteam.wav");

	this->shoot = Mix_LoadWAV("lib/sounds/shoot.wav");
	this->steal = Mix_LoadWAV("lib/sounds/steal.wav");
	this->ballCollision = Mix_LoadWAV("lib/sounds/ballcollision.wav");
	this->fillGoal = Mix_LoadWAV("lib/sounds/fillgoal.wav");
	this->chooseMenu = Mix_LoadWAV("lib/sounds/choosemenu.wav");
}


void Music::freeAudio(){
	Mix_FreeMusic(gameSong);
	Mix_FreeMusic(titleScreen);
	Mix_FreeChunk(startSound);
	Mix_FreeChunk(switchTeam);
	Mix_FreeChunk(selectTeam);
	Mix_FreeChunk(deselectTeam);
	Mix_FreeChunk(shoot);
	Mix_FreeChunk(steal);
	Mix_FreeChunk(ballCollision);
	Mix_FreeChunk(fillGoal);
	Mix_FreeChunk(chooseMenu);
}

Mix_Chunk* Music::getChooseMenu(){
	return chooseMenu;
}
Mix_Chunk* Music::getShoot(){
	return shoot;
}
Mix_Chunk* Music::getSteal(){
	return steal;
}
Mix_Chunk* Music::getBallCollision(){
	return ballCollision;
}
Mix_Chunk* Music::getFillGoal(){
	return fillGoal;
}


Mix_Music* Music::getGameSong(){
	return gameSong;
}
Mix_Music* Music::getTitleScreen(){
	return titleScreen;
}

Mix_Chunk* Music::getStartSound(){
	return startSound;
}

Mix_Chunk* Music::getSwitchTeam(){
	return switchTeam;
}

Mix_Chunk* Music::getSelectTeam(){
	return selectTeam;
}

Mix_Chunk* Music::getDeselectTeam(){
	return deselectTeam;
}


