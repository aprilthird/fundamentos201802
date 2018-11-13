#pragma once
#include <glm\glm.hpp>
#include "SpriteBacth.h"
#include "GLTexture.h"

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Zombie;
class Human;

class Agent
{
protected:
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
	Color color;
	void checkTilePosition(const std::vector<std::string>& levelData, 
		std::vector<glm::vec2>& collideTilePosition,
		float x, float y);
	void collideWithTile(glm::vec2 tilePos);
public:
	Agent();
	Agent(glm::vec2 position, float speed);
	glm::vec2 getPosition()const { return _position; };
	glm::vec2 getDirection() const { return _direction; }
	virtual void update(
		const std::vector<std::string>& levelData, 
		std::vector<Human*>& humans, 
		std::vector<Zombie*>& zombies
	) = 0;
	float getSpeed() { return _speed;  }
	virtual void draw(SpriteBacth& spritebatch);
	bool collideWithLevel(const std::vector<std::string>& levelData);
	bool collideWithOther(Agent* other);
	virtual ~Agent();
};

