#pragma once
#include "Agent.h"
#include "Bullet.h"
class Zombie :public Agent
{
public:
	int _life;
	Zombie();
	Zombie(glm::vec2 position, float speed, int life);
	void draw(SpriteBacth& spriteBatch);
	void update(glm::vec2 playerPosition, const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
	void update(
		const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies
	);
	bool collideWithBullet(Bullet bullet);
	~Zombie();
};

