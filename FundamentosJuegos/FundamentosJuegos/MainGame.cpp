#include <iostream>

#include "MainGame.h"
#include "Error.h"

using namespace std;

MainGame::MainGame() : 
	width(800), 
	height(600), 
	state(GameState::PLAY) {
	camera2D.init(width, height);
}

MainGame::~MainGame() {

}

void MainGame::init() {
	window.create("Camera2d", width, height, 0);
	initShaders();
}

void MainGame::run() {
	init();
	sprites.push_back(new Sprite());
	sprites.back()->init(-1, -1, 1, 1, "Images/Imagen1.png");
	sprites.push_back(new Sprite());
	sprites.back()->init(0, -1, 1, 1, "Images/Imagen1.png");
	update();
}

void MainGame::update() {
	while (state != GameState::EXIT) {
		draw();
		processInput();
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

	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time); // de tipo f por el tipo de dato float
	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	time += 0.002;
	for (size_t i = 0; i < sprites.size(); ++i) {
		sprites[i]->draw();
	}
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
