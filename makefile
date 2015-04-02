all: Project
	
Project: Sprite.o Player.o Ball.o Goal.o Map.o Controller.o Game.o 
	g++ Game.cpp Player.cpp Sprite.cpp Ball.cpp Goal.cpp Map.cpp Controller.cpp -w -lSDL -o Game
Sprite.o: Sprite.cpp
	g++ -c Sprite.cpp -w -lSDL

Player.o: Player.cpp
	g++ -c Player.cpp -w -lSDL

Ball.o: Ball.cpp
	g++ -c Ball.cpp -w -lSDL

Goal.o: Goal.cpp
	g++ -c Goal.cpp -w -lSDL

Map.o: Map.cpp
	g++ -c Map.cpp -w -lSDL

Controller.o: Controller.cpp
	g++ -c Controller.cpp -w -lSDL

clean:
	rm -rf *o *gch *stackdump Project