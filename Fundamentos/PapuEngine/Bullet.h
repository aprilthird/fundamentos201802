#pragma once
#include <glm/glm.hpp>
#include "SpriteBacth.h"
#include "Agent.h"

class Bullet
{
private:
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
	int _lifeTime;
public:
	Bullet(glm::vec2 po, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();
	//void init(glm::vec2 po,glm::vec2 dir,float speed, int lifeTime);
	void draw(SpriteBacth& spriteBatch);
	bool update();
	glm::vec2 getPosition() { return _position; }
	void setPosition(glm::vec2 position) { _position = position; }
};

