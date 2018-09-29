#include <GL\glew.h>

#include "Window.h"
#include "Error.h"

Window::Window()
{
}

Window::~Window()
{
}

int Window::create(string _windowName, 
	int _screenWidth, 
	int _screenHeight, 
	unsigned int currentFlags) {
	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISIBLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}

	if (currentFlags & FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (currentFlags & BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	window = SDL_CreateWindow(
		_windowName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screenWidth,
		screenHeight,
		flags
	);

	if (window == nullptr) {
		fatalError("Window could not be initialized");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Glew was not initialized");
	}
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	return 0;
}

void Window::swapWindow() {
	SDL_GL_SwapWindow(window);
}
