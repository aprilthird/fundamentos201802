#include <cstddef>

#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

Sprite::Sprite()
{
	vboID = 0;
}

void Sprite::init(float _x, float _y, int _width, int _height, string texturePath)
{
	x = _x;
	y = _y;
	height = _height;
	width = _width;

	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}

	texture = ResourceManager::getTexture(texturePath);

	Vertex vertexData[6];
	vertexData[0].setPosition(x + width, y + height);
	vertexData[1].setPosition(x + width, y);
	vertexData[2].setPosition(x, y);
	vertexData[3].setPosition(x, y);
	vertexData[4].setPosition(x, y + height);
	vertexData[5].setPosition(x + width, y + height);

	vertexData[0].setUV(0.0f, 0.0f);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setUV(1.0f, 1.0f);
	vertexData[3].setUV(1.0f, 1.0f);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setUV(0.0f, 0.0f);

	//for (int i = 0; i < 6; ++i) {
	//	vertexData[i].setColorRGBA(255, 0, 0, 255);
	//}
	//vertexData[1].setColorRGBA(0, 0, 255, 255);
	//vertexData[4].setColorRGBA(0, 255, 0, 255);
	//vertexData[5].setColorRGBA(255, 0, 255, 0);
	//vertexData[1].setColorRGBA(255, 255, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	//posicion
	glVertexAttribPointer(0, 
		2, 
		GL_FLOAT, 
		GL_FALSE, 
		sizeof(Vertex), 
		(void*)offsetof(Vertex, position)); 
	/* Indice 0 (Primero), Vertex conformado por DOS atributos, tipo de los atributos, 
	si se va a parsear el color de 0-255(RGB) a 0-1 (GPU), 
	tamaño y la función importada para saber la posición de memoria del color y vertex*/
	//color
	glVertexAttribPointer(1,
		4,
		GL_UNSIGNED_BYTE,
		GL_TRUE,
		sizeof(Vertex),
		(void*)offsetof(Vertex, colorRGBA));
	//UV
	glVertexAttribPointer(2, 
		2, 
		GL_FLOAT, 
		GL_FALSE, 
		sizeof(Vertex), 
		(void*)offsetof(Vertex, uv));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Sprite::~Sprite()
{
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}