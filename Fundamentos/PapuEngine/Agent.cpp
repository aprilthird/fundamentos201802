#include "Agent.h"
#include "ResourceManager.h"
#include "Level.h"
#include <algorithm>

Agent::Agent()
{
}

Agent::Agent(glm::vec2 position, float speed)
{
	_position = position;
	_speed = speed;
}

void Agent::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("Textures/webardo.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData) {
	std::vector<glm::vec2> collideWithTilePosition;
	checkTilePosition(levelData,
		collideWithTilePosition,
		_position.x,
		_position.y);
	checkTilePosition(levelData,
		collideWithTilePosition,
		_position.x + AGENT_WIDTH,
		_position.y);
	checkTilePosition(levelData,
		collideWithTilePosition,
		_position.x,
		_position.y + AGENT_WIDTH);
	checkTilePosition(levelData,
		collideWithTilePosition,
		_position.x + AGENT_WIDTH,
		_position.y + AGENT_WIDTH);

	if (collideWithTilePosition.size() == 0) {
		return false;
	}
	for (size_t i = 0; i < collideWithTilePosition.size(); ++i) {
		collideWithTile(collideWithTilePosition[i]);
	}
	return true;
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData,
	std::vector<glm::vec2>& collideTilePosition,
	float x, float y) {

	glm::vec2 cornesPos = glm::vec2(floor(x / (float)TILE_WIDTH));
	if (cornesPos.x < 0 || cornesPos.x >= levelData[0].size()
		|| cornesPos.y < 0 || cornesPos.y >= levelData[0].size()) {
		return;
	}
	if (levelData[cornesPos.y][cornesPos.x] != '.') {
		collideTilePosition.push_back(cornesPos * 
			(float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

void Agent::collideWithTile(glm::vec2 tilePos) {
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPosition - tilePos;
	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	if (xDepth > 0 || yDepth > 0) {
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			if (distVec.x < 0) {
				_position.x -= xDepth;
			}
			else {
				_position.x += xDepth;
			}
		}
		else {
			if (distVec.y < 0) {
				_position.y -= yDepth;
			}
			else {
				_position.y += yDepth;
			}
		}
	}
}

bool Agent::collideWithOther(Agent* other) {
	glm::vec2 centerPosA = _position + glm::vec2(AGENT_WIDTH / 2);
	glm::vec2 centerPosB = other->getPosition() + glm::vec2(AGENT_WIDTH / 2);
	glm::vec2 dist = centerPosA - centerPosB;
	const float MIN_DISTANCE = AGENT_RADIUS * 2;
	float distance = glm::length(dist);
	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth > 0) {
		glm::vec2 collisionDepthVec = glm::normalize(dist) * collisionDepth;
		_position += collisionDepthVec / 2.0f;
		other->_position -= collisionDepthVec / 2.0f;
		return true;
	}
	return false;
}

Agent::~Agent()
{
}
