#pragma once
#include "Entity.h"

class Human : public Entity
{
protected:
	glm::vec2 _direction;
public:
	Human();
	~Human();
	void init(float speed, glm::vec2 position);
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Human*>& zombies);
};

