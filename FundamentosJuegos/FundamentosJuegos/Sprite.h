#pragma once

#include <string>
#include <GL\glew.h>

#include "GLTexture.h"

using namespace std;

class Sprite
{
private:
	GLTexture texture;
	float x;
	float y;
	int width;
	int height;
	GLuint vboID;
public:
	Sprite();
	void init(float _x, float _y, int _width, int _height, string texturePath);
	void draw();
	~Sprite();
};