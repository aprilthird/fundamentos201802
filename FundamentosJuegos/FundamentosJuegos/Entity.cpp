#include "Entity.h"
#include "ResourceManager.h"
#include "Level.h"
#include <algorithm>


Entity::Entity()
{
}

void Entity::draw(SpriteBatch& spriteBatch) {
	static int textureID = ResourceManager::getTexture("Textures/circle.png").id;
	const glm::vec4 uvRect(0.0, 0.0, 1.0, 1.0);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spriteBatch.draw(destRect, uvRect, textureID, 0.0, color);
}

bool Entity::collideWithLevel(const std::vector<std::string>& levelData) {
	std::vector<glm::vec2> collideTilePosition;
	checkTilePosition(levelData, collideTilePosition, 
		_position.x, _position.y);
	checkTilePosition(levelData, collideTilePosition, 
		_position.x + AGENT_WIDTH, _position.y);
	checkTilePosition(levelData, collideTilePosition, 
		_position.x, _position.y + AGENT_WIDTH);
	checkTilePosition(levelData, collideTilePosition, 
		_position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);

	if (collideTilePosition.size() == 0) return false;

	for (size_t i = 0; i < collideTilePosition.size(); i++) {
		collideWithTile(collideTilePosition[i]);
	}
}

bool Entity::collideWithEntity(Entity* entity) {
	return false;
}

void Entity::checkTilePosition(const std::vector<std::string>& levelData,
	std::vector<glm::vec2>& collideTilePosition, float x, float y) {

	glm::vec2 cornesPos = glm::vec2(floor(x / (float)AGENT_RADIUS), floor(y / (float)AGENT_WIDTH));

	if (cornesPos.x < 0 || cornesPos.x >= levelData[0].size() || 
		cornesPos.y < 0 || cornesPos.y >= levelData.size()) {
		return;
	}

	if (levelData[cornesPos.y][cornesPos.x] != '.') {
		collideTilePosition.push_back(
			cornesPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0));
	}
}

Entity::~Entity()
{
}
