#include "Human.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>

Human::Human()
{
}

void Human::init(float speed, glm::vec2 position) {
	color.set(185, 0, 0, 255);
	_speed = speed;
	_position = position;

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> ranDir(-1.0f, 1.0f);

	_direction = glm::vec2(ranDir(randomEngine), ranDir(randomEngine));
	if (_direction.length() == 0) {
		_direction = glm::vec2(1.0f, 1.0f);
	}
	_direction = glm::vec2(_direction);
}

void Human::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies) {

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> ranRotate(-40.0f, 40.0f);
	_position += _direction * _speed;
	if (collideWithLevel(levelData)) {
		_direction = glm::rotate(_direction, ranRotate(randomEngine));
	}
}

Human::~Human()
{
}
