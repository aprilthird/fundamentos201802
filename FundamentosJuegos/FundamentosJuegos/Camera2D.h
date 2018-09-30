#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera2D
{
private:
	glm::vec2 position;
	float scale;
	int screenWidth;
	int screenHeight;
	bool updateCameraMatrix;
	glm::mat4 cameraMatrix;
	glm::mat4 orthoMatrix;
public:
	Camera2D();
	~Camera2D();

	void update();
	void init(int _screenWidth, int _screenHeight);
	glm::vec2 convertScreenToWorl(glm::vec2 screenScoords);

	void setPosition(const glm::vec2& newPosition) {
		position = newPosition;
		updateCameraMatrix = true;
	}

	void setScale(float newScale) {
		scale = newScale;
		updateCameraMatrix = true;
	}

	glm::vec2 getPosition() const {
		return position;
	}

	float getScale() {
		return scale;
	}

	glm::mat4 getCameraMatrix() {
		return cameraMatrix;
	}
};

