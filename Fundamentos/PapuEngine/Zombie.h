#pragma once
#include "Agent.h"
class Zombie :public Agent
{
public:
	Zombie();
	Zombie(glm::vec2 position, float speed);
	void draw(SpriteBacth& spriteBatch);
	void update();
	void update(glm::vec2 playerPosition);
	~Zombie();
};

