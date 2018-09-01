#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLS_Program.h"

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
	float time;
	Sprite sprite;
	GLS_Program program;
	void processInput();

public:
	MainGame();
	~MainGame();
	GameState state;
	void run();
	void draw();
	void update();
	void initShaders();
};