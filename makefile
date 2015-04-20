all: Project
	
Project: Sprite.o Music.o Player.o Ball.o Goal.o Map.o  Game.o GameEngine.o

	g++ Game.cpp Music.cpp GameEngine.cpp Player.cpp Sprite.cpp Ball.cpp Goal.cpp Map.cpp  -w -lSDL -lSDL_image -lSDL_mixer -o Game
	
Sprite.o: Sprite.cpp
	g++ -c Sprite.cpp -w -lSDL -lSDL_image -lSDL_mixer

Player.o: Player.cpp
	g++ -c Player.cpp -w -lSDL -lSDL_image	-lSDL_mixer

Ball.o: Ball.cpp
	g++ -c Ball.cpp -w -lSDL -lSDL_image -lSDL_mixer

Goal.o: Goal.cpp
	g++ -c Goal.cpp -w -lSDL -lSDL_image	-lSDL_mixer

Map.o: Map.cpp
	g++ -c Map.cpp -w -lSDL -lSDL_image	-lSDL_mixer

GameEngine.o: GameEngine.cpp
	g++ -c GameEngine.cpp -w -lSDL -lSDL_image -lSDL_mixer

Music.o: Music.cpp
	g++ -c Music.cpp -w -lSDL -lSDL_image -lSDL_mixer
	
clean:
	rm -rf *o *gch *stackdump Project
