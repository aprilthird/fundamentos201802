#pragma once
#include <glm/glm.hpp>
#include "SpriteBacth.h"
class Bullet
{
private:
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
	int _lifeTime;
public:
	Bullet(glm::vec2 po, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();
	//void init(glm::vec2 po,glm::vec2 dir,float speed, int lifeTime);
	void draw(SpriteBacth& spriteBatch);
	bool update();

};

