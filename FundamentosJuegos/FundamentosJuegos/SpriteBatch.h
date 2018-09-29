#pragma once
#include <GL\glew.h>
#include "Vertex.h"
#include <glm\glm.hpp>
#include <vector>

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class Glyph {
public:
	GLuint texture;
	Vertex topLeft;
	Vertex topRight;
	Vertex bottomLeft;
	Vertex bottomRight;
	float depth;

	Glyph() {}
	Glyph(const glm::vec4& _destRect, const glm::vec4& _uvRect, 
		GLuint _texture, float _depth, const ColorRGBA& _color) {
		depth = _depth;

		//Z => ancho
		//W => alto

		texture = _texture;
		topLeft.colorRGBA = _color;
		topLeft.setPosition(_destRect.x, _destRect.y + _destRect.w);
		topLeft.setUV(_uvRect.x, _uvRect.y + _uvRect.w);

		topRight.colorRGBA = _color;
		topRight.setPosition(_destRect.x + _destRect.z, _destRect.y + _destRect.w);
		topRight.setUV(_uvRect.x + _uvRect.z, _uvRect.y + _uvRect.w);

		bottomLeft.colorRGBA = _color;
		bottomLeft.setPosition(_destRect.x, _destRect.y);
		bottomLeft.setPosition(_uvRect.x, _uvRect.y);

		bottomRight.colorRGBA = _color;
		bottomRight.setPosition(_destRect.x + _destRect.z, _destRect.y);
		bottomRight.setPosition(_uvRect.x + _uvRect.z, _uvRect.y);
	} 
	~Glyph() {}
};

class RenderBatch {
public:
	RenderBatch(GLuint _offset, GLuint _numVertixex, GLuint _texture);
	GLuint offset;
	GLuint numVertixex;
	GLuint texture;
};

// Ayuda a mandar los sprites como arreglo optimizando el dibujado, 
// así el shader no se ralentizará cuando hayan muchas imágenes

class SpriteBatch
{
private:
	GLuint vbo;
	GLuint vao;
	std::vector<Glyph> glyphs;
	std::vector<Glyph*> glyphsPointers;
	std::vector<RenderBatch> renderBatches;
	void createVertexArray();
	void setGlyph();
	GlyphSortType sortType;
	void createRenderBatches();

public:
	SpriteBatch();
	~SpriteBatch();

	void init();
	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, ColorRGBA color);

	void renderBatch();
	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);
	void sortGlyph();
};