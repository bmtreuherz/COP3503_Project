#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#ifndef MUSIC_H
#define MUSIC_H

class Music{
	Mix_Music *gameSong;
	Mix_Music *titleScreen;

	Mix_Chunk *startSound;
	Mix_Chunk *switchTeam;
	Mix_Chunk *selectTeam;
	Mix_Chunk *deselectTeam;

	Mix_Chunk *shoot;
	Mix_Chunk *steal;
	Mix_Chunk *ballCollision;
	Mix_Chunk *fillGoal;
	Mix_Chunk *chooseMenu;


public:
	Music();
	void initAudio();
	void freeAudio();

	Mix_Music* getGameSong();
	Mix_Music* getTitleScreen();
	Mix_Chunk* getStartSound();
	Mix_Chunk* getSwitchTeam();
	Mix_Chunk* getSelectTeam();
	Mix_Chunk* getDeselectTeam();

	Mix_Chunk* getShoot();
	Mix_Chunk* getSteal();
	Mix_Chunk* getBallCollision();
	Mix_Chunk* getFillGoal();
	Mix_Chunk* getChooseMenu();
};

#endif