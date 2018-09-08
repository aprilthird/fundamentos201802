#include <iostream>

#include "MainGame.h"
#include "Error.h"

using namespace std;

MainGame::MainGame() : 
	window(nullptr), 
	width(800), 
	height(600), 
	state(GameState::PLAY) {
}

MainGame::~MainGame() {

}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
		"Pantalla 1",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) {
		//mostrar mensaje de error
		fatalError("Window could not be initialized");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//mostrar mensaje de error de Glew
		fatalError("Glew could not be initialized");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
}

void MainGame::run() {
	init();
	time = 0;
	sprites.push_back(new Sprite());
	sprites.back()->init(-1, -1, 1, 1, "Images/Imagen1.png");
	sprites.push_back(new Sprite());
	sprites.back()->init(0, -1, 1, 1, "Images/Imagen1.png");
	initShaders();
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
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time); // de tipo f por el tipo de dato float
	time += 0.0002;
	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	for (size_t i = 0; i < sprites.size(); ++i) {
		sprites[i]->draw();
	}
	program.unuse();
	SDL_GL_SwapWindow(window);
}

void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			state = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << event.motion.x << ", " << event.motion.y << endl;
			break;
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
