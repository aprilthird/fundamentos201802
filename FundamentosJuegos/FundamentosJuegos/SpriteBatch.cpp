#include "SpriteBatch.h"
#include <algorithm>


SpriteBatch::SpriteBatch() : vao(0), vbo(0)
{
}

void SpriteBatch::init() {
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType _sortType) {
	sortType = _sortType;
	renderBatches.clear();
	glyphs.clear();
}

void SpriteBatch::end() {
	glyphsPointers.resize(glyphs.size());
	for (size_t i = 0; i < glyphs.size(); i++) {
		glyphsPointers[i] = &glyphs[i];
	}
	sortGlyph();
	createRenderBatches();
}

void SpriteBatch::createRenderBatches() {
	std::vector<Vertex> vertices;
	vertices.resize(glyphs.size() * 6);
	if (glyphs.empty()) {
		return;
	}
	int cv = 0;
	int offset = 0;
	renderBatches.emplace_back(offset, 6, glyphsPointers[0]->texture);

	vertices[cv++] = glyphsPointers[0]->topLeft;
	vertices[cv++] = glyphsPointers[0]->bottomLeft;
	vertices[cv++] = glyphsPointers[0]->bottomRight;
	vertices[cv++] = glyphsPointers[0]->bottomRight;
	vertices[cv++] = glyphsPointers[0]->topRight;
	vertices[cv++] = glyphsPointers[0]->topLeft;
	offset += 6;

	for (int cg = 1; cg < glyphsPointers.size(); cg++) {
		if (glyphsPointers[cg]->texture != glyphsPointers[cg - 1]->texture) {
			renderBatches.emplace_back(offset, 6, glyphsPointers[0]->texture);
		}
		else {
			renderBatches.back().numVertixex += 6;
		}
		vertices[cv++] = glyphsPointers[cg]->topLeft;
		vertices[cv++] = glyphsPointers[cg]->bottomLeft;
		vertices[cv++] = glyphsPointers[cg]->bottomRight;
		vertices[cv++] = glyphsPointers[cg]->bottomRight;
		vertices[cv++] = glyphsPointers[cg]->topRight;
		vertices[cv++] = glyphsPointers[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::renderBatch() {
	glBindVertexArray(vao);
	for (size_t i = 0; i < renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertixex);
	}
	glBindVertexArray(0);
}

void SpriteBatch::sortGlyph() {
	switch (sortType) {
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(
			glyphsPointers.begin(), glyphsPointers.end(), compareBackToFront
		);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(
			glyphsPointers.begin(), glyphsPointers.end(), compareFrontToBack
		);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(
			glyphsPointers.begin(), glyphsPointers.end(), compareTexture
		); 
		break;
	}
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
	return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
	return (a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
	return (a->texture < b->texture);
}

SpriteBatch::~SpriteBatch()
{
}
