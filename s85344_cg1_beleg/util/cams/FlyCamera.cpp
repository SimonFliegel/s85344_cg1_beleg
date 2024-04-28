#include "FlyCamera.h"

#include <gtx/transform.hpp>

FlyCamera::FlyCamera(float yaw, float pitch, float zoom, float speed, float sensitvity)
{
	this->zoom = zoom;
	this->yaw = yaw;
	this->pitch = pitch;
	this->movementSpeed = speed;
	this->mouseSensitivity = sensitvity;

	firstMouse = true;

	// @TODO: make these configurable?
	position = glm::vec3(0.0f, 0.0f, 1.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
}

void FlyCamera::processKeyboardInput(ECameraMovementDirection direction, float deltaTime)
{
	float velocity = MOVEMENT_SPEED * deltaTime;
	if (direction == ECameraMovementDirection::FORWARD) {
		position += front * velocity;
	}
	if (direction == ECameraMovementDirection::BACKWARD) {
		position -= front * velocity;
	}
	if (direction == ECameraMovementDirection::LEFT) {
		position -= right * velocity;
	}
	if (direction == ECameraMovementDirection::RIGHT) {
		position += right * velocity;
	}
}

void FlyCamera::processMouseInput(int xPos, int yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	auto xOffset = float(xPos - lastX);
	auto yOffset = float(lastY - yPos); // y-coordinates range from bottom to top
	lastX = xPos;
	lastY = yPos;

	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	// constrain pitch
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateCameraVectors();
}

void FlyCamera::processScrollInput(int dir)
{
	zoom -= (float) dir; // dir: 1 = zoom in, -1 = zoom out, zoom is the field of view
	if (zoom < MAX_ZOOM)
		zoom = MAX_ZOOM;
	if (zoom > FOV)
		zoom = FOV;
}

glm::mat4 FlyCamera::getViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 FlyCamera::getProjectionMatrix(int windowWidth, int windowHeight) const
{
	return glm::perspective(glm::radians(zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
}

glm::vec3 FlyCamera::getPosition() const
{
	return position;
}

float FlyCamera::getZoom() const
{
	return zoom;
}

// @see: https://www.songho.ca/opengl/gl_anglestoaxes.html
void FlyCamera::updateCameraVectors()
{
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
