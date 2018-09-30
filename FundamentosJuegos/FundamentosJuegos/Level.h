#pragma once
#include <string>
#include <vector>
#include "SpriteBatch.h"

using namespace std;

const int TILE_WIDTH = 64;

class Level
{
private:
	vector<string> _levelData;
	int _numHumans;
	void parseLevel();
	glm::vec2 _playerPosition;
	vector<glm::vec2> _zombiesPosition;

public:
	glm::vec2 getPlayerPosition() const {
		return _playerPosition;
	}

	vector<glm::vec2> getZombiesPosition() const {
		return _zombiesPosition;
	}

	Level(const std::string& filename);
	void draw();
	SpriteBatch _spriteBatch;
	~Level();
};

