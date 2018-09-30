#pragma once
#include <glm\glm.hpp>
#include <string>
#include <vector>

#include "Vertex.h"
#include "SpriteBatch.h"

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH * 0.5;

class Entity
{
protected:
	glm::vec2 _position;
	float _speed;
	ColorRGBA color;
	void checkTilePosition(const std::vector<std::string>& levelData, 
		std::vector<glm::vec2>& collideTilePosition, float x, float y);
	void collideWithTile(glm::vec2 tilePos);
	bool collideWithLevel(const std::vector<std::string>& levelData);
public:
	Entity();
	glm::vec2 getPosition() const {
		return _position;
	}
	virtual void update() = 0;
	void draw(SpriteBatch& spriteBatch);
	bool collideWithEntity(Entity* entity);
	~Entity();
};

