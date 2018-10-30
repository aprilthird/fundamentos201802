#include "Actor.h"
#include "ResourceManager.h"
#include "Level.h"
#include <algorithm>

Actor::Actor()
{

}

void Actor::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("Images/circle.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

Actor::~Actor()
{
}