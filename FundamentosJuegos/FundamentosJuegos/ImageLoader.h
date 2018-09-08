#pragma once
#include <string>

#include "GLTexture.h";

using namespace std;

class ImageLoader
{
public:
	static GLTexture loadPNG(string filePath);
};

