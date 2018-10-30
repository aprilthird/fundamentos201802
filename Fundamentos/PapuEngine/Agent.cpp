#include "Agent.h"
#include "ResourceManager.h"

Agent::Agent()
{
}

Agent::Agent(glm::vec2 position, float speed)
{
	_position = position;
	_speed = speed;
}

void Agent::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("Textures/circle.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

Agent::~Agent()
{
}
