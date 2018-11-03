#pragma once
#include "Agent.h"
class Zombie :public Agent
{
public:
	Zombie();
	Zombie(glm::vec2 position, float speed);
	void draw(SpriteBacth& spriteBatch);
	void update(glm::vec2 playerPosition);
	void update(
		const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies
	);
	~Zombie();
};

