#pragma once
#include <GL\glew.h>

struct Position {
	float x;
	float y;

	void set(float _x, float _y) {
		this->x = _x;
		this->y = _y;
	}
};

struct ColorRGBA {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;

	void set
	(	
		GLubyte _r,
		GLubyte _g,
		GLubyte _b,
		GLubyte _a
	) {
		this->r = _r;
		this->g = _g;
		this->b = _b;
		this->a = _a;
	}
};

struct Vertex {
	Position position;
	ColorRGBA colorRGBA;

	void setPosition(float x, float y) {
		position.set(x, y);
	}

	void setColorRGBA(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a) {
		colorRGBA.set(_r, _g, _b, _a);
	}
};