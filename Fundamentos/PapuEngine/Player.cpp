#include "Player.h"
#include "ResourceManager.h"
#include <SDL\SDL.h>


void Player::init(float speed, glm::vec2 position, InputManager* inputManager) {
	_speed = speed;
	_position = position;
	_inputManager = inputManager;
	//color.set(0, 0, 185, 255);
	color.set(255, 255, 255, 255);
}
void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies) {


	if (_inputManager->isKeyPressed(SDLK_w)) {
		_direction = glm::vec2(0, 1);
		_position.y += _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_s)) {
		_direction = glm::vec2(0, -1);
		_position.y -= _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_a)) {
		_direction = glm::vec2(-1, 0);
		_position.x -= _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_d)) {
		_direction = glm::vec2(1, 0);
		_position.x += _speed;
	}

	collideWithLevel(levelData);
}

void Player::draw(SpriteBacth& spriteBatch) {
	static int textureID = ResourceManager::getTexture("Textures/webardo.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

Player::Player()
{
}


Player::~Player()
{
}
