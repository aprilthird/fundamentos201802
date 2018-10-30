#pragma once
#include <glm\glm.hpp>
#include "SpriteBacth.h"
#include "GLTexture.h"


const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Actor
{
protected:
	glm::vec2 _position;
	float _speed;
	Color color;

public:
	Actor();
	glm::vec2 getPosition()const { return _position; };
	virtual void update(const std::vector<std::string>& levelData) = 0;
	void draw(SpriteBacth& spritebatch);
	virtual ~Actor();
};

