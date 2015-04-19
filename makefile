all: Project
	
Project: Sprite.o Player.o Ball.o Goal.o Map.o  Game.o GameEngine.o

	g++ Game.cpp GameEngine.cpp Player.cpp Sprite.cpp Ball.cpp Goal.cpp Map.cpp  -w -lSDL -lSDL_image -o Game
	
Sprite.o: Sprite.cpp
	g++ -c Sprite.cpp -w -lSDL -lSDL_image

Player.o: Player.cpp
	g++ -c Player.cpp -w -lSDL -lSDL_image

Ball.o: Ball.cpp
	g++ -c Ball.cpp -w -lSDL -lSDL_image

Goal.o: Goal.cpp
	g++ -c Goal.cpp -w -lSDL -lSDL_image

Map.o: Map.cpp
	g++ -c Map.cpp -w -lSDL -lSDL_image

GameEngine.o: GameEngine.cpp
	g++ -c GameEngine.cpp -w -lSDL -lSDL_image
clean:
	rm -rf *o *gch *stackdump Project
