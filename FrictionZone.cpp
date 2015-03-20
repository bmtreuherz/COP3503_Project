class FrictionZone{
private:
	double friction;

public:
	FrictionZone(double friction, int width, int height) : Sprite(width, height){
		this->friction = friction;
	}

	double getFriction(){return friction}
	
	void applyFriction(Player player, bool collide){
		if(collides)
			player.speed = player.speed * friction;
		}
		else{
			player.speed = PLAYER_SPEED;
		}
};
