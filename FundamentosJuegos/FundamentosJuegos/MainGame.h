#pragma once
#include <vector>
#include <SDL\SDL.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLS_Program.h"
#include "Camera2D.h"
#include "Window.h"

enum class GameState
{
	PLAY, EXIT
};

class MainGame {
private:
	int width;
	int height;
	void init();
	Window window;
	float time;
	vector<Sprite*> sprites;
	GLS_Program program;
	Camera2D camera2D;
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