#include <SDL/SDL.h>
#include "Sprite.cpp"
#include "FrictionZone.cpp"
#include "Goals.cpp"

Class Map : public Sprite{
private:
	SDL_Surface* background;;
	Goal goals[];
	FrictionZone frictionZones[];	

public:
	Map(int width, int height, char* File, Goal goals[], FrictionZone frictionZones[]) : Sprite(width, height){
		
		//load the background image
		//This is probably not going to work so figure it out later
		this->Load(File);
		background = returnASurface(File);
		this->goals = goals;
		this->frictionZones = frictionZones;
	}

	SDL_Surface* updateDisplay(Player players[], Ball ball){
		//update screen
		
		//blank slate
		this->Draw(surface, background, 0,0);

		//Display all goals and friction zones
		for(int i = 0; i < goals.size(); i++){
			this->Draw(this->surface, goals[i], goals[i].getX(), goals[i].getY());
		}
		for(int i=0; i < frictionZones.size(); i++){
			this->Draw(this->surface, frictionZones[i], frictionZones[i].getX(), frictionZones[i].getY());
		}

		//Display all the players
		for(int i=0; i < players.size(); i++){
			this->Draw(this->surface, players[i], players[i].getX(), players[i].getY());
		}

		//Display the ball
		this->Draw(this->surface, ball, ball.getX(), ball.getY());

		return this->surface;	
	}

}