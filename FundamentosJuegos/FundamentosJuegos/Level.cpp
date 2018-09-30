#include "Level.h"
#include "Error.h"
#include "ResourceManager.h"

#include <fstream>

Level::Level(const std::string& filename)
{
	std::ifstream file;
	file.open(filename);
	if (file.fail()) {
		fatalError("failed to open " + filename);
	}
	string tmp = "";
	while (std::getline(file, tmp)) {
		_levelData.push_back(tmp);
	}
	parseLevel();
}

void Level::parseLevel() {
	_spriteBatch.init();
	_spriteBatch.begin();
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	for (int y = 0; y < _levelData.size(); y++) {
		for (int x = 0; x < _levelData[y].size(); x++) {
			char tile = _levelData[y][x];
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
			switch (tile) {
			case 'R':
				break;
			case 'B':
				_spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture("Textures/red_bricks.png").id, 0.0f, color);
				break;
			case 'G':
				_spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture("Textures/glass.png").id, 0.0f, color);
				break;
			case 'L':
				break;
			case '@':
				break;
			case 'Z':
				break;
			case '.':
				break;
			default:
				break;
			}
		}
	}
}

Level::~Level()
{
}
