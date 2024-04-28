// @see https://github.com/JoeyDeVries/LearnOpenGL/blob/master/includes/learnopengl/camera.h
#pragma once

#include "AbstractCamera.h"

enum class ECameraMovementDirection
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float MOVEMENT_SPEED = 1.0f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f; // min zoom
const float MAX_ZOOM = 5.0f;

class FlyCamera : public AbstractCamera
{
public: 
	FlyCamera(float yaw = YAW, float pitch = PITCH, float zoom = FOV, float movementSpeed = MOVEMENT_SPEED, float sensitivity = SENSITIVITY);

	void processKeyboardInput(ECameraMovementDirection direction, float deltaTime);
	void processMouseInput(int xPos, int yPos);
	void processScrollInput(int dir);
	glm::mat4 getViewMatrix() const override;
	glm::mat4 getProjectionMatrix(int windowWidth, int windowHeight) const override;
	glm::vec3 getPosition() const override;	
	float getZoom() const;

private:
	float zoom;
	float movementSpeed;
	float mouseSensitivity;

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	// euler angles
	float yaw;
	float pitch;

	bool firstMouse;
	int lastX;
	int lastY;

	void updateCameraVectors();
};

