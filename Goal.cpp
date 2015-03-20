

class Goal: public Sprite{
protected:
	bool team;
	int score;
	Sprite fillGoal;
public:
	Goals(bool team, int width, int height) : Sprite(width, height){
		this->team = team;
		if(team){
			Sprite s(width/10, height/10);
			s.load("lib/lightGreen");
			fillGoal = s;
		}
		else{
			Sprite s(width/10, height/10);
			s.load("lib/lightPink");
			fillGoal = s
		}

	}
	void incrementScore(bool hasBall){
		if(hasBall && team == true){
			score++;
			if(score % 10 == 1){
				Sprite::Draw(Goal.getSurface, fillGoal, 0, fillGoal.height * (score / 10));
			}
			else{
				Sprite::Draw(Goal.getSurface, fillGoal, fillGoal.width * (score % 10), fillGoal.height * (score / 10))
			}
		}
	}

};
