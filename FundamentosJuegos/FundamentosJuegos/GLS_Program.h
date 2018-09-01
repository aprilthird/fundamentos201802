#pragma once

#include <GL\glew.h>
#include <string>

using namespace std;

class GLS_Program
{
private:
	GLuint programID;
	GLuint fragmentShaderID;
	GLuint fragmentVertexID;
	void compileShader(const string& shaderPath, GLuint uid);

public:
	GLS_Program();
	int numAttribute;
	void addAttribut(const string atributeName);
	void use();
	void unuse();
	void compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath);
	void linkShader();
	GLuint getUniformLocation(const string& name);
	~GLS_Program();
};