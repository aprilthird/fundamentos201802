#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>

enum class GameState
{
	PLAY, EXIT
};

class MainGame {
private:
	int width;
	int height;
	void init();
	SDL_Window* window;
	void processInput();

public:
	MainGame();
	~MainGame();
	GameState state;
	void run();
	void draw();
	void update();
};