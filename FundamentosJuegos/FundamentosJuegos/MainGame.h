#pragma once
#include <vector>
#include <SDL\SDL.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLS_Program.h"
#include "Camera2D.h"
#include "Window.h"
#include "SpriteBatch.h"
#include "Level.h"

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
	vector<Level*> levels;
	GLS_Program program;
	Camera2D camera2D;
	void processInput();
	SpriteBatch spriteBatch;

	int _currentLevel;
	void initLevel();

public:
	MainGame();
	~MainGame();
	GameState state;
	void run();
	void draw();
	void update();
	void initShaders();
};