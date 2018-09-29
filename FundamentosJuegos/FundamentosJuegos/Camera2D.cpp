#include "Camera2D.h"



Camera2D::Camera2D() : 
	position(0, 0),
	cameraMatrix(1.0f),
	updateCameraMatrix(true),
	orthoMatrix(1.0f),
	screenWidth(500),
	screenHeight(500)
{
}


Camera2D::~Camera2D()
{
}


void Camera2D::init(int _screenWidth, int _screenHeight) {
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
}


void Camera2D::update() {
	if (updateCameraMatrix) {
		updateCameraMatrix = false;
		glm::vec3 translate(-position.x + screenWidth * 0.5, -position.y + screenHeight * 0.5, 0.0f);
		cameraMatrix = glm::translate(orthoMatrix, translate);
		glm::vec3 scale(scale, scale, 0.0f);
		cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * cameraMatrix;
	}
}