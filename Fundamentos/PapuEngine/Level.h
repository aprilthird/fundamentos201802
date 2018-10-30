#pragma once
#include <string>
#include <vector>
#include "SpriteBacth.h"

using namespace std;

const int TILE_WIDTH = 64;
class Level
{

private:
	vector<string> _levelData;
	int _numHumans;
	void parseLevel();
public:
	glm::vec2 _playerPosition;
	std::vector<glm::vec2> _zombiesPosition;
	glm::vec2 getPlayerPosition() const { 
		return _playerPosition; 
	};
	std::vector<glm::vec2> getZombiesPosition()const {
		return _zombiesPosition;
	};

	Level(const std::string& fileName);
	void draw();
	SpriteBacth _spriteBatch;
	~Level();
};

