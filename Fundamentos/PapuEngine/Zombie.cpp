#include "Zombie.h"
#include "ResourceManager.h"
#include "Bullet.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>


Zombie::Zombie()
{
}

Zombie::Zombie(glm::vec2 position, float speed, int life) : Agent(position, speed)
{
	_direction = glm::vec2(0.0f, 0.0f);
	_life = life;
}

void Zombie::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("Textures/Zombie.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

void Zombie::update(glm::vec2 playerPosition, const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies) {

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> ranRotate(-40.0f, 40.0f);

	if (collideWithLevel(levelData)) {
		_direction = glm::rotate(_direction, ranRotate(randomEngine));
	}
	else {
		_direction = glm::normalize(playerPosition - _position);
	}

	/*if (playerPosition.x > _position.x)
	else
		_position.x -= _speed;
	if (playerPosition.y > _position.y)
		_position.y += _speed;
	else
		_position.y -= _speed;
*/
	_position += _direction * _speed;

	for (int j = 0; j < zombies.size(); j++) {
		if (this != zombies[j]) this->collideWithOther(zombies[j]);
	}
}

bool Zombie::collideWithBullet(Bullet bullet) {
	glm::vec2 centerPosA = _position + glm::vec2(AGENT_WIDTH / 2);
	glm::vec2 centerPosB = bullet.getPosition() + glm::vec2(AGENT_WIDTH / 2);
	glm::vec2 dist = centerPosA - centerPosB;
	const float MIN_DISTANCE = AGENT_RADIUS * 2;
	float distance = glm::length(dist);
	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth > 0) {
		glm::vec2 collisionDepthVec = glm::normalize(dist) * collisionDepth;
		_position += collisionDepthVec / 2.0f;
		bullet.setPosition(bullet.getPosition() - collisionDepthVec / 2.0f);
		_life -= 20;
		return true;
	}
	return false;
}

void Zombie::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
	_position.y += _speed;
}

Zombie::~Zombie()
{
}
