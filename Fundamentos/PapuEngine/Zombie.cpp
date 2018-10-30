#include "Zombie.h"
#include "ResourceManager.h"


Zombie::Zombie()
{
}

Zombie::Zombie(glm::vec2 position, float speed) : Agent(position, speed)
{
}

void Zombie::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("Textures/Zombie.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

void Zombie::update() { 
	_position.y += _speed;
}

void Zombie::update(glm::vec2 playerPosition) {
	if (playerPosition.x > _position.x)
		_position.x += _speed;
	else
		_position.x -= _speed;
	if (playerPosition.y > _position.y)
		_position.y += _speed;
	else
		_position.y -= _speed;
}

Zombie::~Zombie()
{
}
