#include <iostream>

#include "MainGame.h"
#include "Error.h"
#include "ResourceManager.h"
#include "Engine.h"

using namespace std;

MainGame::MainGame() : 
	width(800), 
	height(600), 
	time(0),
	state(GameState::PLAY) {
	camera2D.init(width, height);
}

MainGame::~MainGame() {

}

void MainGame::init() {
	FD08::init();
	window.create("Sprite Batch", width, height, 0);
	initShaders();
	spriteBatch.init();
}

void MainGame::initLevel() {
	_currentLevel = 0;
	levels.push_back(new Level("Levels/level1.txt"));
}

void MainGame::run() {
	init();
	update();
}

void MainGame::update() {
	while (state != GameState::EXIT) {
		processInput();
		draw();
		camera2D.update();
		time += 0.002f;
	}
}

void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation = program.getUniformLocation("P");
	glm::mat4 cameraMatrix = camera2D.getCameraMatrix();
	
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	/*GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);*/ // de tipo f por el tipo de dato float

	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	spriteBatch.begin();
	glm::vec4 position(0.0f, 0.0f, 100.0f, 100.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	static GLTexture texture = ResourceManager::getTexture("Textures/ejemplo.png");
	ColorRGBA color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	spriteBatch.draw(position, uv, texture.id, 0.0f, color);
	spriteBatch.draw(position + glm::vec4(50.0, 0.0, 0.0, 0.0), uv, texture.id, 0.0f, color);

	spriteBatch.end();
	spriteBatch.renderBatch();

	//time += 0.002;

	program.unuse();
	window.swapWindow();
}

void MainGame::processInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float CAMERA_SCALE = 0.1f;

	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			state = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//cout << event.motion.x << ", " << event.motion.y << endl;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				camera2D.setPosition(
					camera2D.getPosition() - glm::vec2(0.0, CAMERA_SPEED)
				);
				break;
			case SDLK_s:
				camera2D.setPosition(
					camera2D.getPosition() + glm::vec2(0.0, CAMERA_SPEED)
				); 
				break;
			case SDLK_a:
				camera2D.setPosition(
					camera2D.getPosition() - glm::vec2(CAMERA_SPEED, 0.0)
				);
				break;
			case SDLK_d:
				camera2D.setPosition(
					camera2D.getPosition() + glm::vec2(CAMERA_SPEED, 0.0)
				);
				break;
			case SDLK_q:
				camera2D.setScale(
					camera2D.getScale() + CAMERA_SCALE
				);
				break;
			case SDLK_e:
				camera2D.setScale(
					camera2D.getScale() - CAMERA_SCALE
				);
				break;
			}
		}
	}
}

void MainGame::initShaders() {
	program.compileShaders("Shaders/colorShaderVertex.txt", "Shaders/colorShaderFragment.txt");
	program.addAttribut("vertexPosition");
	program.addAttribut("vertexColor");
	program.addAttribut("vertexUV");
	program.linkShader();
}
